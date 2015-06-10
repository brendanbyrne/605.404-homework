/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 10 June, 2015
  
  Revision History:
      10 June, 2015 - class created
  
  Class Name: PokerHand.cpp
  
  Intent: To allow the comparison of different hands in poker
  
  Description: This file defines the PokerHand class which contains a 5 card
               hand. The value of the hand is calculated by the algorithm
	       presented at:
	       
  http://www.mathcs.emory.edu/~cheung/Courses/170/Syllabus/10/pokerValue.html
    
*///============================================================================
#ifndef POKER_HAND_HPP
#define POKER_HAND_HPP

#include <array>
#include <ostream>

#include "PlayingCard.hpp"

namespace hw2
{
  class PokerHand
  {
  public:
    const static int SIZE_OF_HAND = 5;
    
    typedef std::array<PlayingCard, SIZE_OF_HAND> Hand;
    
    PokerHand(Hand&);
    Hand getHand() const;
    int getValue() const;
    
  private:
    bool isAceHigh;
    Hand hand;
    int value;
    
    static int calculateHandValue(Hand&);
    static bool isFlush(Hand&);
    static bool isFourOfAKind(Hand&);
    static bool isFullHouse(Hand&);
    static bool isOnePair(Hand&);
    static bool isStraight(Hand&);
    static bool isThreeOfAKind(Hand&);
    static bool isTwoPairs(Hand&);
  }; // PokerHand

  std::ostream& operator<<(std::ostream&, const PokerHand&);
  
}; // namespace hw2

#endif // POKER_HAND_HPP
