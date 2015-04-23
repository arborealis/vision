#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#define OUTPUT_BUFFER_SIZE 1024

#if CV_MAJOR_VERSION < 3
  #define CAP_PROP_FRAME_WIDTH CV_CAP_PROP_FRAME_WIDTH
  #define CAP_PROP_FRAME_HEIGHT CV_CAP_PROP_FRAME_HEIGHT
#endif

int main(int argc, char* argv[]) {
    if (argc >= 2 && std::strcmp(argv[1], "-h") == 0) {
        std::cout << "usage: entoptic [hostname [port]]\n";
        return 0;
    }

    const char* address = "127.0.0.1";
    if (argc >= 2)
        address = argv[1];

    int port = 7000;
    if (argc >= 3)
        port = std::atoi(argv[2]);

    // OSC setup
    UdpTransmitSocket transmitSocket(IpEndpointName(address, port));
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);

    // open the video camera no. 0
    cv::VideoCapture cap(0);

    // if not success, exit program
    if (!cap.isOpened()) {
        std::cout << "Cannot open the video cam" << std::endl;
        return -1;
    }

    // get the width of frames of the video
    double dWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    // get the height of frames of the video
    double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT);

    std::cout << "Frame size : " << dWidth << " x " << dHeight << std::endl;

    //create a window called "MyVideo"
    cv::namedWindow("MyVideo", cv::WINDOW_AUTOSIZE); 

    while (true) {
        cv::Mat frame;
        // read a new frame from video
        bool bSuccess = cap.read(frame);
        // if not success, break loop
        if (!bSuccess) { 
            std::cout << "Cannot read a frame from video stream" << std::endl;
            break;
        }

        // show the frame in "MyVideo" window
        imshow("MyVideo", frame); 

        // OSC stuff
        p.Clear();
        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/test1") 
                << true << 23 << (float)3.1415 << "hello"
            << osc::EndMessage
            << osc::BeginMessage("/test2") 
                << true << 24 << (float)10.8 << "world"
            << osc::EndMessage
        << osc::EndBundle;
    
        transmitSocket.Send(p.Data(), p.Size());

        // wait for 'esc' key press for 30ms.
        // If 'esc' key is pressed, break loop
        if (cv::waitKey(30) == 27) { 
            std::cout << "esc key is pressed by user" << std::endl;
            break; 
        }
    }
    return 0;
}
