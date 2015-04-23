#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>


#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"


#define OUTPUT_BUFFER_SIZE 1024 * 4


int main(int argc, char* argv[]) {

    if (argc >= 2 && std::strcmp(argv[1], "-h") == 0) {
        std::cout << "usage: entoptic [hostname [port]]"<<std::endl;
        return 0;
    }

    const char* address = "127.0.0.1";
    //if (argc >= 2)
      //  address = argv[1];

    int port = 7000;
    //if (argc >= 3)
        //port = std::atoi(argv[2]);

    // OSC setup
    UdpTransmitSocket transmitSocket(IpEndpointName(address, port));
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);
    std::string osc_address_str;
    std::string gridData;
    float activation;

     char c;
     std::cout<<"press ctl-c to quit "<<std::endl;
    int frame = 0;
    while (true) {

        // OSC stuff
        if (frame == 0) {
            gridData = "";
            for (int i = 1; i < 21; ++i)
            {
                for (int j = 1; j < 11; ++j)
                {
                    activation = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

                    if (activation < .9) {
                        gridData += "0,";
                    } 
                    else {
                        gridData += std::to_string(activation) + ",";
                    }
                    
                }
            }
        }

        p.Clear();
        p << osc::BeginMessage("/A/C1") 
            << gridData.substr(0, gridData.size()-1).c_str()
            << osc::EndMessage;
        
        

        transmitSocket.Send(p.Data(), p.Size());

         
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        ++frame;
        if (frame >= 50) 
            frame = 0;
    }
    std::cout<<"exited: "<<std::endl;
    return 0;
}
