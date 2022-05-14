project(librarity_but_dumber_tests)
include(FetchContent)
FetchContent_Declare(gtest
        QUIET
        URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
        )
# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

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