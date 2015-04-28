#!/bin/zsh

if ! cmake .
then
    ./gtest/delete.sh
    exit
fi

if ! make
then
    ./gtest/delete.sh
    exit
fi

clear
echo "Testing is starting:"

for ((i = 0; i < 3; i++))
do
    echo
done

./poker_testing

for ((i = 0; i < 3; i++))
do
    echo
done

./gtest/delete.sh
