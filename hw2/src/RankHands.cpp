/*
  RankHands.cpp
  Author: Brendan Byrne
  Date: 15 June, 2015
  Class: 605.404.31 Object Oriented Programming with C++
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
  // load the configuration file
  libconfig::Config cfg;
  cfg.readFile("comparisons.cfg");

  // print out description of config file
  std::string name;
  cfg.lookupValue("description", name);
  std::cout << "Description: " << name << std::endl;

  // load and print settings stored in the config file
  int number_of_comparisions;
  int number_of_hands;
  int number_of_cards;
  cfg.lookupValue("number_of_comparisions", number_of_comparisions);
  cfg.lookupValue("number_of_hands", number_of_hands);
  cfg.lookupValue("number_of_cards", number_of_cards);
  std::cout << "Number of comparisions to be made: "
	    << number_of_comparisions << std::endl;
  std::cout << "Number of handss in comparision: "
	    << number_of_hands << std::endl;
  std::cout << "Number of cards in hand per player: "
	    << number_of_cards << std::endl;
  std::cout << std::endl;

  // for each comparision
  for (int comparisionNumber = 1;
       comparisionNumber <= number_of_comparisions;
       comparisionNumber++)
  {

    // build two poker hands to compare
    std::array<hw2::PokerHand, 2> hands;
    
    for (int handNumber = 1;
	 handNumber <= number_of_hands;
	 handNumber++)
    {
      
      // build a single poker hand
      hw2::PokerHand::Hand hand;
      for (int cardNumber = 1;
	   cardNumber <= number_of_cards;
	   cardNumber++)
      {
	
	// build location of lookup string
	std::stringstream ss;
	ss << "compare" << comparisionNumber
	   << ".h" <<  handNumber
	   << ".card" << cardNumber;
	
	// look up the card properties
	int rank;
	int suit;
	cfg.lookupValue(ss.str()+".rank", rank);
	cfg.lookupValue(ss.str()+".suit", suit);

	// add card to hand
	hand[cardNumber-1] = hw2::PlayingCard(rank, suit);
	
      } // for cardNumber
      
      // add hand to compare
      hands[handNumber-1] = hw2::PokerHand(hand);
      
    } // for handNumber

    // figure out which hand is calculated to win
    int calculatedWinner;
    if (hands[0].getValue() > hands[1].getValue())
    {
      calculatedWinner = 1;
    }
    else if (hands[0].getValue() == hands[1].getValue())
    {
      calculatedWinner = 0;
    }
    else
    {
      calculatedWinner = -1;
    } // end if

    // load the predicted winner from the config file
    int givenWinner;
    std::stringstream ss;
    ss << "compare" << comparisionNumber << ".winner";
    cfg.lookupValue(ss.str(), givenWinner);

    // print out the results
    std::cout << "Comparision: " << comparisionNumber << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    std::cout << "  Comparing" << std::endl;
    std::cout << "    " << hands[0].getHand() << std::endl;
    std::cout << "      against" << std::endl;
    std::cout << "    " << hands[0].getHand() << std::endl;
    std::cout << std::endl;
    std::cout << "  Expected outcome: " << givenWinner << std::endl;
    std::cout << "  Calculated outcome: " << calculatedWinner << std::endl;
    std::cout << std::endl;
    
  } // for comparisionNumber

  return 0;
} // main function
