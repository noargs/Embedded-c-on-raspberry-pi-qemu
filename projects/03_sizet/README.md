The pointer size also depends on the architecture. Developers often need to address the elements of arrays, and, since arrays are internally represented as pointers, the offset representation depends on the pointer's size.
For example, in a 32-bit system, pointers are 32-bit, the same as _int_. However, in a 64-bit system, the size of _int_ is still 32-bit, while pointers are 64-bit.
**size_t** is a special data type since it represents offset and data sizes in an architecture- independent way.

1. Change the directory to **/mnt/projects/03_sizet** by running `# cd /mnt/projects/02_fixedtypes_cmake` on Ubuntu (running in docker container)

2. Create the **sizet.cpp** file and create `CMakeLists.txt` with following contents.
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
5. Now, we can copy the `03_sizet` executable in the _build_ folder, to the target system (i.e. Raspberry pi), on the Ubuntu by `# scp -P22040 /mnt/projects/03_sizet/build/sizet pi@192.168.1.1:~/03_sizet`
6. When asked for password, type `raspberry`. Switch back to Raspberry pi emulator window. Confirm the executable we just copied `$ ls ~`
7. Now, run the program `$ ./03_sizet`

   
* Start previously created container `$ docker start <container-name/ID>` and Login to the interactive shell `$ docker exec -ti <container-name/ID> bash` 
* If encountered with an error _Connection closed by remote host_ then don't forget to enable SSH services (i.e. SSH Server) on target system (i.e. Rasberry pi on Qemu), by running `$ sudo systemctl start ssh`, if Qemu was shut and recently started again.
* If encountered with error _Could not set up host forwarding rule_ then try to change the _tcp_ ports with different port numbers
