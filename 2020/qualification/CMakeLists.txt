cmake_minimum_required(VERSION 3.15)
project(qualification)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib)
include_directories(src)

add_executable(qualification
        lib/Algorithm.h
        lib/Defines.h
        lib/FileHandler.h
        src/Algorithm.cpp
        src/FileHandler.cpp
        src/GoogleHash.cpp
        Makefile)
