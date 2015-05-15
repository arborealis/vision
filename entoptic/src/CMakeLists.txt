FILE (GLOB_RECURSE project_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)

SET (project_MOC_HEADERS app.h)
SET (project_LIBS ${OpenCV_LIBS} )
SET (project_BIN ${PROJECT_NAME})


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


ADD_EXECUTABLE(${project_BIN} ${project_SRCS} ${project_MOC_SRCS_GENERATED})
TARGET_LINK_LIBRARIES(${project_BIN} ${project_LIBS})
SET_TARGET_PROPERTIES(${project_BIN} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${project_BIN} CLEAN_DIRECT_OUTPUT 1)

INSTALL(TARGETS ${project_BIN} DESTINATION bin)
