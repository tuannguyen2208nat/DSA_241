/*
 * Assignment 1 - Developing List Data Structures and Artificial Neural Networks
 * file : unit_test.cpp
 * Data Structures and Algorithms
 * Author: Võ Tiến
 * Link FB : https://www.facebook.com/Shiba.Vo.Tien
 * Link Group : https://www.facebook.com/groups/khmt.ktmt.cse.bku
 * Date: 10.9.2024
 */
#include "unit_test.hpp"
map<string, bool (UnitTest::*)()> UnitTest::TESTS;

bool UnitTest::function1()
{
  // data
  XArrayList<int> list;

  // expect
  int expect = 0;

  // output
  int output = list.size();

  // remove data

  // prit result
  if (expect == output)
  {
    cout << green << "test function 1 --------------- PASS" << reset << "\n";
    return true;
  }
  else
  {
    cout << red << "test function 1 --------------- FAIL" << reset << "\n";
    cout << "\texpect : " << expect << endl;
    cout << "\toutput : " << output << endl;
    return false;
  }
}

bool UnitTest::function2()
{
  // data
  XArrayList<int> list;

  // expect
  int expect = 0;

  // output
  int output = list.size();

  // remove data

  // prit result
  if (expect == output)
  {
    cout << green << "test function 1 --------------- PASS" << reset << "\n";
    return true;
  }
  else
  {
    cout << red << "test function 1 --------------- FAIL" << reset << "\n";
    cout << "\texpect : " << expect << endl;
    cout << "\toutput : " << output << endl;
    return false;
  }
}