#!/bin/zsh

if [[ -f CMakeCache.txt ]]
then
    rm CMakeCache.txt
fi

if [[ -d CMakeFiles/ ]]
then
    rm -r CMakeFiles
fi

if [[ -f cmake_install.cmake ]]
then
    rm cmake*
fi

if [[ -f Makefile ]]
then
    rm Makefile
fi

if [[ -f dfs_testing ]]
then
    rm dfs_testing
fi

if [[ -f graph ]]
then
    rm graph
fi
