// PokerHand.cpp - Functions for determining the value of a poker hand

#include <string>
#include <array>
#include <sstream>
#include <algorithm> // for find, sort

#include <boost/algorithm/string/join.hpp>

#include "PokerHand.hpp"

// testing
#include <iostream>

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
    std::cout << "Hand: " << hand << std::endl;
    std::cout << "Is flush: " << isFlush(hand) << std::endl;
    std::cout << "Is straight: " << isStraight(hand) << std::endl;
    std::cout << "Is four of a kind: " << isFourOfAKind(hand) << std::endl;
    std::cout << "Is three of a kind: " << isThreeOfAKind(hand) << std::endl;
    std::cout << "Is 2 pairs: " << isTwoPairs(hand) << std::endl;
    std::cout << "Is a pair: " << isOnePair(hand) << std::endl;
    
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
      
    //return value;
    return 0;
  }

  /*============================================================================	
    frequencyRank
        creates a frequency count of the different card ranks

    Revision History:
        11 June, 2015 - function created
  *///==========================================================================
  PokerHand::RankCount PokerHand::frequencyRank(const Hand& hand)
  {
    RankCount frequency;
    for(auto card : hand)
    {
      ++frequency[card.getRank()];
    }
    return frequency;
  }

  /*============================================================================	
    frequencySuit
        creates a frequency count of the different card suits

    Revision History:
        11 June, 2015 - function created
  *///==========================================================================
  PokerHand::SuitCount PokerHand::frequencySuit(const Hand& hand)
  {
    SuitCount frequency;
    for(auto card : hand)
    {
      ++frequency[card.getSuit()];
    }
    return frequency;
  }
  
  /*============================================================================
    isFlush
        Determines whether of not the hand is a flush

    Revision History:
        10 June, 2015 - function created
	11 June, 2015 - completed logic added
  *///==========================================================================
  bool PokerHand::isFlush(Hand& hand)
  {
    SuitCount frequency = frequencySuit(hand);
    return frequency.size() == 1;
  }

  /*============================================================================
    isFourOfAKind
        Determines whether of not the hand has a four of kind

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  bool PokerHand::isFourOfAKind(Hand& hand)
  {
    bool rightConfiguration;
    
    RankCount frequency = frequencyRank(hand);

    if(frequency.size() != 2)
    {
      rightConfiguration = false;
    }
    else
    {
      rightConfiguration = frequency[0] == 4 || frequency[1] == 4;
    }

    return rightConfiguration;
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
    bool hasAce = hand.end() != std::find_if(hand.begin(), hand.end(),
					     [](PlayingCard& card) -> bool
					     {
					       return card.getRank() == PlayingCard::Rank::ACE;
					     });
    
    return hasAce;
  }

  /*============================================================================
    isThreeOfAKind
        Determines whether of not the hand has a three of a kind

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  bool PokerHand::isThreeOfAKind(Hand& hand)
  {
    RankCount frequency = frequencyRank(hand);
    for (auto count : frequency)
    {
      std::cout << cout << std::endl;
    }
    return false;
    //return rightConfiguration;
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
    suitSort
        sorts the hand based on the enum value of the suit, useful for 
	seperating the suits

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  void PokerHand::suitSort(Hand& hand)
  {
    std::sort(hand.begin(), hand.end(),
	      [](const PlayingCard& firstCard,
		 const PlayingCard& secondCard) -> bool
	      {
		return firstCard.getSuit() < secondCard.getSuit();;
	      });
  }
  
  /*============================================================================
    rankSort
        sorts the hand based on the enum value of the rank

    Note
        The ace will always be consider high in this search

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
   void PokerHand::rankSort(Hand& hand)
   {
     std::sort(hand.begin(), hand.end(),
	       [](const PlayingCard& firstCard,
		  const PlayingCard& secondCard) -> bool
	       {
		 return firstCard.getRank() < secondCard.getRank();
	       });
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
  std::ostream& operator<<(std::ostream& out, const PokerHand::Hand&  hand)
  {
   
    std::array<std::string, PokerHand::SIZE> strings;

    std::transform(hand.begin(), hand.end(), strings.begin(), [](const PlayingCard& card)
		   {
		     std::stringstream ss;
		     ss << card;
		     return ss.str();
		   });

    out << "[" + boost::algorithm::join(strings, ", ") + "]";
    
    return out;
  }
    
}; // namespace hw2
