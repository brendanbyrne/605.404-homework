/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 10 June, 2015
  
  Revision History:
      10 June, 2015 - class created
      11 June, 2015 - many of the functions are fleshed out
      15 June, 2015 - logic tweaked for more precise encoding
      16 June, 2015 - supporting comments added
  
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
    static const int SIZE = 5; // the size of a poker hand

    // poker hand typedef, used to force the size of a poker hand
    typedef std::array<PlayingCard, SIZE> Hand;

    // typedef for rank frequency count output
    typedef std::map<PlayingCard::Rank, int> RankCount;
    
    // typedef for suit frequency count output
    typedef std::map<PlayingCard::Suit, int> SuitCount;
    
    PokerHand(); // default constructor, build empty class
    PokerHand(const Hand&); // construct PokerHand from a given 5 card hand
    Hand getHand() const; // hand attribute getter
    int getValue() const; // value attribute getter
    void setHand(const Hand&); // set the hand attribute to the provided Hand
    
  private:
    Hand hand; // the 5 cards representing the poker hand
    int value; // the encoded value of the poker hand

    // Encoding offsets for different kinds of hands
    static const int STRAIGHT_FLUSH  = 8000000;
    static const int FOUR_OF_A_KIND  = 7000000;
    static const int FULL_HOUSE      = 6000000;
    static const int FLUSH           = 5000000;
    static const int STRAIGHT        = 4000000;
    static const int THREE_OF_A_KIND = 3000000;
    static const int TWO_PAIRS       = 2000000;
    static const int ONE_PAIR        = 1000000;
    
    // enterance function for deteriming the type and value of a hand
    static int calculateHandValue(Hand&);

    // Functions for determining the type of hand
    static bool isFlush(const Hand&);
    static bool isFourOfAKind(const Hand&);
    static bool isFullHouse(const Hand&);
    static bool isOnePair(const Hand&);
    static bool isStraight(Hand&, bool&);
    static bool isThreeOfAKind(const Hand&);
    static bool isTwoPairs(const Hand&);

    // helper functions
    static RankCount frequencyRank(const Hand&); // frequency count of card ranks
    static SuitCount frequencySuit(const Hand&); // frequency count of card suits
    static void rankSort(Hand&); // ascending inplace sort of cards by rank
    
    // Functions for determining the value of a hand
    static int valueFlush(Hand&);
    static int valueFourOfAKind(const Hand&);
    static int valueFullHouse(const Hand&);
    static int valueHighCard(Hand& hand, bool isStraightAceLow = false);
    static int valueOnePair(Hand&);
    static int valueStraight(Hand&, bool);
    static int valueStraightFlush(Hand&, bool);    
    static int valueThreeOfAKind(const Hand&);
    static int valueTwoPairs(Hand&);    
    
  }; // PokerHand
  
  /*============================================================================
    getHand
        Returns the std::array

    Revision History
        10 June, 2015 - function created
  *///==========================================================================
  inline PokerHand::Hand PokerHand::getHand() const
  {
    return this->hand;
  }

  /*============================================================================
    getValue
        Returns the calculated value of the hand

    Revision History
        10 June, 2015 - function created
  *///==========================================================================
  inline int PokerHand::getValue() const
  {
    return this->value;
  }

  /*============================================================================
    setHand
        Changes the "hand" data member

    Revision History
        15 June, 2015 - function created
  *///==========================================================================
  inline void PokerHand::setHand(const Hand& hand)
  {
    this->hand = hand;
    this->value = PokerHand::calculateHandValue(this->hand);
  }
  
  // namespaced function overloads
  std::ostream& operator<<(std::ostream&, const PokerHand::Hand&);
  
}; // namespace hw2

#endif // POKER_HAND_HPP
