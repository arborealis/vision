include_directories(ip)
include_directories(osc)

IF(WIN32)
 set(IpSystemTypePath ip/win32)
 set(LIBS ${LIBS} Ws2_32 winmm)
ELSE(WIN32)
 set(IpSystemTypePath ip/posix)
ENDIF(WIN32)

ADD_LIBRARY(oscpack 
ip/IpEndpointName.h
ip/IpEndpointName.cpp
ip/NetworkingUtils.h
${IpSystemTypePath}/NetworkingUtils.cpp
ip/UdpSocket.h
${IpSystemTypePath}/UdpSocket.cpp
ip/PacketListener.h
ip/TimerListener.h
osc/OscTypes.h
osc/OscTypes.cpp 
osc/OscHostEndianness.h
osc/OscException.h
osc/OscPacketListener.h
osc/MessageMappingOscPacketListener.h
osc/OscReceivedElements.h
osc/OscReceivedElements.cpp
osc/OscPrintReceivedElements.h
osc/OscPrintReceivedElements.cpp
osc/OscOutboundPacketStream.h
osc/OscOutboundPacketStream.cpp
)	


