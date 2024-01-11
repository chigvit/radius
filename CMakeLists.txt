cmake_minimum_required(VERSION 3.27)
project(radius)

set(CMAKE_CXX_STANDARD 17)

add_executable(radius main.cpp
        Loader.h
        API.h)
