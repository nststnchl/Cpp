cmake_minimum_required(VERSION 2.8.4)
project(DFS)

find_package(Boost COMPONENTS serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${DFS_SOURCE_DIR})

add_executable(dfs_testing
    dfs_testing.cpp
    Graph.h
    Graph.cpp
    gtest/gtest-all.cc
    gtest/gtest.h
    gtest/gtest_main.cc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -std=c++11 -pedantic")

target_link_libraries(dfs_testing -lgmp -lgmpxx -lpthread ${Boost_LIBRARIES})
