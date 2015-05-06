#!/bin/zsh

echo "Would you like to run main or poker_testing?"
echo -ne "Enter main or poker_testing: "
read x

if [[ $x == "main" ]]
then
    mv run1.txt CMakeLists.txt
else
    mv run2.txt CMakeLists.txt
fi

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

if [[ $x == "poker_testing" ]]
then
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
else
    ./main
fi

if [[ $x == "main" ]]
then
    mv CMakeLists.txt run1.txt
else
    mv CMakeLists.txt run2.txt
fi

./gtest/delete.sh
