// PokerHand.cpp - Functions for determining the value of a poker hand

#include <string>
#include <array>
#include <sstream>

#include <boost/algorithm/string/join.hpp>

#include "PokerHand.hpp"

namespace hw2
{
  /*============================================================================
    PokerHand
        Constructor for a PokerHand object

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  PokerHand::PokerHand(Hand& hand):
    hand(hand), value(PokerHand::calculateHandValue(this->hand))
  {
  }
  
  /*============================================================================
    calculateHandValue
        Evaluates the stored Hand and determines its numerical value

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  int PokerHand::calculateHandValue(Hand& hand)
  {
    return 0;
  }

  /*============================================================================
    getHand
        Returns the std::array

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  PokerHand::Hand PokerHand::getHand() const
  {
    return this->hand;
  }
  
  /*============================================================================
    getValue
        Returns the calculated value of the hand

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  int PokerHand::getValue() const
  {
    return this->value;
  }

  /*============================================================================
    isFlush
        Determines whether of not the hand is a flush

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  bool PokerHand::isFlush(Hand& hand)
  {
    return false;
  }

  /*============================================================================
    isFourOfAKind
        Determines whether of not the hand has a four of kind

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  bool PokerHand::isFourOfAKind(Hand& hand)
  {
    return false;
  }

  /*============================================================================
    isFullHouse
        Determines whether of not the hand is a full house

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  bool PokerHand::isFullHouse(Hand& hand)
  {
    return false;
  }

  /*============================================================================
    isOnePair
        Determines whether of not the hand has a single pair of cards

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  bool PokerHand::isOnePair(Hand& hand)
  {
    return false;
  }
  
  /*============================================================================
    isStraight
        Determines whether of not the hand is a straight

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  bool PokerHand::isStraight(Hand& hand)
  {
    return false;
  }

  /*============================================================================
    isThreeOfAKind
        Determines whether of not the hand has a three of a kind

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  bool PokerHand::isThreeOfAKind(Hand& hand)
  {
    return false;
  }

  /*============================================================================
    isTwoPair
        Determines whether of not the hand has a two pairs

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  bool PokerHand::isTwoPairs(Hand& hand)
  {
    return false;
  }  

  /*============================================================================
    operator<<
        Returns a human readable representation of a poker hand

    Note:
        Only works inside hw2 namespace useless combined with "using"

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, const PokerHand&  pokerhand)
  {
    PokerHand::Hand hand = pokerhand.getHand();
    std::array<std::string, hand.size()> strings;

    std::transform(hand.begin(), hand.end(), strings.begin(), [](PlayingCard& card)
		   {
		     std::stringstream ss;
		     ss << card;
		     return ss.str();
		   });

    out << boost::algorithm::join(strings, ", ");
    
    return out;
  }
    
}; // namespace hw2
