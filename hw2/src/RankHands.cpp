#include <libconfig.h++>

#include <array>

#include "PokerHand.hpp"
#include "PlayingCard.hpp"

// for testing
#include <iostream>
#include <string>

using hw2::operator<<;

int main()
{
  hw2::PokerHand::Hand h1 = {hw2::PlayingCard(14, 0),
			     hw2::PlayingCard(3, 1),
			     hw2::PlayingCard(3, 2),
			     hw2::PlayingCard(2, 1),
			     hw2::PlayingCard(2, 2)};
  
  hw2::PokerHand ph1(h1);
  
  /*
  libconfig::Config cfg;
  cfg.readFile("hands_to_test.cfg");
  libconfig::Setting& root = cfg.getRoot();
  
  std::string name;
  root.lookupValue("name", name);
  
  std::cout << name << std::endl;  

  libconfig::Setting& handList = root["hand"];
  int count = handList.getLength();
  std::cout << "size: " << count << std::endl;
  for(int i = 0; i < count; i++)
  {
    libconfig::Setting& number = handList[i];
    int val;//; = handList[i][0];
    number.lookupValue("val",val);
    std::cout << "Val: " << val << std::endl;
  }
  */
  return 0;
}
