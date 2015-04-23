#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#define OUTPUT_BUFFER_SIZE 1024

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{

   if( argc >= 2 && std::strcmp( argv[1], "-h" ) == 0 ){
        std::cout << "usage: entoptic [hostname [port]]\n";
        return 0;
    }

    const char *address = "127.0.0.1";
    if( argc >= 2 )
        address = argv[1];

    int port = 7000;
    if( argc >= 3 )
        port = std::atoi( argv[2] );

    // OSC setup
    (void) argc; // suppress unused parameter warnings
    (void) argv; // suppress unused parameter warnings
    UdpTransmitSocket transmitSocket( IpEndpointName( address, port ) );
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );



     VideoCapture cap(0); // open the video camera no. 0

     if (!cap.isOpened())  // if not success, exit program
     {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }

    double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    cout << "Frame size : " << dWidth << " x " << dHeight << endl;

    namedWindow("MyVideo",WINDOW_AUTOSIZE); //create a window called "MyVideo"

    while (1)
    {
        Mat frame;
        bool bSuccess = cap.read(frame); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

        imshow("MyVideo", frame); //show the frame in "MyVideo" window


        // OSC stuff
        p.Clear();
        p << osc::BeginBundleImmediate << osc::BeginMessage( "/test1" ) 
            << true << 23 << (float)3.1415 << "hello" << osc::EndMessage
        << osc::BeginMessage( "/test2" ) 
            << true << 24 << (float)10.8 << "world" << osc::EndMessage
        << osc::EndBundle;
    
        transmitSocket.Send( p.Data(), p.Size() );



        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break; 
       }
    }
    return 0;

}
