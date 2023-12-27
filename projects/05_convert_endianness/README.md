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
add_executable(sender sender.cpp)
add_executable(receiver receiver.cpp)


set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CXX_FLAGS "--std=c++14")
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)
```

3. Run CMake `# mkdir build && cd build && cmake ..` and build applicationn by running `# make`
4. Switch to Ubuntu and install SSH client `# apt install -y ssh`
5. Now, we can copy the `sender` and `receiver` executable in the _build_ folder, to the target system (i.e. Raspberry pi), on the Ubuntu by `# scp -P22040 /mnt/projects/05_convert_endianness/build/sender pi@192.168.1.1:~/sender` and simillary `# scp -P22040 /mnt/projects/05_convert_endianness/build/receiver pi@192.168.1.1:~/receiver`
6. When asked for password, type `raspberry`. Switch back to Raspberry pi emulator window. Confirm the executable we just copied `$ ls ~`
7. Now, run the _sender_ binary and pass two command-line arguments (_Hello_ and _World!_): `$ ./sender "Hello "` and `$ ./sender "World!"`. This won't generate any ouput
8. Now, run the receiver `$ ./receiver`
9. Now, check the content of the file (i.e. _envconv.data_). It will be in binary format. Hence we need _xxd_ tool to convert it into hexadecimal format:
```bash
$ xxd envconv.data
0000000: 0000 0006 4865 6c6c 6f20 0000 0006 576f ....Hello ....Wo
0000010: 726c 6421                               rld!
```

10. The file contains two strings, hello and world, prepended by their sizes. The size fields are always stored in big-endian byte order, independent of the architecture. This allows the sender and the receiver to be run on two different machines with different endianness.

   
* Start previously created container `$ docker start <container-name/ID>` and Login to the interactive shell `$ docker exec -ti <container-name/ID> bash` 
* If encountered with an error _Connection closed by remote host_ then don't forget to enable SSH services (i.e. SSH Server) on target system (i.e. Rasberry pi on Qemu), by running `$ sudo systemctl start ssh`, if Qemu was shut and recently started again.
* If encountered with error _Could not set up host forwarding rule_ then try to change the _tcp_ ports with different port numbers


