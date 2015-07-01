/*==============================================================================
  
  main.cpp
  
  Author: Brendan Byrne
  
  Inputs: None
    
  Outputs: The answer to several integer operations demonstrating the usage of
           the HugeInt class
  
*///============================================================================

#include <iostream>

#include "HugeInt.hpp"

int main()
{
  hw4::HugeInt hi1 = -9010;
  hw4::HugeInt hi2 = 910;
  
  hw4::HugeInt hi3 = 3;
  hw4::HugeInt hi4 = -3;
  
  hw4::HugeInt hi5("100");
  hw4::HugeInt hi6("10");
  
  std::cout << "lhs: " << hi5 << std::endl;
  std::cout << "rhs: " << hi6 << std::endl;

  hw4::HugeInt result = hi5/hi6;
  std::cout << "division test: " << result << std::endl;
  
  return 0;
}
