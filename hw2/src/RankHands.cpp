#include <libconfig.h++>

#include <array>

#include "PokerHand.hpp"
#include "PlayingCard.hpp"

// for testing
#include <iostream>
#include <string>

using hw2::operator<<;
/*
void readHand(int[][] intHand)
{
  for (auto rankAndSuit : intHand)
  {
    hw2::PlayingCard pc(rankAndSuit[0],rankAndSuit[1]);
    std::cout << pc << std::endl;
  }
}
*/

int main()
{
  hw2::PokerHand::Hand heartFlushHand = {hw2::PlayingCard(7, 2),
					 hw2::PlayingCard(6, 2),
					 hw2::PlayingCard(5, 2),
					 hw2::PlayingCard(4, 2),
					 hw2::PlayingCard(3, 2)};

  hw2::PokerHand heartStraightFlush(heartFlushHand);

  std::cout << "\n" << std::endl;
  
  hw2::PokerHand::Hand spadeFlushHand = {hw2::PlayingCard(5,0),
					 hw2::PlayingCard(4,0),
					 hw2::PlayingCard(3,0),
					 hw2::PlayingCard(2,0),
					 hw2::PlayingCard(14,0)};

  hw2::PokerHand spadeStraightFlush(spadeFlushHand);
  
  bool value = hw2::PlayingCard::Rank::TWO > hw2::PlayingCard::Rank::ACE;
  std::cout << "Ace > Two = " << value << std::endl;
  
  
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
