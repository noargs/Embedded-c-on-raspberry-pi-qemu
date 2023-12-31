After an embedded application is built on a build system (Ubuntu running on docker container) using a cross-compiler, it should be transferred to the target system (Raspberry pi running on Qemu). The best way to do this on Linux-based embedded systems is by using networking connectivity and a remote shell (_Secure shell SSH_). We will copy the application binary `hello` to emulated ARM system (Raspberry pi on Qemu) using secure copy, connect to it using SSH, and run the executable in SSH.

1. Change the directory to **/mnt/projects/01_connect_with_raspberry** by running `# cd /mnt/projects/01_connect_with_raspberry` on Ubuntu (running in docker container)
2. Build the **hello.cpp** file with `# arm-linux-gnueabi-g++ hello.cpp -o hello`
3. Find out the ip address of your machine (Not Ubuntu or Raspberry pi), Run `ifconfig` on macOS, or Linux, or `ipconfig` for Windows.
4. Assume 192.168.1.1 as a template IP address (you should replace this with your actual IP address)
5. Switch to Raspberry pi emulator and enable SSH services (i.e. SSH Server) by running `$ sudo systemctl start ssh`
6. Switch to Ubuntu and install SSH client `# apt install -y ssh`
7. Now, we can copy the `hello` executable to the target system (i.e. Raspberry pi) on Ubuntu by `# scp -P22040 /mnt/projects/01_connect_with_raspberry/hello pi@192.168.1.1:~`
8. When asked for password, type `raspberry`. Switch back to Raspberry pi emulator window. Confirm the executable we just copied `$ ls hello`
9. Now, run the program `$ ./hello`

   
* Start previously created container `$ docker start <container-name/ID>` and Login to the interactive shell `$ docker exec -ti <container-name/ID> bash`  


### Debuging embedded applications (gdb and gdbserver)
Debugging embedded applications depends upon target embedded system. MCU manufacturers often provide specialised debuggers for their MCU as well as hardware support for remote debugging using a **Joint Test Action Group (JTAG)** protocol. It will allow to debug the microcontroller code immediatley after MCU starts executing instructions.    
If the target board runs linux, often used practical method of debugging is to use an extensive debug output and to use **GDB** as an interactive debugger.     

1. Switch to QEMU (Raspberry pi) window and run `$ gdb ./hello` 
2. It will open the _gdb_ command line and type _run_ to run the application `(gdb) run`
3. Now, run the _quit_, or just _q_ `(gdb) q`

The environment for embedded development usually involves two systems — a _build system_ (Ubuntu on docker in our case) and a _target system_ (Raspberry Pi on emulator). Sometimes, interactive debugging on the target system is impractical because of the high latency of remote communication.    

In such situations, developers can use remote debugging support provided by GDB. In this setup, an embedded application is launched on the target system using **gdbserver**. Developers run GDB on a build system and connect to gdbserver over the network.

1. Log in as _pi_ using the _raspberry_ password, unless you're already logged in.
2. To install gdbserver, run the following command: `# sudo apt-get install gdbserver`
3. Run the hello application under gdbserver: `$ gdbserver 0.0.0.0:9090 ./hello`
4. Switch to the build system terminal and change the directory to `/mnt/projects/01_connect_with_raspberry`: `# cd /mnt//projects/01_connect_with_raspberry`
5. Install the _gdb-multiarch_ package, which provides the necessary support for the ARM platform: `# apt install -y gdb-multiarch`
6. Next, run _gdb_: `# gdb-multiarch -q ./hello`
7. Configure the remote connection by typing the following command in the gdb command line (make sure you replace 192.168.1.1 with your actual IP address): `target remote 192.168.1.1:9090`
8. Type the following command: `continue`

The program will now run.

### Using CMake as a build system
Real applications, usually have a more complex structure. They can contain multiple source files, depend on other libraries, and be split into independent projects.
We need a way to conveniently define build rules for any type of application. CMake is one of the most well-known and widely used tools that allow developers to define high-level rules and translate them into a lower-level build system, such as a Unix make

1. Change the directory to **/mnt/projects/01_connect_with_raspberry** by running `# cd /mnt/projects/01_connect_with_raspberry` on Ubuntu (running in docker container)

2. Install **CMake** in your build system `# apt install -y cmake`

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
7. Now, we can copy the `hello` executable present in the _build_ folder, to the target system (i.e. Raspberry pi), on the Ubuntu by `# scp -P22040 /mnt/projects/01_connect_with_raspberry/build/hello pi@192.168.1.1:~/hello`
8. When asked for password, type `raspberry`. Switch back to Raspberry pi emulator window. Confirm the executable we just copied `$ ls ~`
9. Now, run the program `$ ./hello`

   
* Start previously created container `$ docker start <container-name/ID>` and Login to the interactive shell `$ docker exec -ti <container-name/ID> bash` 
* If encountered with an error _Connection closed by remote host_ then don't forget to enable SSH services (i.e. SSH Server) on target system (i.e. Rasberry pi on Qemu), by running `$ sudo systemctl start ssh`, if Qemu was shut and recently started again.
* If encountered with error _Could not set up host forwarding rule_ then try to change the _tcp_ ports with different port numbers

