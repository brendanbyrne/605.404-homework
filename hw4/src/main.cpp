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
  hw4::HugeInt hi1 = 1000;
  hw4::HugeInt hi2 = 9000;
  
  std::cout << "HugeInt: " << hi1+hi2 << std::endl;
    
  return 0;
}
