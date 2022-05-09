cmake_minimum_required(VERSION 3.16)
project(librarity_but_dumber)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp)

add_executable(librarity_but_dumber_run ${SOURCE_FILES})

include_directories(lib)
add_subdirectory(lib)

target_link_libraries(librarity_but_dumber_run librarity_but_dumber_lib)

add_subdirectory(test)