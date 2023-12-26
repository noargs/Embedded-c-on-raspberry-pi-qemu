After an embedded application is built on a build system (Ubuntu running on docker container) using a cross-compiler, it should be transferred to the target system (Raspberry pi running on Qemu). The best way to do this on Linux-based embedded systems is by using networking connectivity and a remote shell (_Secure shell SSH_). We will copy the application binary `02_fixedtypes_cmake` to emulated ARM system (Raspberry pi on Qemu) using secure copy, connect to it using SSH, and run the executable in SSH.

1. Change the directory to **/mnt/projects/02_fixedtypes_cmake** by running `# cd /mnt/projects/02_fixedtypes_cmake` on Ubuntu (running in docker container)

2. Create the **fixedtypes.cpp** file and install **CMake** in your build system `# apt install -y cmake`

3. Create CMakeLists.txt with following contents.
```make
cmake_minimum_required(VERSION 3.5.1)
project(fixedtypes_cmake)
add_executable(fixed_types fixed_types.cpp)
```

4. Running cmake command will generate binary for x86. However we need to add cross-compilation support.
```make
set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabi-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
project(fixed_types_cmake)
add_executable(fixed_types fixed_types.cpp)
```

5. Run CMake `# mkdir build && cd build && cmake ..` and build applicationn by running `# make`
6. Switch to Ubuntu and install SSH client `# apt install -y ssh`
7. Now, we can copy the `fixedtypes` executable in the _build_ folder, to the target system (i.e. Raspberry pi), on the Ubuntu by `# scp -P22040 /mnt/projects/02_fixedtypes_cmake/build/fixedtypes pi@192.168.1.1:~/02_fixedtypes_cmake`
8. When asked for password, type `raspberry`. Switch back to Raspberry pi emulator window. Confirm the executable we just copied `$ ls ~`
9. Now, run the program `$ ./02_fixedtypes_cmake`

   
* Start previously created container `$ docker start <container-name/ID>` and Login to the interactive shell `$ docker exec -ti <container-name/ID> bash` 
* If encountered with an error _Connection closed by remote host_ then don't forget to enable SSH services (i.e. SSH Server) on target system (i.e. Rasberry pi on Qemu), by running `$ sudo systemctl start ssh`, if Qemu was shut and recently started again.
* If encountered with error _Could not set up host forwarding rule_ then try to change the _tcp_ ports with different port numbers
