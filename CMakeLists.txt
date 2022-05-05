cmake_minimum_required(VERSION 3.16)
project(librarity_but_dumber)

set(CMAKE_CXX_STANDARD 11)

add_executable(librarity_but_dumber main.cpp src/book/Book.cpp src/book/Book.h src/user/User.cpp src/user/User.h src/library/Library.cpp src/library/Library.h)
