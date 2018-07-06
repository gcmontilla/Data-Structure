cmake_minimum_required(VERSION 3.10)
project(BPlusTree)

set(CMAKE_CXX_STANDARD 11)

add_executable(BPlusTree main.cpp BPlusTree.h utility.h mmap.h map.h)