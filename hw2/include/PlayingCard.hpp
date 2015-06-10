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
    enum class Suit {SPADES, CLUBS, HEARTS, DIAMONDS};
    
    enum class Rank {TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN,
	EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
    
    PlayingCard(Rank, Suit);
    PlayingCard::Rank getRank() const;
    PlayingCard::Suit getSuit() const;
    
  private:    
    Rank rank;
    Suit suit;
    
  }; //PlayingCard

  std::ostream& operator<<(std::ostream&, const PlayingCard::Suit&);
  std::ostream& operator<<(std::ostream&, const PlayingCard::Rank&);
  std::ostream& operator<<(std::ostream&, const PlayingCard&);
  
} // namespace hw2



#endif // PLAYING_CARD_HPP
