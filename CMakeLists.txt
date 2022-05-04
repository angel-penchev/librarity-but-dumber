cmake_minimum_required(VERSION 3.16)
project(librarity_but_dumber)

set(CMAKE_CXX_STANDARD 11)

add_executable(librarity_but_dumber main.cpp Book.cpp Book.h User.cpp User.h Library.cpp Library.h)
