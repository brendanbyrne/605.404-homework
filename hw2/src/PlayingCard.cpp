// PlayingCard.cpp - Functions for using a Vegas style playing card

#include "PlayingCard.hpp"

namespace hw2
{
  /*============================================================================

    PlayingCard
        Constructor for a PlayingCard object
    
  *///==========================================================================

  PlayingCard::PlayingCard(Rank rank, // The desired rank of the card
			   Suit suit):// the desired suit of the card
    suit(suit), rank(rank)
  {}

  /*============================================================================

    getRank
        Returns the rank of the card
	
  *///==========================================================================

  PlayingCard::Rank PlayingCard::getRank() const
  {
    return this->rank;
  }
  
  /*============================================================================

    getSuit
        Returns the suit of the card
	
  *///==========================================================================
  PlayingCard::Suit PlayingCard::getSuit() const
  {
    return this->suit;  
  }
  
  /*============================================================================

    str
        Returns a human readable representation of the card
	
  *///==========================================================================
  std::string PlayingCard::str() const
  {
    const std::string RANK = this->rankToStr.at(this->rank);
    const std::string SUIT = this->suitToStr.at(this->suit);
    return RANK + " of " + SUIT;
  }
  
}; // namespace hw2
