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
  libconfig::Config cfg;
  std::string name;
  cfg.readFile("test.cfg");
  cfg.lookupValue("name", name);
  std::cout << name << std::endl;
  libconfig::Setting& root = cfg.getRoot();
  
  hw2::PlayingCard pc(hw2::PlayingCard::Rank::KING,
		      hw2::PlayingCard::Suit::SPADES);
  
  hw2::PokerHand::Hand hand = {pc, pc, pc, pc, pc};
  hw2::PokerHand pokerhand(hand);

  std::cout << pokerhand << std::endl;
  
  return 0;
}
