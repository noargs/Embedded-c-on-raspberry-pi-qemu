cmake_minimum_required(VERSION 3.5.1)
project(02_fixedtypes)
add_executable(fixedtypes fixedtypes.cpp)


set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CXX_FLAGS "--std=c++11")
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)