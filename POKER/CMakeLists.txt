cmake_minimum_required(VERSION 2.8.4)
project(POKER)

add_executable(poker_testing
    poker_testing.cpp
    game.h
    game.cpp
    start_game.cpp
    card.h
    open_card.h
    open_card.cpp
    close_card.h
    close_card.cpp
    player.h
    human_player.h
    human_player.cpp
    deck.h
    deck.cpp
    UI.h
    UI.cpp
    gtest/gtest-all.cc
    gtest/gtest.h
    gtest/gtest_main.cc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -std=c++11 -pedantic")

target_link_libraries(poker_testing -lpthread)
