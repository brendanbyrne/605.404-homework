#include <libconfig.h++>

#include "PokerHand.hpp"
#include "PlayingCard.hpp"

// for testing
#include <iostream>
#include <string>

using hw2::operator<<;

libconfig::Setting& loadConfig(const char* filename)
{  
  libconfig::Config cfg;
  
  cfg.readFile(filename);
  
  libconfig::Setting& root = cfg.getRoot();
  return root;
}


int main()
{
  hw2::PokerHand::Hand h1 = {hw2::PlayingCard(2, 0),
			     hw2::PlayingCard(3, 0),
			     hw2::PlayingCard(4, 0),
			     hw2::PlayingCard(5, 0),
			     hw2::PlayingCard(6, 1)};
  
  hw2::PokerHand ph1(h1);
  
  std::cout << "Hand Value: " << ph1.getValue() << std::endl;
  
  libconfig::Config cfg;
  cfg.readFile("test.cfg");
  
  std::string name;
  cfg.lookupValue("description", name);
  std::cout << name << std::endl;
  
  int suit;
  int rank;
  
  cfg.lookupValue("compare1.h1.card1.suit", suit);
  cfg.lookupValue("compare1.h1.card1.rank", rank);
  
  hw2::PlayingCard pc(rank, suit);
  std::cout << pc << std::endl;
  

  return 0;
}
