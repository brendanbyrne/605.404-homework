// PokerHand.cpp - Functions for determining the value of a poker hand

#include <string>
#include <array>
#include <sstream>
#include <algorithm> // find_if, sort

#include <boost/algorithm/string/join.hpp>

#include "PokerHand.hpp"

namespace hw2
{
  /*============================================================================
    PokerHand
        Default Constructor for a PokerHand object
        
    Note
        This was created to allow PokerHand objects to be declared in an 
        uninitialized std::array

    Revision History
        15 June, 2015 - function created
  *///==========================================================================
  PokerHand::PokerHand()
  {
  }
  
  /*============================================================================
    PokerHand
        Constructor for a PokerHand object

    Revision History
        10 June, 2015 - function created
  *///==========================================================================
  PokerHand::PokerHand(const Hand& hand): // array of cards making up a hand
    hand(hand), value(PokerHand::calculateHandValue(this->hand))
  {
  }
  
  /*============================================================================
    calculateHandValue
        Evaluates the stored Hand and determines its numerical value

    Revision History
        10 June, 2015 - function created
  *///==========================================================================
  int PokerHand::calculateHandValue(Hand& hand) // array of cards making up a hand
  {

    bool isStraightAceLow = false; // is only set to high if the hand is a
                                   // straight, contains an ace, and the 
                                   // ace is at the bottom of the run
    
    int value;
    // figure out what kind of poker hand it is
    if (PokerHand::isFlush(hand) && PokerHand::isStraight(hand, isStraightAceLow))
    {
      value = PokerHand::valueStraightFlush(hand, isStraightAceLow);
    }
    else if (PokerHand::isFourOfAKind(hand))
    {
      value =  PokerHand::valueFourOfAKind(hand);
    }
    else if (PokerHand::isFullHouse(hand))
    {
      value = PokerHand::valueFullHouse(hand);
    }
    else if(PokerHand::isFlush(hand))
    {
      value = PokerHand::valueFlush(hand);
    }
    else if (PokerHand::isStraight(hand, isStraightAceLow))
    {
      value = PokerHand::valueStraight(hand, isStraightAceLow);
    }
    else if (PokerHand::isThreeOfAKind(hand))
    {
      value = PokerHand::valueThreeOfAKind(hand);
    }
    else if (PokerHand::isTwoPairs(hand))
    {
      value = PokerHand::valueTwoPairs(hand);
    }
    else if (PokerHand::isOnePair(hand))
    {
      value = PokerHand::valueOnePair(hand);
    }
    else
    {
      value = PokerHand::valueHighCard(hand);
    }
    
    return value;
  }

  /*============================================================================        
    frequencyRank
        performs a frequency count of the different card ranks in a hand

    Revision History
        11 June, 2015 - function created
  *///==========================================================================
  PokerHand::RankCount PokerHand::frequencyRank(const Hand& hand)
                                         // array of cards making up a hand
  {
    RankCount count;
    for (auto card : hand)
    {
      ++count[card.getRank()];
    }
    return count;
  }

  /*============================================================================        
    frequencySuit
        performs a frequency count of the different card suits in a hand

    Revision History
        11 June, 2015 - function created
  *///==========================================================================
  PokerHand::SuitCount PokerHand::frequencySuit(const Hand& hand)
                                        // array of cards making up a hand
  {
    SuitCount count;
    for (auto card : hand)
    {
      ++count[card.getSuit()];
    }
    return count;
  }
  
  /*============================================================================
    isFlush
        Determines whether of not the hand is a flush

    Revision History
        10 June, 2015 - function created
        11 June, 2015 - complete logic added
  *///==========================================================================
  bool PokerHand::isFlush(const Hand& hand)
                          // array of cards making up a hand
  {
    SuitCount count = PokerHand::frequencySuit(hand);
    return count.size() == 1;
  }

  /*============================================================================
    isFourOfAKind
        Determines whether of not the hand has a four of kind

    Revision History
        10 June, 2015 - function created
  *///==========================================================================
  bool PokerHand::isFourOfAKind(const Hand& hand)
                                // array of cards making up a hand
  {
    RankCount count = PokerHand::frequencyRank(hand);
    
    bool hasFour;
    if (count.size() != 2)
    {
      hasFour = false;
    }
    else
    {
      RankCount::iterator it = count.begin();
      do
      {
        hasFour = it++->second == 4 || hasFour;
      } while ( !hasFour && it != count.end() );
    }

    return hasFour;
  }

  /*============================================================================
    isFullHouse
        Determines whether of not the hand is a full house

    Revision History
        11 June, 2015 - function created
  *///==========================================================================
  bool PokerHand::isFullHouse(const Hand& hand)
                              // array of cards making up a hand
  {
    RankCount count = PokerHand::frequencyRank(hand);
    
    bool hasThreeCount;
    bool hasTwoCount;

    
    if (count.size() != 2)
    {
      hasThreeCount = false;
      hasTwoCount = false;
    }
    else
    {
      for (auto keyVal : count)
      {
        hasThreeCount = (keyVal.second == 3) || hasThreeCount;
        hasTwoCount = (keyVal.second == 2) || hasTwoCount;
      }
    }
    
    return hasThreeCount && hasTwoCount;
  }

  /*============================================================================
    isOnePair
        Determines whether of not the hand has a single pair of cards

    Revision History
        10 June, 2015 - function created
  *///==========================================================================
  bool PokerHand::isOnePair(const Hand& hand)
                            // array of cards making up a hand
  {
    RankCount count = PokerHand::frequencyRank(hand);
    return count.size() == 4;
  }
  
  /*============================================================================
    isStraight
        Determines whether of not the hand is a straight

    Note
        There is exists a special case with the Ace card.  Straights need to be
        checked to allow for ace high [10, J, Q, K, A] and ace low [A, 2, 3, 4]
        corner cases.

    Revision History        
        13 June, 2015 - Function Created
  *///==========================================================================
  bool PokerHand::isStraight(Hand& hand, // array of cards making up a hand
                             bool& isStraightAceLow) // output variable,
                                                     //true if the straight has a low ace
  {
    // does this hand contain an ace
    PokerHand::rankSort(hand);
    Hand::iterator aceLocation;
    aceLocation = std::find_if (hand.begin(), hand.end(),
                                [](PlayingCard& card) -> bool
                                {
                                  return card.getRank() == PlayingCard::Rank::ACE;
                                });
    bool hasAce = hand.end() != aceLocation;

    Hand::iterator it;
    bool hasStraight;
    // determines if the hand is a straight
    if (hasAce)
    {
      it = hand.begin();
      bool straightLowAce = it++->getRank() == PlayingCard::Rank::TWO &&
                            it++->getRank() == PlayingCard::Rank::THREE &&
                            it++->getRank() == PlayingCard::Rank::FOUR &&
                            it->getRank() == PlayingCard::Rank::FIVE;

      it = hand.begin();
      bool straightHighAce = it++->getRank() == PlayingCard::Rank::TEN &&
                             it++->getRank() == PlayingCard::Rank::JACK &&
                             it++->getRank() == PlayingCard::Rank::QUEEN &&
                             it->getRank() == PlayingCard::Rank::KING;

      // is there a straight involving a low valued ace
      // note: this value is returned by reference
      isStraightAceLow = straightLowAce; 
      
      hasStraight = straightLowAce || straightHighAce;
    }
    else
    {
      it = hand.begin();
      PlayingCard::Rank currentRank = it++->getRank();
      
      PlayingCard::Rank nextRank;
      PlayingCard::Rank predictedRank;
      hasStraight = true;
      do
      {
        // increment the current rank to the next one
        int valuePredictedRank = static_cast<int>(currentRank)+1;
        predictedRank = static_cast<PlayingCard::Rank>(valuePredictedRank);
        
        nextRank = it++->getRank();
        
        hasStraight = (nextRank == predictedRank) && hasStraight;
        
        currentRank = nextRank;
      } while (hasStraight && it != hand.end() );
    }
    
    return hasStraight;
  }

  /*============================================================================
    isThreeOfAKind
        Determines whether of not the hand has a three of a kind

    Revision History
        11 June, 2015 - function created
  *///==========================================================================
  bool PokerHand::isThreeOfAKind(const Hand& hand)
                                 // array of cards making up a hand
  {
    RankCount count = PokerHand::frequencyRank(hand);
    
    bool hasThree;
    RankCount::iterator it = count.begin();
    do
    {
      hasThree = it++->second == 3;
    } while ( !hasThree && it!=count.end() );
    
    return hasThree;
  }

  /*============================================================================
    isTwoPair
        Determines whether of not the hand has a two pairs

    Revision History
        10 June, 2015 - function created
  *///==========================================================================
  bool PokerHand::isTwoPairs(const Hand& hand)
                             // array of cards making up a hand
  {
    RankCount count = PokerHand::frequencyRank(hand);
    bool hasTwoPairs;

    // are there the right amount of cards for a two pair
    if (count.size() != 3)
    {
      hasTwoPairs = false;
    }
    else
    {
      const int PAIR = 2;
      int numberOfPairs = 0;
      for (auto keyVal : count)
      {
        if (keyVal.second == PAIR)
        {
          ++numberOfPairs;
        }
      }
      hasTwoPairs = numberOfPairs == PAIR;
    }
    return hasTwoPairs;
  }  
    
  /*============================================================================
    rankSort
        Ascenging order sort of the hand using the  enum value of the rank

    Note
        The ace will always be consider high in this search

    Revision History
        11 June, 2015 - function created
  *///==========================================================================
  void PokerHand::rankSort(Hand& hand) // array of cards making up a hand
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
    
    Revision History
        11 June, 2015 - function created
  *///==========================================================================
  int PokerHand::valueFlush(Hand& hand) // array of cards making up a hand
  {
    int value = PokerHand::FLUSH;
    value += PokerHand::valueHighCard(hand);
    return value;
  }
  
  /*============================================================================
    valueFourOfAKind
        Determines the value of a hand if assuming it is a four of a kind

    Revision History
        11 June, 2015 - function created
        15 June, 2015 - fixed non quad rank not effecting outcome
  *///==========================================================================
  int PokerHand::valueFourOfAKind(const Hand& hand)
                                  // array of cards making up a hand
  {
    
    RankCount count = PokerHand::frequencyRank(hand);

    PlayingCard::Rank rankQuad;
    PlayingCard::Rank rankSingle;
    for (auto keyVal : count)
    {
      if (keyVal.second == 4)
      {
        rankQuad = keyVal.first;
      }
      else if (keyVal.second == 1)
      {
        rankSingle = keyVal.first;
      }
    }
    
    int value = PokerHand::FOUR_OF_A_KIND;
    value += 14 * static_cast<int>(rankQuad);
    value += static_cast<int>(rankSingle);

    return value;
  }
  
  /*============================================================================
    valueFullHouse
        Determines the value of a hand if assuming it is a full house

    Revision History
        10 June, 2015 - function created
        15 June, 2015 - fixed X full of Y where rank Y wasn't effecting outcome
  *///==========================================================================
  int PokerHand::valueFullHouse(const Hand& hand)
                                // array of cards making up a hand
  {
    RankCount count = PokerHand::frequencyRank(hand);

    PlayingCard::Rank rankTriple;
    PlayingCard::Rank rankDouble;

    for (auto keyVal : count)
    {
      if (keyVal.second == 3)
      {
        rankTriple = keyVal.first;
      }
      else if (keyVal.second == 2)
      {
        rankDouble = keyVal.first;
      }
    }

    int value = PokerHand::FULL_HOUSE;
    value += 14 * static_cast<int>(rankTriple);
    value += static_cast<int>(rankDouble);

    return value;
  }

  /*============================================================================
    valueHighCard
        Determines the value of a hand disregarding the other possible special
        possible types: (e.g. Full House, Flush, etc...)

    Revision History
        13 June, 2015 - function created
  *///==========================================================================
  int PokerHand::valueHighCard(Hand& hand, // array of cards making up a hand
                               bool isAceLow) // switch to use the low value for ace
  {
    PokerHand::rankSort(hand);
    
    int value = 0;
    
    if (isAceLow)
    {
      const int ACE_LOW_VALUE = 1;
      value += ACE_LOW_VALUE;
      value += 14*static_cast<int>(hand[0].getRank());
      value += 14*14*static_cast<int>(hand[1].getRank());
      value += 14*14*14*static_cast<int>(hand[2].getRank());
      value += 14*14*14*14*static_cast<int>(hand[3].getRank());
    }
    else
    {
      value += static_cast<int>(hand[0].getRank());
      value += 14*static_cast<int>(hand[1].getRank());
      value += 14*14*static_cast<int>(hand[2].getRank());
      value += 14*14*14*static_cast<int>(hand[3].getRank());
      value += 14*14*14*14*static_cast<int>(hand[4].getRank());
    }
      
    return value;
  }
  
  /*============================================================================
    valueOnePair
        Determines the value of a hand if assuming it is a One Pair hand only

    Revision History
        14 June, 2015 - function created
  *///==========================================================================
  int PokerHand::valueOnePair(Hand& hand)
                              // array of cards making up a hand
  {
    PokerHand::rankSort(hand);
    
    int value;
    // find where the pair is and score accordingly
    if (hand[0].getRank() == hand[1].getRank())
    {
      value = 14 * 14 * 14 * static_cast<int>(hand[0].getRank()) +
        static_cast<int>(hand[2].getRank()) + 
        14 * static_cast<int>(hand[3].getRank()) +
        14 * 14 * static_cast<int>(hand[4].getRank());
    }
    else if (hand[1].getRank() == hand[2].getRank())
    {
      value = 14 * 14 * 14 * static_cast<int>(hand[1].getRank()) +
        static_cast<int>(hand[0].getRank()) + 
        14 * static_cast<int>(hand[3].getRank()) +
        14 * 14 * static_cast<int>(hand[4].getRank());
    }
    else if (hand[2].getRank() == hand[3].getRank())
    {
      value = 14 * 14 * 14 * static_cast<int>(hand[2].getRank()) +
        static_cast<int>(hand[0].getRank()) +
        14 * static_cast<int>(hand[1].getRank()) +
        14 * 14 * static_cast<int>(hand[4].getRank());
    }
    else
    {
      value = 14 * 14 * 14 * static_cast<int>(hand[3].getRank()) +
        static_cast<int>(hand[0].getRank()) +
        14 * static_cast<int>(hand[1].getRank()) + 
        14 * 14 * static_cast<int>(hand[2].getRank());
    }

    return PokerHand::ONE_PAIR + value;
  }

  /*============================================================================
    valueStraigt
        Determines the value of a hand if assuming it only contains a Straight

    Revision History
        13 June, 2015 - function created
  *///==========================================================================
  int PokerHand::valueStraight(Hand& hand, // array of cards making up a hand
                               bool isStraightAceLow) // pass through for the state
                                                      // of the ace card
  {
    int value = PokerHand::STRAIGHT;
    value += PokerHand::valueHighCard(hand, isStraightAceLow);
    return value;
  }

  /*============================================================================
    valueStraightFlush
        Determines the value of a hand if assuming it is a Straight Flush

    Revision History
        10 June, 2015 - function created
  *///==========================================================================
  int PokerHand::valueStraightFlush(Hand& hand, // array of cards making up a hand
                                    bool isStraightAceLow) // pass through for the state
                                                         // of the ace card
  {
    int value = PokerHand::STRAIGHT_FLUSH;
    value += PokerHand::valueHighCard(hand, isStraightAceLow);
    return value;
  }

  /*============================================================================
    valueThreeOfAKind
        Determines the value of a hand if assuming it has Three of a Kind

    Revision History
        10 June, 2015 - function created
  *///==========================================================================
  int PokerHand::valueThreeOfAKind(const Hand& hand)
                                   // array of cards making up a hand
  {
    RankCount count = PokerHand::frequencyRank(hand);
    
    PlayingCard::Rank rankTriple;
    std::array<PlayingCard::Rank, 2>  rankSingle;
    std::array<PlayingCard::Rank, 2>::iterator it = rankSingle.begin();

    // find the ranks appear 3 times and 1 time
    for (auto keyVal : count)
    {
      if (keyVal.second == 3)
      {
        rankTriple = keyVal.first;
      }
      else if (keyVal.second == 1)
      {
        *it = keyVal.first;
        it++;
      }
    }

    // add to the value accorrding to the different ranks
    int value = PokerHand::THREE_OF_A_KIND;
    value += 14 * 14 * static_cast<int>(rankTriple);
    
    if (rankSingle[0] > rankSingle[1])
    {
      value += 14 * static_cast<int>(rankSingle[0]);
      value += static_cast<int>(rankSingle[1]);
    }
    else
    {
      value += 14 * static_cast<int>(rankSingle[1]);
      value += static_cast<int>(rankSingle[0]);
    }

    return value;
  }

  /*============================================================================
    valueTwoPairs
        Determines the value of a hand if assuming it has two pairs

    Revision History
        14 June, 2015 - function created
  *///==========================================================================
  int PokerHand::valueTwoPairs(Hand& hand)
                               // array of cards making up a hand
  {
    PokerHand::rankSort(hand);
    
    int value;
    // where the pairs are and value accordingly
    if (hand[0].getRank() == hand[1].getRank() &&
        hand[2].getRank() == hand[3].getRank())
    {
      value = 14 * 14 * static_cast<int>(hand[2].getRank()) +
        14 * static_cast<int>(hand[0].getRank()) +
        static_cast<int>(hand[4].getRank());
    }
    else if (hand[0].getRank() == hand[1].getRank() &&
             hand[3].getRank() == hand[4].getRank())
    {
      value = 14 * 14 * static_cast<int>(hand[3].getRank()) +
        14 * static_cast<int>(hand[0].getRank()) +
        static_cast<int>(hand[2].getRank());
    }
    else
    {
      value = 14 * 14 * static_cast<int>(hand[3].getRank()) +
        14 * static_cast<int>(hand[1].getRank()) +
        static_cast<int>(hand[0].getRank());
    }
    
    return  PokerHand::TWO_PAIRS + value;
  }  
  
  /*============================================================================
    operator<<
        Returns a human readable representation of a poker hand

    Note
        Only works inside hw2 namespace

    Revision History
        10 June, 2015 - function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, // the desired output stream
                           const PokerHand::Hand&  hand)
                           // array of cards making up a hand
  {
   
    std::array<std::string, PokerHand::SIZE> strings;

    std::transform(hand.begin(), hand.end(), strings.begin(),
                   [](const PlayingCard& card) -> std::string
                   {
                     std::stringstream ss;
                     ss << card;
                     return ss.str();
                   });

    out << "[" + boost::algorithm::join(strings, ", ") + "]";
    
    return out;
  }
    
}; // namespace hw2
