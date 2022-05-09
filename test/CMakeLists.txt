project(librarity_but_dumber_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_FILES
        unit/BookTest.cpp
        )

add_executable(librarity_but_dumber_tests_run ${TEST_FILES})
target_link_libraries(librarity_but_dumber_tests_run librarity_but_dumber_lib)
target_link_libraries(librarity_but_dumber_tests_run gtest gtest_main)