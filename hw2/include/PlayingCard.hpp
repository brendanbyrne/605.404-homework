/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 9 June, 2015
  
  Revision History:
      9 June, 2015 - class created
      10 June, 2015 - operator<< override provided
  
  Class Name: PlayingCard.hpp
  
  Intent: To contain and organize state information about a playing card
  
  Description: This file defines the PlayingCard class which maintains the
               state information of a traditional vegas style playing card. A
	       PlayingCard has a Suit and Value, both expressed as enums.
  
*///============================================================================

#ifndef PLAYING_CARD_HPP
#define PLAYING_CARD_HPP

#include <ostream>

namespace hw2
{

  class PlayingCard
  {
  public:
    enum class Rank {TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN,
	EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};

    enum class Suit : int{SPADES, CLUBS, HEARTS, DIAMONDS};

    PlayingCard();
    PlayingCard(Rank, Suit);
    PlayingCard(const int, const int);
    Rank getRank() const;
    Suit getSuit() const;
    void setRank(Rank&);
    void setSuit(Suit&);
    
  private:    
    Rank rank;
    Suit suit;
    
  }; //PlayingCard

  /*============================================================================
    getRank
        Returns the rank of the card

    Revision History:
        9 June, 2015 - function created
  *///==========================================================================
  inline PlayingCard::Rank PlayingCard::getRank() const
  {
    return this->rank;
  }

  /*============================================================================
    getSuit
        Returns the suit of the card

    Revision History:
        9 June, 2015 - function created
  *///==========================================================================
  inline PlayingCard::Suit PlayingCard::getSuit() const
  {
    return this->suit;
  }

  /*============================================================================
    setRank
        Sets the "rank" data member to the input value

    Revision History:
        14 June, 2015 - function created
  *///==========================================================================
  inline void PlayingCard::setRank(Rank& rank)
  {
    this->rank = rank;
  }

  /*============================================================================
    setSuit
        Sets the "suit" data member to the input value

    Revision History:
        14 June, 2015 - function created
  *///==========================================================================
  inline void PlayingCard::setSuit(Suit& suit)
  {
    this->suit = suit;
  }
  
  std::ostream& operator<<(std::ostream&, const PlayingCard::Suit&);
  std::ostream& operator<<(std::ostream&, const PlayingCard::Rank&);
  std::ostream& operator<<(std::ostream&, const PlayingCard&);
  
} // namespace hw2



#endif // PLAYING_CARD_HPP
