#!/bin/bash

# Check if the executable 'main' already exists and remove it
if [ -f main ]; then
    echo "Removing existing executable 'main'."
    rm main
fi

# Compile the C++ program
g++ -o g++ -o main -Iinclude -Isrc -std=c++17 main.cpp \
 test/unit_test/unit_test.cpp test/random_test/random_test.cpp

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo -e "\033[36m\033[1mCompilation successful. Run ./main to execute.\033[0m"
    echo -e "\033[32m\033[1mterminal unit test\033[0m"
    echo -e "\033[31m./main test_unit\033[0m"
    echo -e "\033[31m./main test_unit all\033[0m"
    echo -e "\033[31m./main test_unit nameFunctionUnitTest\033[0m"
    echo
    echo -e "\033[32m\033[1mterminal auto test\033[0m"
    echo -e "\033[31m./main test_random number_1 number_2\033[0m"
    echo -e "\033[31m./main test_random number\033[0m"
else
    echo -e "\033[31m\033[1mCompilation failed.\033[0m"
fi