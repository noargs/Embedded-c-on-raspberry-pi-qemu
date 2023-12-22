### Embedded C++ with Virtual Raspberry pi on QEMU

* **A build system:** (i.e. x86) The system you use to write the code. (We use Docker to run Ubuntu in a virtualise environment on our computer.) 
* **A target system:** (i.e. ARM) The system your code is going to run on. (We use QEMU to emulate Raspberry pi board.)

##### Download / Install Docker    

> https:/​/​docs.​docker.​com/​docker-​for-​mac/​install
1. Confirm the installation `$ docker --version`
2. Run the command to use an Ubuntu image `$ docker pull ubuntu:bionic`
3. Create workspace folder `$ mkdir ~/Embedded-c`
4. Now, run the downloaded image in the container `$ docker run -ti -v $HOME/Embedded-c/projects:/mnt ubuntu:bionic`
5. Next, run following command to get the information about the system: `# uname -a`    
      
            
* `$HOME/Embedded-c/projects:/mnt` on _step 4_ means whatever we put inside `~/Embedded-c/projects` folder, will appear in `/mnt` folder of Linux (i.e. Ubuntu) running inside Docker container.
- Start/Stop previously created container `$ docker start <container-name/ID>` and `$ docker stop <container-name/ID>`. Then you can login to the interactive shell `$ docker exec -ti <container-name/ID> bash`

##### Download / Install Qemu       

> https:/​/​www.​qemu.​org/​download/

1. Download [2019-07-10-raspbian-buster-lite.zip](http://downloads.raspberrypi.org/raspbian_lite/images/raspbian_lite-2019-07-12/2019-07-10-raspbian-buster-lite.zip) and place this zip file into `~/Embedded-c/pi` 
2. Change the directory to `pi` folder i.e. `cd ~/Embedded-c/pi` in the terminal and run following command
```sh
$ qemu-system-arm -M versatilepb -dtb versatile-pb.dtb -cpu arm1176 -kernel kernel-qemu-4.14.79-stretch -m 256 -drive file=2019-07-10-raspbian-buster-lite.img,format=raw -append "rw console=ttyAMA0 rootfstype=ext4 root=/dev/sda2 loglevel=8" -net user,hostfwd=tcp::22023-:22,hostfwd=tcp::9090-:9090 -net nic -serial stdio & 
```   

3. A new window will appear, displaying the Linux boot process and few seconds later a login prompt
4. Log in using `pi` as the username and `raspberry` as the password.
5. Run following command and it will displays the architecutre as _ARM_ not _x86_ (our target system, Emulated Raspberry pi board)
```sh
$ uname -a
```      
      
			
Assume our workspace folder name is `Embedded-c` as created above which further contain two folders as follows:      

```
**Embedded-c**   
│   
├── **pi**
│   ├── Linux root filesytem: _2019-07-10-raspbian-buster-lite.zip_
│   ├── Linux kernel: _kernel-qemu-4.14.79-stretch_
│   ├── Device tree blob: _versatile-pb.dtb_
├── **projects**
│   ├── 00_project
│   ├── 01_project
│   ├── 02_project
│   ├── 03_ ...
├── README.md
└── .gitignore
```