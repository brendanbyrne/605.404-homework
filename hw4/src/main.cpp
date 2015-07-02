/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 25 June, 2015
  
  main.cpp
  
  Author: Brendan Byrne
  
  Inputs: None
    
  Outputs: The answer to several integer operations demonstrating the usage of
           the HugeInt class
  
*///============================================================================

#include <iostream>
#include <iomanip>
#include <string>

#include "HugeInt.hpp"

int main()
{
  hw4::HugeInt bigInt;
  hw4::HugeInt result;
  std::string strMath;
  int intMath;
  std::string testTitle;
  std::string operatorStr;
  
  // Tests of the addition operator
  bigInt = std::string("100000000000000000000000000000000000000000000000000000000090");
  strMath = "9";
  intMath = 10;
  
  testTitle = "Addition Tests";
  operatorStr = "+";
  std::cout << std::string(80, '=') << std::endl;
  std::cout << std::setw(40 + testTitle.size()/2) << testTitle << std::endl;
  std::cout << std::string(80, '=') << std::endl;

  std::cout << "HugeInt " << operatorStr << " string" << std::endl;
  result = bigInt + strMath;
  std::cout << bigInt << " " << operatorStr << " " << strMath << " = " << "\n"
            << result << "\n" << std::endl;

  std::cout << "string " << operatorStr << " HugeInt" << std::endl;
  result = strMath + bigInt;
  std::cout << strMath << " " << operatorStr << " " << bigInt << " = " << "\n"
            << "    " << result << "\n" << std::endl;

  std::cout << "HugeInt " << operatorStr << " int" << std::endl;
  result = bigInt + intMath;
  std::cout << bigInt << " " << operatorStr << " " << intMath << " = " << "\n"
            << result << "\n" << std::endl;

  std::cout << "int " << operatorStr << " HugeInt" << std::endl;
  result = intMath + bigInt;
  std::cout << intMath << " " << operatorStr << " " << bigInt << " = " << "\n"
            << "     " << result << "\n" << std::endl;
  

  
  // Tests of the subtraction operator
  bigInt = std::string("100000000000000000000000000000000000000000000000000000000000");
  strMath = "10";
  intMath = 1;
  
  testTitle = "Subtraction Tests";
  operatorStr = "-";
  std::cout << std::string(80, '=') << std::endl;
  std::cout << std::setw(40 + testTitle.size()/2) << testTitle << std::endl;
  std::cout << std::string(80, '=') << std::endl;
  
  std::cout << "HugeInt " << operatorStr << " string" << std::endl;
  result = bigInt - strMath;
  std::cout << bigInt << " " << operatorStr << " " << strMath << " = " << "\n" 
            << " " << result << "\n" << std::endl;

  std::cout << "string " << operatorStr << " HugeInt" << std::endl;
  result = strMath - bigInt;
  std::cout << strMath << " " << operatorStr << " " << bigInt << " = " << "\n"
            << "     " << result << "\n" << std::endl;

  std::cout << "HugeInt " << operatorStr << " int" << std::endl;
  result = bigInt - intMath;
  std::cout << bigInt << " " << operatorStr << " " << intMath << " = " << "\n"
            << " " << result << "\n" << std::endl;

  std::cout << "int " << operatorStr << " HugeInt" << std::endl;
  result = intMath - bigInt;
  std::cout << intMath << " " << operatorStr << " " << bigInt << " = " << "\n"
            << "    " << result << "\n" << std::endl;

  
  // Tests of the multiplication operator
  bigInt = std::string("100000000000000000010000000000030000000060000000000000000000");
  strMath = "-11";
  intMath = 2;
  
  testTitle = "Multiplication Tests";
  operatorStr = "*";
  std::cout << std::string(80, '=') << std::endl;
  std::cout << std::setw(40 + testTitle.size()/2) << testTitle << std::endl;
  std::cout << std::string(80, '=') << std::endl;
  
  std::cout << "HugeInt " << operatorStr << " string" << std::endl;
  result = bigInt * strMath;
  std::cout << bigInt << " " << operatorStr << " " << strMath << " = " << "\n" 
            << "" << result << "\n" << std::endl;

  std::cout << "string " << operatorStr << " HugeInt" << std::endl;
  result = strMath * bigInt;
  std::cout << strMath << " " << operatorStr << " " << bigInt << " = " << "\n"
            << "    " << result << "\n" << std::endl;

  std::cout << "HugeInt " << operatorStr << " int" << std::endl;
  result = bigInt * intMath;
  std::cout << bigInt << " " << operatorStr << " " << intMath << " = " << "\n"
            << "" << result << "\n" << std::endl;

  std::cout << "int " << operatorStr << " HugeInt" << std::endl;
  result = intMath * bigInt;
  std::cout << intMath << " " << operatorStr << " " << bigInt << " = " << "\n"
            << "    " << result << "\n" << std::endl;
  
  
  // Tests of the division operator
  bigInt = std::string("100000000000000000000000000000000000000060000000000000000000");
  strMath = "3";
  intMath = -5;
  
  testTitle = "Division Tests";
  operatorStr = "/";
  std::cout << std::string(80, '=') << std::endl;
  std::cout << std::setw(40 + testTitle.size()/2) << testTitle << std::endl;
  std::cout << std::string(80, '=') << std::endl;
  
  std::cout << "HugeInt " << operatorStr << " string" << std::endl;
  result = bigInt / strMath;
  std::cout << bigInt << " " << operatorStr << " " << strMath << " = " << "\n" 
            " " << result << "\n" << std::endl;

  std::cout << "string " << operatorStr << " HugeInt" << std::endl;
  result = strMath / bigInt;
  std::cout << strMath << " " << operatorStr << " " << bigInt << " = " << "\n"
            << result << "\n" << std::endl;

  std::cout << "HugeInt " << operatorStr << " int" << std::endl;
  result = bigInt / intMath;
  std::cout << bigInt << " " << operatorStr << " " << intMath << " = " << "\n"
            << result << "\n" << std::endl;

  std::cout << "int " << operatorStr << " HugeInt" << std::endl;
  result = intMath / bigInt;
  std::cout << intMath << " " << operatorStr << " " << bigInt << " = " << "\n"
            << " " << result << "\n" << std::endl;
  
  
  
  return 0;
} // main
