#include <libconfig.h++>
#include "PlayingCard.hpp"

// for testing
#include <iostream>
#include <string>

int main()
{
  libconfig::Config cfg;
  
  cfg.readFile("test.cfg");
  
  
  std::string name;

  cfg.lookupValue("name", name);

  std::cout << name << std::endl;
  

  //libconfig::Setting& root = cfg.getRoot();
  
  
  return 0;
}
