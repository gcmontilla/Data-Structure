cmake_minimum_required(VERSION 3.9)
project(avl)

set(CMAKE_CXX_STANDARD 11)

add_executable(avl main.cpp tree_node.h AVL.h)