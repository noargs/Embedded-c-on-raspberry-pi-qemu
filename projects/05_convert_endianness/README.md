While serialization libraries deal with the endianness under the hood, there are situations where developers might want to implement a lightweight communication protocol themselves.
While the C++ Standard Library does not provide functions for serialization, developers may utilize the fact that, in binary network protocols, byte order is defined and is always big-endian.
  
The Standard Library provides a set of functions that can be used for conversion between the current platform (hardware) and big-endian (network) byte orders:

* uint32_t **htonl** (uint32_t value): Converts uint32_t from hardware to network order
* uint32_t **ntohl** (uint32_t value): Converts uint32_t from network to hardware order
* uint16_t **htons** (uint16_t value): Converts uint16_t from hardware to network order
* uint16_t **ntohl** (uint16_t value): Converts uint16_t from network to hardware order

Developers can use these functions to exchange binary data between applications running on different platforms.

* 05_convert_endianness app, we will learn how to encode strings so that they can be exchanged between two systems that may have the same or different endianness 

1. Change the directory to **/mnt/projects/05_convert_endianness** by running `# cd /mnt/projects/05_convert_endianness` on Ubuntu (running in docker container)

2. `CMakeLists.txt` contains following contents.
```make
cmake_minimum_required(VERSION 3.5.1)
project(05_convert_endianness)
add_executable(convert_endianness convert_endianness.cpp)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CXX_FLAGS "--std=c++11")
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)
```

3. Run CMake `# mkdir build && cd build && cmake ..` and build applicationn by running `# make`
4. Switch to Ubuntu and install SSH client `# apt install -y ssh`
5. Now, we can copy the `05_convert_endianness` executable in the _build_ folder, to the target system (i.e. Raspberry pi), on the Ubuntu by `# scp -P22040 /mnt/projects/05_convert_endianness/build/convert_endianness pi@192.168.1.1:~/05_convert_endianness`
6. When asked for password, type `raspberry`. Switch back to Raspberry pi emulator window. Confirm the executable we just copied `$ ls ~`
7. Now, run the program `$ ./05_convert_endianness`

   
* Start previously created container `$ docker start <container-name/ID>` and Login to the interactive shell `$ docker exec -ti <container-name/ID> bash` 
* If encountered with an error _Connection closed by remote host_ then don't forget to enable SSH services (i.e. SSH Server) on target system (i.e. Rasberry pi on Qemu), by running `$ sudo systemctl start ssh`, if Qemu was shut and recently started again.
* If encountered with error _Could not set up host forwarding rule_ then try to change the _tcp_ ports with different port numbers


