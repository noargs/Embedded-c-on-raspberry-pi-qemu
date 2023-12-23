Contain projects for **A target system:** (i.e. ARM) The system your code is going to run on. (We use QEMU to emulate Raspberry pi board.)
    
1. Start previously created container `$ docker start <container-name/ID>` 
2. Login to the interactive shell `$ docker exec -ti <container-name/ID> bash`
3. Run following command to make sure cross-compiler is working fine `arm-linux-gnueabi-g++`    
4. Change the directory to **/mnt/projects/<project-name>** by running `# cd /mnt/projects/<project-name>`
      
```
Embedded-c  
│   
├-+ pi
│
├── projects
│   ├── 00_project
│   ├── 01_project
│   ├── 02_project
│   ├── 03_ ...
│
├── README.md
└── .gitignore
```     
 