#include <stdio.h>
#include <cv.h>
#include <cstdlib>
#include <highgui.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdlib.h>
#include "opencv2/video/tracking.hpp"
#include <math.h>
#include <time.h>
#include "oscpack/osc/OscOutboundPacketStream.h"
#include "oscpack/ip/UdpSocket.h"
#include <string>
#include <sstream>
#include <chrono>
#include <thread>

#define OUTPUT_BUFFER_SIZE 1024 * 4

float MHI_DURATION = 0.05;
int DEFAULT_THRESHOLD = 16;
float MAX_TIME_DELTA = 12500.0;
float MIN_TIME_DELTA = 5;

int GRID_HEIGHT = 8;
int GRID_WIDTH = 8;

int main (int argc, char** argv) {
    // OSC setup
    std::string address = "127.0.0.1";
    int port = 7000;
    if (argc > 3) {
        address = argv[2];
        char* endptr;
        port = strtol(argv[3], &endptr, 10);
        if (!*argv[1] || *endptr) {
            std::cerr << "WAT! '" << argv[3]
                << "' can not be intepreted as a port number"
                << std::endl;
            return -1;
        }
    }

    UdpTransmitSocket transmitSocket(IpEndpointName(address.c_str(), port));
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);
    std::string osc_address_str;
    std::vector<float> osc_data;

    cv::VideoCapture cap;
    bool is_video_file = false;

    long int cam_num = 0;
    if (argc > 1) {
        char* endptr;
        cam_num = strtol(argv[1], &endptr, 10);
        if (!*argv[1] || *endptr) {
            std::cout << "Opening video file." << std::endl;
            cap.open(argv[1]);
            is_video_file = true;
        } else {
            cap.open(cam_num);
        }
    } else {
        cap.open(0);
    }

    std::stringstream osc_cam_id;
    osc_cam_id << "/Arbor/Camera/" << cam_num << "/";
    cv::namedWindow(osc_cam_id.str().c_str(), CV_WINDOW_AUTOSIZE);

    cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    if (!cap.isOpened()) {
        std::cerr << "Cannot open video source" << std::endl;
        return -1;
    }

    cv::Mat frame, frame_diff, gray_diff, motion_mask;
    cap.read(frame);
    cv::Size frame_size = frame.size();
    int h = frame_size.height;
    int w = frame_size.width;
    double timestamp = 1000.0 * clock() / CLOCKS_PER_SEC;
    cv::Mat prev_frame = frame.clone();
    cv::Mat motion_history(h, w, CV_32FC1, cv::Scalar(0, 0, 0));
    cv::Mat mg_mask(h, w, CV_8UC1, cv::Scalar(0, 0, 0));
    cv::Mat mg_orient(h, w, CV_32FC1, cv::Scalar(0, 0, 0));
    cv::Mat seg_mask(h, w, CV_32FC1, cv::Scalar(0, 0, 0));
    std::vector<cv::Rect> seg_bounds;
    cv::Mat visual(h, w, CV_8UC3);
    cv::Mat silh_roi, orient_roi, mask_roi, mhi_roi;
    cv::Mat rolling_avg = cv::Mat::zeros(GRID_HEIGHT+1, GRID_WIDTH+1,
                                         CV_32F);
    cv::Mat active_grid = cv::Mat::zeros(GRID_HEIGHT+1, GRID_WIDTH+1,
                                         CV_32F);

    int frame_count = 0;
    time_t timer_begin, timer_end;
    time (&timer_begin);

    while (1) {
        osc_data.clear();


        cap.read(frame);
        if (!frame.data) {
            if (is_video_file) {
                cap.set(CV_CAP_PROP_POS_AVI_RATIO, 0);
                continue;
            } else {
                std::cout << "camera stopped" << std::endl;
                break;
            }
        }

        cv::absdiff(frame, prev_frame, frame_diff);
        cv::cvtColor(frame_diff, gray_diff, CV_BGR2GRAY);
        cv::threshold(gray_diff, motion_mask, DEFAULT_THRESHOLD, 255, 0);
        timestamp = 1000.0 * clock() / CLOCKS_PER_SEC;
        cv::updateMotionHistory(motion_mask, motion_history, timestamp,
                                MHI_DURATION);
        cv::calcMotionGradient(motion_history, mg_mask, mg_orient,
                               MIN_TIME_DELTA, MAX_TIME_DELTA, 3);
        cv::segmentMotion(motion_history, seg_mask, seg_bounds, timestamp, 32);

        for (int i = 0; i < seg_bounds.size(); i++) {
            const cv::Rect& rec = seg_bounds[i];
            if (rec.area() > 5000 && rec.area() < 70000) {
                silh_roi = motion_mask(rec);
                orient_roi = mg_orient(rec);
                mask_roi = mg_mask(rec);
                mhi_roi = motion_history(rec);
                if (norm(silh_roi, cv::NORM_L2, cv::noArray()) > rec.area()*0.5) {
                    double angle = cv::calcGlobalOrientation(
                        orient_roi, mask_roi, mhi_roi,timestamp, MHI_DURATION);
                }
            }
        }

        int GRID_SQUARE_HEIGHT = (h / GRID_HEIGHT); // 480 / 10 = 48
        int GRID_SQUARE_WIDTH = (w / GRID_WIDTH);   // 640 / 20 = 32

        // Check grid squares for activation.
        cv::Mat activation = cv::Mat::zeros(GRID_HEIGHT+1, GRID_WIDTH+1,
                                            CV_32F);
        for (int i=0; i<GRID_HEIGHT; ++i) {
            for (int j=0; j<GRID_WIDTH; ++j) {
                cv::Mat sub_mat = motion_mask(cv::Rect(
                    int(j * GRID_SQUARE_WIDTH),
                    int(i * GRID_SQUARE_HEIGHT),
                    int(GRID_SQUARE_WIDTH),
                    int(GRID_SQUARE_HEIGHT)));
                float total_activated = (float)cv::sum(sub_mat)[0];
                float percentage_activated = total_activated / (float)(
                    sub_mat.rows * 255 * sub_mat.cols);
                activation.at<float>(i, j) = percentage_activated;
            }
        }      

        cv::Scalar mean_activation;
        cv::Scalar stddev_activation;
        cv::Mat mask = (activation > 0.1);
        cv::meanStdDev(activation, mean_activation, stddev_activation, mask);

        float cutoff_activation = (mean_activation.val[0] +
                                    stddev_activation.val[0] * 0.5);
        if (cutoff_activation < 0.1) {
            cutoff_activation = 0.1;
        }

        cv::threshold(activation, activation, cutoff_activation, 1.0,
                      cv::THRESH_TOZERO);
        cv::Mat cutoff_mask = (activation > cutoff_activation);
        cv::normalize(activation, activation, 0.0, 1.0, cv::NORM_MINMAX,
                      -1, mask);

        active_grid = (active_grid * 0.6);
        cv::threshold(active_grid, active_grid, 0.01, 1.0, cv::THRESH_TOZERO);
        active_grid = cv::max(active_grid, activation);

        visual = frame.clone();
        cv::addWeighted(visual, 0.0,
                        frame, 0.8,
                        0.0, visual);

        // Paint grid lines on screen.
        for (int i=1; i<GRID_HEIGHT; ++i) {
            cv::line(visual,
                     cv::Point2i(0, int(i * GRID_SQUARE_HEIGHT)),
                     cv::Point2i(w, int(i * GRID_SQUARE_HEIGHT)),
                     cv::Scalar(255, 255, 255));
        }
        for (int i=1; i<GRID_WIDTH; ++i) {
            cv::line(visual,
                     cv::Point2i(int(i * GRID_SQUARE_WIDTH), 0),
                     cv::Point2i(int(i * GRID_SQUARE_WIDTH), h),
                     cv::Scalar(255, 255, 255));
        }

        // Paint activated boxes and construct osc grid.
        for (int i=0; i<GRID_HEIGHT; ++i) {
            for (int j=0; j<GRID_WIDTH; ++j) {
                float activate_level = active_grid.at<float>(i, j);
                // construct osc string
                osc_data.push_back(activate_level);
                if (activate_level > 0.01) {
                    cv::Rect display_rect(
                        int(j * GRID_SQUARE_WIDTH),
                        int(i * GRID_SQUARE_HEIGHT),
                        int(GRID_SQUARE_WIDTH),
                        int(GRID_SQUARE_HEIGHT));
                    cv::Mat buffer = cv::Mat::zeros(h, w, CV_8UC3);
                    cv::rectangle(
                        buffer,
                        display_rect,
                        cv::Scalar(255, 255, 255),
                        CV_FILLED);
                    cv::addWeighted(
                        visual, 1.0,
                        buffer, activate_level,
                        0.0, visual);
                }
            }
        }

        // Send OSC packet for Usine instrument.
        p.Clear();
        p << osc::BeginMessage(osc_cam_id.str().c_str());
        for (int i=0; i<osc_data.size(); ++i) {
            p << osc_data[i];
        }
        p << osc::EndMessage;
        transmitSocket.Send(p.Data(), p.Size());

        // Display activated squares overlayed on screen.
        cv::imshow(osc_cam_id.str().c_str(), visual);
        prev_frame = frame.clone();

	    ++frame_count;
        if (cv::waitKey(30) >= 0) {
            std::cout << "esc key is pressed by user" << std::endl;
            break;
        }
    }

    time (&timer_end);
    double seconds_elapsed = difftime (timer_end, timer_begin);
    std::cout << seconds_elapsed << " seconds for "
	      << frame_count << "  frames : FPS = "
	      <<  (float)((float)(frame_count) / seconds_elapsed)
	      << std::endl;

    return 0;
}
