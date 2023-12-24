After an embedded application is built on a build system (Ubuntu running on docker container) using a cross-compiler, it should be transferred to the target system (Raspberry pi running on Qemu). The best way to do this on Linux-based embedded systems is by using networking connectivity and a remote shell (_Secure shell SSH_). We will copy the application binary `hello` to emulated ARM system (Raspberry pi on Qemu) using secure copy, connect to it using SSH, and run the executable in SSH.

1. Change the directory to **/mnt/projects/01_connect_with_raspberry** by running `# cd /mnt/projects/01_connect_with_raspberry` on Ubuntu (running in docker container)
2. Build the **hello.cpp** file with `# arm-linux-gnueabi-g++ hello.cpp -o hello`
3. Find out the ip address of your machine (Not Ubuntu or Raspberry pi), Run `ifconfig` on macOS, or Linux, or `ipconfig` for Windows.
4. Assume 192.168.1.1 as a template IP address (you should replace this with your actual IP address)
5. Switch to Raspberry pi emulator and enable SSH services (i.e. SSH Server) by running `$ sudo systemctl start ssh`
6. Switch to Ubuntu and install SSH client `# apt install -y ssh`
7. Now, we can copy the `hello` executable to the target system (i.e. Raspberry pi) on Ubuntu by `# scp -P22023 /mnt/projects/01_connect_with_raspberry/hello pi@192.168.1.1:~`
8. When asked for password, type `raspberry`. Switch back to Raspberry pi emulator window. Confirm the executable we just copied `$ ls hello`
9. Now, run the program `$ ./hello`

   
* Start previously created container `$ docker start <container-name/ID>` and Login to the interactive shell `$ docker exec -ti <container-name/ID> bash`     
