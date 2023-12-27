C and C++ developers often forget that the size of fundamental data types such as char, short, and int are architecture-dependent. At the same time, most of the hardware peripherals define specific requirements regarding the size of the fields that are used for data exchanges. To make the code working with the external hardware or communication protocols portable, embedded developers use fixed-size integer types, which explicitly specify the size of a data field

| Width    |  Signed  | Unsigned |
|:---------|:--------:|---------:|
| 8-bit    | int8_t   | uint8_t  |
| 16-bit   | int16_t  | uint16_t |
| 32-bit   | int32_t  | uint32_t |

1. Change the directory to **/mnt/projects/02_fixedtypes_cmake** by running `# cd /mnt/projects/02_fixedtypes_cmake` on Ubuntu (running in docker container)

2. Create the **fixedtypes.cpp** file and create `CMakeLists.txt` with following contents.
```make
cmake_minimum_required(VERSION 3.5.1)
project(fixedtypes_cmake)
add_executable(fixedtypes fixedtypes.cpp)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CXX_FLAGS "--std=c++11")
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)
```

3. Run CMake `# mkdir build && cd build && cmake ..` and build applicationn by running `# make`
4. Switch to Ubuntu and install SSH client `# apt install -y ssh`
5. Now, we can copy the `02_fixedtypes_cmake` executable in the _build_ folder, to the target system (i.e. Raspberry pi), on the Ubuntu by `# scp -P22040 /mnt/projects/02_fixedtypes_cmake/build/fixedtypes pi@192.168.1.1:~/02_fixedtypes_cmake`
6. When asked for password, type `raspberry`. Switch back to Raspberry pi emulator window. Confirm the executable we just copied `$ ls ~`
7. Now, run the program `$ ./02_fixedtypes_cmake`

   
* Start previously created container `$ docker start <container-name/ID>` and Login to the interactive shell `$ docker exec -ti <container-name/ID> bash` 
* If encountered with an error _Connection closed by remote host_ then don't forget to enable SSH services (i.e. SSH Server) on target system (i.e. Rasberry pi on Qemu), by running `$ sudo systemctl start ssh`, if Qemu was shut and recently started again.
* If encountered with error _Could not set up host forwarding rule_ then try to change the _tcp_ ports with different port numbers
