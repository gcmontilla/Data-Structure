cmake_minimum_required(VERSION 3.10)
project(hash)

set(CMAKE_CXX_STANDARD 17)

add_executable(hash main.cpp record.h HashTable.h DoubleHashTable.h ChainedHashTable.h)