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
    int value;
    if (isFlush(hand) && isStraight(hand))
    {
      value = valueStraightFlush(hand);
    }
    else if(isFourOfAKind(hand))
    {
      value =  valueFourOfAKind(hand);
    }
    else if(isFullHouse(hand))
    {
      value = valueFullHouse(hand);
    }
    else if(isFlush(hand))
    {
      value = valueFlush(hand);
    }
    else if (isStraight(hand))
    {
      value = valueStraight(hand);
    }
    else if (isThreeOfAKind(hand))
    {
      value = valueThreeOfAKind(hand);
    }
    else if (isTwoPairs(hand))
    {
      value = valueTwoPairs(hand);
    }
    else if (isOnePair(hand))
    {
      value = valueOnePair(hand);
    }
    else
    {
      value = valueHighCard(hand);
    }
      
    return value;
  }
  
  /*============================================================================
    getHand
        Returns the std::array

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  // PokerHand::Hand PokerHand::getHand() const
  // {
  //   return this->hand;
  // }
  
  /*============================================================================
    getValue
        Returns the calculated value of the hand

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  // int PokerHand::getValue() const
  // {
  //   return this->value;
  // }

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
    valueFlush
        Determines the value of a hand if assuming it is a flush

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  int PokerHand::valueFlush(Hand&)
  {
    return 0;
  }

  /*============================================================================
    valueFourOfAKind
        Determines the value of a hand if assuming it is a four of a kind

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  int PokerHand::valueFourOfAKind(Hand&)
  {
    return 0;
  }

  /*============================================================================
    valueFullHouse
        Determines the value of a hand if assuming it is a full house

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  int PokerHand::valueFullHouse(Hand&)
  {
    return 0;
  }

  /*============================================================================
    valueHighCard
        Determines the value of a hand disregarding the other possible special
	possible types: (e.g. Full House, Flush, etc...)

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  int PokerHand::valueHighCard(Hand&)
  {
    return 0;
  }
  
  /*============================================================================
    valueOnePair
        Determines the value of a hand if assuming it is a One Pair hand only

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  int PokerHand::valueOnePair(Hand&)
  {
    return 0;
  }

  /*============================================================================
    valueStraigt
        Determines the value of a hand if assuming it only contains a Straight

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  int PokerHand::valueStraight(Hand&)
  {
    return 0;
  }

  /*============================================================================
    valueStraightFlush
        Determines the value of a hand if assuming it is a Straight Flush

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  int PokerHand::valueStraightFlush(Hand&)
  {
    return 0;
  }

  /*============================================================================
    valueThreeOfAKind
        Determines the value of a hand if assuming it has Three of a Kind

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  int PokerHand::valueThreeOfAKind(Hand&)
  {
    return 0;
  }

  /*============================================================================
    valueThreeOfAKind
        Determines the value of a hand if assuming it has Three of a Kind

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  int PokerHand::valueTwoPairs(Hand&)
  {
    return 0;
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
