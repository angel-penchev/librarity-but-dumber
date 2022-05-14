project(librarity_but_dumber_tests)
add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

set(TEST_FILES
        unit/BookTest.cpp
        e2e/LibrarityButDumberTest.cpp)

add_executable(librarity_but_dumber_tests ${TEST_FILES})
target_link_libraries(librarity_but_dumber_tests librarity_but_dumber_lib)
target_link_libraries(librarity_but_dumber_tests gtest gtest_main)

add_definitions("-DPATH_TO_FIXTURES=\"${CMAKE_SOURCE_DIR}/test/fixtures/\"")

include(GoogleTest)
gtest_discover_tests(librarity_but_dumber_tests
        PROPERTIES
        DISCOVERY_TIMEOUT 240
        )