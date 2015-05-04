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

float MHI_DURATION = 0.05;
int DEFAULT_THRESHOLD = 32;
float MAX_TIME_DELTA = 12500.0;
float MIN_TIME_DELTA = 5;

int main (int argc, char** argv) {
    cv::namedWindow("motion", CV_WINDOW_AUTOSIZE);

    cv::VideoCapture cap(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
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
    cv::Mat vis(h, w, CV_32FC3);
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

        cv::imshow("motion", motion_mask);
        prev_frame = frame.clone();
        if (cv::waitKey(30) >= 0) {
            std::cout << "esc key is pressed by user" << std::endl;
            break; 
        }
    }

    return 0;
}
