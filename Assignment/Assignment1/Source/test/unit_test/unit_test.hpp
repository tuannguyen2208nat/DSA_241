/*
 * Assignment 1 - Developing List Data Structures and Artificial Neural Networks
 * file : unit_test.hpp
 * Data Structures and Algorithms
 * Author: Võ Tiến
 * Link FB : https://www.facebook.com/Shiba.Vo.Tien
 * Link Group : https://www.facebook.com/groups/khmt.ktmt.cse.bku
 * Date: 10.9.2024
 */
#ifndef UNIT_TEST_HPP
#define UNIT_TEST_HPP

#include "../../include/list/listheader.h"
#include "../main.hpp"

class UnitTest {
 public:
  UnitTest() {
    UnitTest::registerTest("function1", &UnitTest::function1);
    UnitTest::registerTest("function2", &UnitTest::function2);
    // TODO unit new
  }

 private:
  bool function1();
  bool function2();
  // TODO unit new

 public:
  static map<string, bool (UnitTest::*)()> TESTS;
  // ANSI escape codes for colors
  const string green = "\033[32m";
  const string red = "\033[31m";
  const string cyan = "\033[36m";
  const string reset = "\033[0m";  // To reset to default color

  static void registerTest(string name, bool (UnitTest::*function)()) {
    if (TESTS.find(name) != TESTS.end()) {
      throw std::runtime_error("Test with name '" + name + "' already exists.");
    }
    TESTS[name] = function;
  }

  void runTest(const std::string &name) {
    auto it = TESTS.find(name);
    if (it != TESTS.end()) {
      (this->*(it->second))();  // Gọi hàm kiểm tra
    } else {
      throw std::runtime_error("Test with name '" + name + "' does not exist.");
    }
  }

  void runAllTests() {
    vector<string> fails;
    for (const auto &test : TESTS) {
      if (!(this->*(test.second))()) {
        fails.push_back(test.first);
      }
    }

    cout << cyan << "\nResult -------------------------" << reset << endl;
    // Print the results
    if (fails.empty()) {
      cout << green << "All tests passed!" << reset << endl;
    } else {
      int totalTests = TESTS.size();
      int failedTests = fails.size();
      int passedTests = totalTests - failedTests;
      double passRate =
          (totalTests > 0)
              ? (static_cast<double>(passedTests) / totalTests) * 100.0
              : 0.0;
      cout << red << "Some tests failed:";
      for (const auto &fail : fails) {
        cout << "  " << fail;
      }
      cout << cyan << "\nPass rate: " << passRate << "%" << reset << endl;
    }
  }
};

#endif  // UNIT_TEST_HPP