#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "opencv2/video/tracking.hpp"
#include <math.h>
#include <time.h>
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

float MHI_DURATION = 0.05;
int DEFAULT_THRESHOLD = 16;
float MAX_TIME_DELTA = 12500.0;
float MIN_TIME_DELTA = 5;

int GRID_HEIGHT = 10;
int GRID_WIDTH = 20;

int main (int argc, char** argv) {
    cv::namedWindow("motion", CV_WINDOW_AUTOSIZE);

    cv::VideoCapture cap(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 800);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
    if (!cap.isOpened()) {
        std::cerr << "Cannot open camera" << std::endl;
        return -1;
    }

    cv::Mat frame, frame_diff, gray_diff, motion_mask;
    cap.read(frame);
    cv::Size frame_size = frame.size();
    int h = frame_size.height;
    int w = frame_size.width;
    double timestamp = 1000.0 * clock() / CLOCKS_PER_SEC;
    cv::Mat prev_frame = frame.clone();
    cv::Mat motion_history(h, w, CV_32FC1, cv::Scalar(0,0,0));
    cv::Mat mg_mask(h, w, CV_8UC1, cv::Scalar(0,0,0));
    cv::Mat mg_orient(h, w, CV_32FC1, cv::Scalar(0,0,0));
    cv::Mat seg_mask(h, w, CV_32FC1, cv::Scalar(0,0,0));
    std::vector<cv::Rect> seg_bounds;
    cv::Mat visual(h, w, CV_32FC3);
    cv::Mat silh_roi, orient_roi, mask_roi, mhi_roi;

    while (1) {
        cap.read(frame);
        if(!frame.data) {
            std::cout << "camera stopped" << std::endl;
            break;
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
                float total = (float)cv::sum(sub_mat)[0];
                activation.at<float>(i, j) = total / (float)(
                    sub_mat.rows * 255 * sub_mat.cols);
            }
        }

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
        // Paint activated boxes.
        for (int i=0; i<GRID_HEIGHT; ++i) {
            for (int j=0; j<GRID_WIDTH; ++j) {
                float activate_level = activation.at<float>(i, j);
                if (activate_level < 0.1)
                    continue;
                cv::Mat active_rect(h, w, CV_32FC3);
                cv::Rect display_rect(
                    int(j * GRID_SQUARE_WIDTH),
                    int(i * GRID_SQUARE_HEIGHT),
                    int(GRID_SQUARE_WIDTH),
                    int(GRID_SQUARE_HEIGHT));
                cv::rectangle(
                    visual,
                    display_rect,
                    cv::Scalar(255, 255, 255),
                    CV_FILLED);
                //cv::addWeighted(visual, 1.0,
                //                active_rect, activate_level,
                //                0.0, visual);
            }
        }

        cv::imshow("motion", visual);
        prev_frame = frame.clone();
        if (cv::waitKey(30) >= 0) {
            std::cout << "esc key is pressed by user" << std::endl;
            break; 
        }
    }

    return 0;
}
