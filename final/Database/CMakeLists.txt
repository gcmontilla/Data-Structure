cmake_minimum_required(VERSION 3.10)
project(Database)

set(CMAKE_CXX_STANDARD 11)

add_executable(Database main.cpp STokenizer.cpp STokenizer.h constants.h Token.cpp Token.h consts.h file_record.h file_record.cpp utilities.cpp utilities.h Parse.cpp Parse.h Table.cpp Table.h BPlusTree.h mmap.h pair.h utilities.h utilities.cpp b_tree.h map.h utility.h SQL.cpp SQL.h)