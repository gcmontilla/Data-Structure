cmake_minimum_required(VERSION 3.9)
project(linked_lists)

set(CMAKE_CXX_STANDARD 11)

add_executable(linked_lists main.cpp queue.cpp Headers/queue.h Headers/list.h stack.cpp Headers/stack.h)