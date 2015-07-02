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
#include <string>

#include "HugeInt.hpp"

int main()
{
  hw4::HugeInt bigInt;
  hw4::HugeInt result;
  
  std::cout << "Addition test" << std::endl;
  bigInt = std::string("1000000000100000000001000000000010000000000100000000001000000000010000000000");
  std::string strAdd = "9";
  
  result = bigInt + strAdd;
  std::cout << bigInt << " + " << strAdd << " = " << result << "\n" << std::endl;
    
  result = strAdd + bigInt;
  std::cout << strAdd << " + " << bigInt << " = " << result << "\n" << std::endl;
  

  std::cout << "Subtraction test" << std::endl;
  bigInt = std::string("10000000000000000000000000000000000000000000000000000000000000000000000");
  std::cout << "Number of digits in bigInt: " << bigInt.getValue().size() << std::endl;

  int intSub = 1;
  
  result = bigInt - intSub;
  std::cout << "Number of digits in result: " << result.getValue().size() << std::endl;
  std::cout << bigInt << " - " << intSub << " = " << result << "\n" << std::endl;
  
  result = intSub - bigInt;
  std::cout << intSub << " - " << bigInt << " = " << result << "\n" << std::endl;
  
    return 0;
}
