cmake_minimum_required(VERSION 2.6)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

project("Unittest")
set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# Link runTests with what we want to test 
# and the GTest and pthread library
add_executable(runTests unittest.cpp ../grammer.tab.c lex.yy.c)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
