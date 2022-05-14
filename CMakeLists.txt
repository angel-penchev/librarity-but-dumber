cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILE main.cpp)
set(PROJECT_NAME librarity_but_dumber)
set(LIBRARY librarity_but_dumber_lib)


project(
        ${PROJECT_NAME}
        VERSION 1.0
        DESCRIPTION "Command-line software solution for storing, organizing and accessing books."
        LANGUAGES CXX)

# Testing
enable_testing()
add_subdirectory(test)

# Project
add_executable(${PROJECT_NAME} ${SOURCE_FILE})

add_subdirectory(lib)
include_directories(include)

target_link_libraries(${PROJECT_NAME} ${LIBRARY})
