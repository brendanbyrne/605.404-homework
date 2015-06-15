/*
  RankHands.cpp
  Author: Brendan Byrne
  Date: 15 June, 2015
  Class: 605.404.31 Object Oriented Programming in C++
  Purpose: This program loads a configuration file and compares all
           the different poker hands that are contained with in it
  Input: (from a configuration file)
           Player hands and the expected winner
  Output: (to standard out) The poker hands being compared, which hand
          was calculated to win and which hand should have won
*/

#include <iostream>
#include <string>
#include <sstream>
#include <array>

#include <libconfig.h++>

#include "PokerHand.hpp"
#include "PlayingCard.hpp"

using hw2::operator<<;

int main()
{

  std::cout << "Loading Configuration File" << std::endl;
  
  libconfig::Config cfg;
  cfg.readFile("test.cfg");
  
  std::string name;
  cfg.lookupValue("description", name);
  std::cout << "Description: " << name << std::endl;
    
  int number_of_comparisions;
  int number_of_players;
  int number_of_cards;
  cfg.lookupValue("number_of_comparisions", number_of_comparisions);
  cfg.lookupValue("number_of_players", number_of_players);
  cfg.lookupValue("number_of_cards", number_of_cards);

  std::cout << "Number of comparisions to be made: "
	    << number_of_comparisions << std::endl;
  std::cout << "Number of players in comparision: "
	    << number_of_players << std::endl;
  std::cout << "Number of cards in hand per player: "
	    << number_of_cards << std::endl;
  std::cout << std::endl;

  //number_of_comparisions = 3;

  // Run all the comparisions in the cfg file  
  for (int comparisionNumber = 1;
       comparisionNumber <= number_of_comparisions;
       comparisionNumber++)
  {
    
    std::array<hw2::PokerHand, 2> players;
    for (int playerNumber = 1;
	 playerNumber <= number_of_players;
	 playerNumber++)
    {
      
      hw2::PokerHand::Hand hand;
      
      for (int cardNumber = 1;
	   cardNumber <= number_of_cards;
	   cardNumber++)
      {
	// empty the string stream
	std::stringstream ss;
	
	// build lookup string location
	ss << "compare" << comparisionNumber
	   << ".h" <<  playerNumber
	   << ".card" << cardNumber;
	
	// look up the card properties
	int rank;
	int suit;
	cfg.lookupValue(ss.str()+".rank", rank);
	cfg.lookupValue(ss.str()+".suit", suit);

	// add card to hand
	hand[cardNumber-1] = hw2::PlayingCard(rank, suit);
	
      } // for cardNumber

      // add player to compare
      players[playerNumber-1] = hw2::PokerHand(hand);
      
    } // for playerNumber
    
    int calculatedWinner;
    if (players[0].getValue() > players[1].getValue())
    {
      calculatedWinner = 1;
    }
    else if (players[0].getValue() == players[1].getValue())
    {
      calculatedWinner = 0;
    }
    else
    {
      calculatedWinner = -1;
    }

    int givenWinner;
    std::stringstream ss;
    ss << "compare" << comparisionNumber << ".winner";
    cfg.lookupValue(ss.str(), givenWinner);
    
    std::cout << "Comparision: " << comparisionNumber << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    std::cout << "  Comparing" << std::endl;
    std::cout << "    " << players[0].getHand() << std::endl;
    std::cout << "      against" << std::endl;
    std::cout << "    " << players[1].getHand() << std::endl;
    std::cout << std::endl;
    std::cout << "  Values: " << players[0].getValue()
	      << " vs. " << players[1].getValue() << std::endl;
    std::cout << "  Expected outcome: " << givenWinner << std::endl;
    std::cout << "  Calculated outcome: " << calculatedWinner << std::endl;
    std::cout << std::endl;
    
  } // for comparisionNumber

  return 0;
}
