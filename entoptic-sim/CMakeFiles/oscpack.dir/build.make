# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dsel/code/vision/entoptic-sim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dsel/code/vision/entoptic-sim

# Include any dependencies generated for this target.
include CMakeFiles/oscpack.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/oscpack.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/oscpack.dir/flags.make

CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.o: CMakeFiles/oscpack.dir/flags.make
CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.o: ip/IpEndpointName.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dsel/code/vision/entoptic-sim/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.o -c /home/dsel/code/vision/entoptic-sim/ip/IpEndpointName.cpp

CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dsel/code/vision/entoptic-sim/ip/IpEndpointName.cpp > CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.i

CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dsel/code/vision/entoptic-sim/ip/IpEndpointName.cpp -o CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.s

CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.o.requires:
.PHONY : CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.o.requires

CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.o.provides: CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.o.requires
	$(MAKE) -f CMakeFiles/oscpack.dir/build.make CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.o.provides.build
.PHONY : CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.o.provides

CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.o.provides.build: CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.o

CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.o: CMakeFiles/oscpack.dir/flags.make
CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.o: ip/posix/NetworkingUtils.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dsel/code/vision/entoptic-sim/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.o -c /home/dsel/code/vision/entoptic-sim/ip/posix/NetworkingUtils.cpp

CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dsel/code/vision/entoptic-sim/ip/posix/NetworkingUtils.cpp > CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.i

CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dsel/code/vision/entoptic-sim/ip/posix/NetworkingUtils.cpp -o CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.s

CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.o.requires:
.PHONY : CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.o.requires

CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.o.provides: CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.o.requires
	$(MAKE) -f CMakeFiles/oscpack.dir/build.make CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.o.provides.build
.PHONY : CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.o.provides

CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.o.provides.build: CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.o

CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.o: CMakeFiles/oscpack.dir/flags.make
CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.o: ip/posix/UdpSocket.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dsel/code/vision/entoptic-sim/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.o -c /home/dsel/code/vision/entoptic-sim/ip/posix/UdpSocket.cpp

CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dsel/code/vision/entoptic-sim/ip/posix/UdpSocket.cpp > CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.i

CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dsel/code/vision/entoptic-sim/ip/posix/UdpSocket.cpp -o CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.s

CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.o.requires:
.PHONY : CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.o.requires

CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.o.provides: CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.o.requires
	$(MAKE) -f CMakeFiles/oscpack.dir/build.make CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.o.provides.build
.PHONY : CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.o.provides

CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.o.provides.build: CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.o

CMakeFiles/oscpack.dir/osc/OscTypes.cpp.o: CMakeFiles/oscpack.dir/flags.make
CMakeFiles/oscpack.dir/osc/OscTypes.cpp.o: osc/OscTypes.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dsel/code/vision/entoptic-sim/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/oscpack.dir/osc/OscTypes.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/oscpack.dir/osc/OscTypes.cpp.o -c /home/dsel/code/vision/entoptic-sim/osc/OscTypes.cpp

CMakeFiles/oscpack.dir/osc/OscTypes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oscpack.dir/osc/OscTypes.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dsel/code/vision/entoptic-sim/osc/OscTypes.cpp > CMakeFiles/oscpack.dir/osc/OscTypes.cpp.i

CMakeFiles/oscpack.dir/osc/OscTypes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oscpack.dir/osc/OscTypes.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dsel/code/vision/entoptic-sim/osc/OscTypes.cpp -o CMakeFiles/oscpack.dir/osc/OscTypes.cpp.s

CMakeFiles/oscpack.dir/osc/OscTypes.cpp.o.requires:
.PHONY : CMakeFiles/oscpack.dir/osc/OscTypes.cpp.o.requires

CMakeFiles/oscpack.dir/osc/OscTypes.cpp.o.provides: CMakeFiles/oscpack.dir/osc/OscTypes.cpp.o.requires
	$(MAKE) -f CMakeFiles/oscpack.dir/build.make CMakeFiles/oscpack.dir/osc/OscTypes.cpp.o.provides.build
.PHONY : CMakeFiles/oscpack.dir/osc/OscTypes.cpp.o.provides

CMakeFiles/oscpack.dir/osc/OscTypes.cpp.o.provides.build: CMakeFiles/oscpack.dir/osc/OscTypes.cpp.o

CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.o: CMakeFiles/oscpack.dir/flags.make
CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.o: osc/OscReceivedElements.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dsel/code/vision/entoptic-sim/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.o -c /home/dsel/code/vision/entoptic-sim/osc/OscReceivedElements.cpp

CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dsel/code/vision/entoptic-sim/osc/OscReceivedElements.cpp > CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.i

CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dsel/code/vision/entoptic-sim/osc/OscReceivedElements.cpp -o CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.s

CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.o.requires:
.PHONY : CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.o.requires

CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.o.provides: CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.o.requires
	$(MAKE) -f CMakeFiles/oscpack.dir/build.make CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.o.provides.build
.PHONY : CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.o.provides

CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.o.provides.build: CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.o

CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.o: CMakeFiles/oscpack.dir/flags.make
CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.o: osc/OscPrintReceivedElements.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dsel/code/vision/entoptic-sim/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.o -c /home/dsel/code/vision/entoptic-sim/osc/OscPrintReceivedElements.cpp

CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dsel/code/vision/entoptic-sim/osc/OscPrintReceivedElements.cpp > CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.i

CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dsel/code/vision/entoptic-sim/osc/OscPrintReceivedElements.cpp -o CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.s

CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.o.requires:
.PHONY : CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.o.requires

CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.o.provides: CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.o.requires
	$(MAKE) -f CMakeFiles/oscpack.dir/build.make CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.o.provides.build
.PHONY : CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.o.provides

CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.o.provides.build: CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.o

CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.o: CMakeFiles/oscpack.dir/flags.make
CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.o: osc/OscOutboundPacketStream.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dsel/code/vision/entoptic-sim/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.o -c /home/dsel/code/vision/entoptic-sim/osc/OscOutboundPacketStream.cpp

CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dsel/code/vision/entoptic-sim/osc/OscOutboundPacketStream.cpp > CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.i

CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dsel/code/vision/entoptic-sim/osc/OscOutboundPacketStream.cpp -o CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.s

CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.o.requires:
.PHONY : CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.o.requires

CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.o.provides: CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.o.requires
	$(MAKE) -f CMakeFiles/oscpack.dir/build.make CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.o.provides.build
.PHONY : CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.o.provides

CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.o.provides.build: CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.o

# Object files for target oscpack
oscpack_OBJECTS = \
"CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.o" \
"CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.o" \
"CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.o" \
"CMakeFiles/oscpack.dir/osc/OscTypes.cpp.o" \
"CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.o" \
"CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.o" \
"CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.o"

# External object files for target oscpack
oscpack_EXTERNAL_OBJECTS =

liboscpack.a: CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.o
liboscpack.a: CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.o
liboscpack.a: CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.o
liboscpack.a: CMakeFiles/oscpack.dir/osc/OscTypes.cpp.o
liboscpack.a: CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.o
liboscpack.a: CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.o
liboscpack.a: CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.o
liboscpack.a: CMakeFiles/oscpack.dir/build.make
liboscpack.a: CMakeFiles/oscpack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library liboscpack.a"
	$(CMAKE_COMMAND) -P CMakeFiles/oscpack.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/oscpack.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/oscpack.dir/build: liboscpack.a
.PHONY : CMakeFiles/oscpack.dir/build

CMakeFiles/oscpack.dir/requires: CMakeFiles/oscpack.dir/ip/IpEndpointName.cpp.o.requires
CMakeFiles/oscpack.dir/requires: CMakeFiles/oscpack.dir/ip/posix/NetworkingUtils.cpp.o.requires
CMakeFiles/oscpack.dir/requires: CMakeFiles/oscpack.dir/ip/posix/UdpSocket.cpp.o.requires
CMakeFiles/oscpack.dir/requires: CMakeFiles/oscpack.dir/osc/OscTypes.cpp.o.requires
CMakeFiles/oscpack.dir/requires: CMakeFiles/oscpack.dir/osc/OscReceivedElements.cpp.o.requires
CMakeFiles/oscpack.dir/requires: CMakeFiles/oscpack.dir/osc/OscPrintReceivedElements.cpp.o.requires
CMakeFiles/oscpack.dir/requires: CMakeFiles/oscpack.dir/osc/OscOutboundPacketStream.cpp.o.requires
.PHONY : CMakeFiles/oscpack.dir/requires

CMakeFiles/oscpack.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/oscpack.dir/cmake_clean.cmake
.PHONY : CMakeFiles/oscpack.dir/clean

CMakeFiles/oscpack.dir/depend:
	cd /home/dsel/code/vision/entoptic-sim && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dsel/code/vision/entoptic-sim /home/dsel/code/vision/entoptic-sim /home/dsel/code/vision/entoptic-sim /home/dsel/code/vision/entoptic-sim /home/dsel/code/vision/entoptic-sim/CMakeFiles/oscpack.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/oscpack.dir/depend
