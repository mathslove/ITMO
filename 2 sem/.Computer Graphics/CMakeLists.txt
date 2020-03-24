cmake_minimum_required(VERSION 3.15)
project(lab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(lab1 main.cpp pnm.cpp pnm.h)