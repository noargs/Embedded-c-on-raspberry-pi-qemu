Endianness defines the _order_ in which bytes that represent large numerical values are stored in memory.

There are two types of endianness:   

* **Big-endian**: The most significant byte is store first. A 32-bit value, `0x01020304`, is stored at the _ptr_ address, as follows:

| Offset in memory (byte)   |  Value   |
|:--------------------------|:--------:|
| ptr                       |  0x01    |
| ptr + 1                   |  0x02    |
| ptr + 2                   |  0x03    |
| ptr + 4                   |  0x04    |

Examples of big-endian architectures include AVR32 and Motorola 68000.

* **Little-endian**: The least significant byte is store first. A 32-bit value, `0x01020304`, is stored at the _ptr_ address, as follows:

| Offset in memory (byte)   |  Value   |
|:--------------------------|:--------:|
| ptr                       |  0x04    |
| ptr + 1                   |  0x03    |
| ptr + 2                   |  0x02    |
| ptr + 4                   |  0x01    |

The x86 architecture is little-endian.

1. Change the directory to **/mnt/projects/04_endianness** by running `# cd /mnt/projects/04_endianness` on Ubuntu (running in docker container)

2. `CMakeLists.txt` contains following contents.
```make
cmake_minimum_required(VERSION 3.5.1)
project(04_endianness)
add_executable(endianness endianness.cpp)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CXX_FLAGS "--std=c++11")
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)
```

3. Run CMake `# mkdir build && cd build && cmake ..` and build applicationn by running `# make`
4. Switch to Ubuntu and install SSH client `# apt install -y ssh`
5. Now, we can copy the `04_endianness` executable in the _build_ folder, to the target system (i.e. Raspberry pi), on the Ubuntu by `# scp -P22040 /mnt/projects/04_endianness/build/endianness pi@192.168.1.1:~/04_endianness`
6. When asked for password, type `raspberry`. Switch back to Raspberry pi emulator window. Confirm the executable we just copied `$ ls ~`
7. Now, run the program `$ ./04_endianness`

   
* Start previously created container `$ docker start <container-name/ID>` and Login to the interactive shell `$ docker exec -ti <container-name/ID> bash` 
* If encountered with an error _Connection closed by remote host_ then don't forget to enable SSH services (i.e. SSH Server) on target system (i.e. Rasberry pi on Qemu), by running `$ sudo systemctl start ssh`, if Qemu was shut and recently started again.
* If encountered with error _Could not set up host forwarding rule_ then try to change the _tcp_ ports with different port numbers

