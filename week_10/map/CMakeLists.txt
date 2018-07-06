cmake_minimum_required(VERSION 3.10)
project(map)

set(CMAKE_CXX_STANDARD 17)

add_executable(map main.cpp pair.h map.h utility.h b_tree.h)