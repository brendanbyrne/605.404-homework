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
  hw4::HugeInt hi2 = 9010;
  
  hw4::HugeInt hi3 = 3;
  hw4::HugeInt hi4 = -3;

  std::cout << "hi3-hi4: " << hi3+hi4 << std::endl;

  std::cout << hi1 << " == " << hi2 << " == " << (hi1== hi2) << std::endl;

  return 0;
}
