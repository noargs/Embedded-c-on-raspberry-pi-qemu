**A target system:** (i.e. ARM) The system your code is going to run on. (We use QEMU to emulate Raspberry pi board.)
    
- Change the directory to `pi` folder i.e. `cd ~/Embedded-c/pi` in the terminal and run following command
```sh
$ qemu-system-arm -M versatilepb -dtb versatile-pb.dtb -cpu arm1176 -kernel kernel-qemu-4.14.79-stretch -m 256 -drive file=2019-07-10-raspbian-buster-lite.img,format=raw -append "rw console=ttyAMA0 rootfstype=ext4 root=/dev/sda2 loglevel=8" -net user,hostfwd=tcp::22023-:22,hostfwd=tcp::2200-:2200 -net nic -serial stdio & 
```   
- Dont forget to download [2019-07-10-raspbian-buster-lite.zip](http://downloads.raspberrypi.org/raspbian_lite/images/raspbian_lite-2019-07-12/2019-07-10-raspbian-buster-lite.zip) and extract the zip file (i.e. .img file) into `~/Embedded-c/pi` in order for above command to work properly 
- A new window will appear, displaying the Linux boot process and few seconds later a login prompt
- Log in using `pi` as the username and `raspberry` as the password.
- Run following command and it will displays the architecutre as _ARM_ not _x86_ (our target system, Emulated Raspberry pi board)
```sh
$ uname -a
```      
      
```
Embedded-c  
│   
├── pi
│   ├── 2019-07-10-raspbian-buster-lite.img (Linux root filesytem)
│   ├── kernel-qemu-4.14.79-stretch (Linux kernel)
│   ├── versatile-pb.dtb (Device tree blob)
│
├+- projects
│
├── README.md
└── .gitignore
```     
 