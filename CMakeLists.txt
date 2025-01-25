cmake_minimum_required(VERSION 3.10)

project(PowerShell)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(PowerShell src/main.cpp src/PowerShell.cpp)