1. Start previously created container `$ docker start <container-name/ID>` 
2. Login to the interactive shell `$ docker exec -ti <container-name/ID> bash`
3. Run following command to make sure cross-compiler is working fine `arm-linux-gnueabi-g++`
4. Change the directory to **/mnt/projects/00_helloworld** by running `# cd /mnt/projects/00_hellowrold`
5. Build the **hello.cpp** file with `# arm-linux-gnueabi-g++ hello.cpp -o hello`
6. You can generate the details about the executable binary using the `# file hello` tool.   
     
