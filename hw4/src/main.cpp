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
  
  hw4::HugeInt hi5("10");
  hw4::HugeInt hi6("-210");
  
  std::cout << hi5*hi6 << std::endl;
  
  return 0;
}
