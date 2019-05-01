cmake_minimum_required(VERSION 3.13)
project(OSProject2 CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(OSProject2 src/main.cpp src/process.cpp include/process.h include/cpu.h src/cpu.cpp include/runqueue.h
        src/runqueue.cpp include/memory/common.h)
target_include_directories(OSProject2 PRIVATE include)