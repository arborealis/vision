#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <sstream>

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#define OUTPUT_BUFFER_SIZE 1024 * 4

#if CV_MAJOR_VERSION < 3
  #define CAP_PROP_FRAME_WIDTH CV_CAP_PROP_FRAME_WIDTH
  #define CAP_PROP_FRAME_HEIGHT CV_CAP_PROP_FRAME_HEIGHT
#endif

std::string IntToString (int a)
{
    std::ostringstream temp;
    temp<<a;
    return temp.str();
}

std::string FloatToString (float a)
{
    std::ostringstream temp;
    temp<<a;
    return temp.str();
}

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
    double dWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    // get the height of frames of the video
    double dHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    std::cout << "Frame size : " << dWidth << " x " << dHeight << std::endl;

    // create a window called "MyVideo"
    cv::namedWindow("MyVideo", cv::WINDOW_AUTOSIZE); 

    std::string osc_address_str;
    std::string gridData;
    float activation;
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
        
        gridData = "";
        for (int i = 1; i < 21; ++i)
        {
            for (int j = 1; j < 11; ++j)
            {
                activation = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                if (activation < .7) {
                    gridData += "0,";
                } 
                else {
                    gridData += FloatToString(activation) + ",";
                }
                
            }
        }

        p.Clear();
        p << osc::BeginMessage("/A/C1") 
            << gridData.substr(0, gridData.size()-1).c_str()
            << osc::EndMessage;
    
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
