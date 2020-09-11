cmake_minimum_required(VERSION 3.12)
project(IFT3001_TP2_Question4)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(IFT3001_TP2_Question4
        evenement.hpp
        partition.cpp
        partition.hpp
        tests_partition.cpp)
