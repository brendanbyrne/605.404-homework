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
#include <map>
#include <ostream>

#include "PlayingCard.hpp"

namespace hw2
{
  class PokerHand
  {
  public:
    static const int SIZE = 5;
    
    typedef std::array<PlayingCard, SIZE> Hand;
    typedef std::map<PlayingCard::Rank, int> RankCount;
    typedef std::map<PlayingCard::Suit, int> SuitCount;
    
    PokerHand(Hand&);
    Hand getHand() const;
    int getValue() const;
    
  private:
    bool isAceHigh;
    Hand hand;
    int value;

    // Encoding offsets for different kinds of hands
    static const int STRAIGHT_FLUSH  = 8000000;
    static const int FOUR_OF_A_KIND  = 7000000;
    static const int FULL_HOUSE      = 6000000;
    static const int FLUSH           = 5000000;
    static const int STRAIGHT        = 4000000;
    static const int THREE_OF_A_KIND = 3000000;
    static const int TWO_PAIRS       = 2000000;
    static const int ONE_PAIR        = 1000000;

    // Functions for determining the type of hand
    static int calculateHandValue(Hand&);
    static bool isFlush(Hand&);
    static bool isFourOfAKind(Hand&);
    static bool isFullHouse(Hand&);
    static bool isOnePair(Hand&);
    static bool isStraight(Hand&);
    static bool isThreeOfAKind(Hand&);
    static bool isTwoPairs(Hand&);

    // helper functions
    static RankCount frequencyRank(const Hand&);
    static SuitCount frequencySuit(const Hand&);
    static void rankSort(Hand&);
    
    // Functions for determining the value of a hand
    static int valueFlush(Hand&);
    static int valueFourOfAKind(Hand&);
    static int valueFullHouse(Hand&);
    static int valueHighCard(Hand&);
    static int valueOnePair(Hand&);
    static int valueStraight(Hand&);
    static int valueStraightFlush(Hand&);    
    static int valueThreeOfAKind(Hand&);
    static int valueTwoPairs(Hand&);    
    
  }; // PokerHand

  /*============================================================================
    getHand
        Returns the std::array

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  inline PokerHand::Hand PokerHand::getHand() const
  {
    return this->hand;
  }

  /*============================================================================
    getValue
        Returns the calculated value of the hand

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  inline int PokerHand::getValue() const
  {
    return this->value;
  }
  
  std::ostream& operator<<(std::ostream&, const PokerHand::Hand&);
  
}; // namespace hw2

#endif // POKER_HAND_HPP
