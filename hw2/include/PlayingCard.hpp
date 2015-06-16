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
    // enum to represent the rank NOT the value of card
    enum class Rank {TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN,
	EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};

    // neum to represt the suit of the card
    enum class Suit : int{SPADES, CLUBS, HEARTS, DIAMONDS};

    PlayingCard(); // default construct
    PlayingCard(Rank, Suit); // enum based constructor
    PlayingCard(const int, const int); //
    Rank getRank() const; // rank getter function
    Suit getSuit() const; // suit getter function
    void setRank(Rank&); // rank setter function
    void setSuit(Suit&); // suit setter function
    
  private:    
    Rank rank; // attribute that holds the card's rank
    Suit suit; // attribute that holds the card's suit
    
  }; // class PlayingCard

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

  //  << overloading in the hw2 namespace i.e. using hw2::operator<<
  // overloads for Suit, Rank, and PlayingCard objects
  std::ostream& operator<<(std::ostream&, const PlayingCard::Suit&);
  std::ostream& operator<<(std::ostream&, const PlayingCard::Rank&);
  std::ostream& operator<<(std::ostream&, const PlayingCard&);
  
} // namespace hw2



#endif // PLAYING_CARD_HPP
