/*
 * Assignment 1 - Developing List Data Structures and Artificial Neural Networks
 * file : main.cpp
 * Data Structures and Algorithms
 * Author: Võ Tiến
 * Link FB : https://www.facebook.com/Shiba.Vo.Tien
 * Link Group : https://www.facebook.com/groups/khmt.ktmt.cse.bku
 * Date: 10.9.2024

 * build code : g++ -o main -Iinclude -Isrc -std=c++17 main.cpp
 test/unit_test/unit_test.cpp test/random_test/random_test.cpp

 * run code
    * terminal unit test
    ! ./main test_unit
    ! ./main test_unit all
    ! ./main test_unit nameFunctionUnitTest

    * terminal auto test
    ! ./main test_random number_1 number_2
    ! ./main test_random number
*/

#include "test/random_test/random_test.hpp"
#include "test/unit_test/unit_test.hpp"

void printTestCase();
void handleTestUnit(int argc, char *argv[]);
void handleTestRandom(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  if (argc <= 1)
  {
    printTestCase();
    return 1;
  }

  std::string arg1 = argv[1];
  if (arg1 == "test_unit")
  {
    handleTestUnit(argc, argv);
  }
  else if (arg1 == "test_random")
  {
    handleTestRandom(argc, argv);
  }
  else
  {
    printTestCase();
  }
}

void handleTestUnit(int argc, char *argv[])
{
  UnitTest unitTest;

  if (argc == 2 || (argc == 3 && std::string(argv[2]) == "all"))
  {
    std::cout << "Running all unit tests: ----------\n";
    unitTest.runAllTests();
  }
  else if (argc == 3)
  {
    std::cout << "Running unit test: " << argv[2] << " ----------\n";
    unitTest.runTest(argv[2]);
  }
  else
  {
    printTestCase();
  }
}

void handleTestRandom(int argc, char *argv[])
{
  if (argc == 3)
  {
    try
    {
      int number = std::stoi(argv[2]);
      std::cout << "Running RandomTest with single number: " << number
                << " ----------\n";
      RandomTest random(number, number);
      random.runTest();
    }
    catch (const std::invalid_argument &e)
    {
      std::cerr << "Invalid number argument: " << e.what() << std::endl;
    }
  }
  else if (argc == 4)
  {
    try
    {
      int number1 = std::stoi(argv[2]);
      int number2 = std::stoi(argv[3]);
      std::cout << "Running RandomTest with numbers: " << number1 << " to "
                << number2 << " ----------\n";
      RandomTest random(number1, number2);
      random.runTest();
    }
    catch (const std::invalid_argument &e)
    {
      std::cerr << "Invalid number argument: " << e.what() << std::endl;
    }
  }
  else
  {
    printTestCase();
  }
}

void printTestCase()
{
  const std::string RESET = "\033[0m";
  const std::string BOLD = "\033[1m";
  const std::string RED = "\033[31m";
  const std::string GREEN = "\033[32m";
  const std::string CYAN = "\033[36m";

  std::cout << GREEN << BOLD << "terminal unit test" << RESET << std::endl;
  std::cout << RED << "./main test_unit" << RESET << std::endl;
  std::cout << RED << "./main test_unit all" << RESET << std::endl;
  std::cout << RED << "./main test_unit nameFunctionUnitTest" << RESET
            << std::endl
            << std::endl;

  std::cout << GREEN << BOLD << "terminal auto test" << RESET << std::endl;
  std::cout << RED << "./main test_random number_1 number_2" << RESET
            << std::endl;
  std::cout << RED << "./main test_random number" << RESET << std::endl;
}