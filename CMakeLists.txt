cmake_minimum_required(VERSION 3.6)                 # CMake version check
project(bdb)                                         # Create project "bdb"
set(CMAKE_CXX_STANDARD 11)                          # Enable c++11 standard
set(SOURCE_FILES bdb.c)                             # Add main.cpp file of project root directory as source file
add_executable(db ${SOURCE_FILES})
