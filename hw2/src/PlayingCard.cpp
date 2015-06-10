// PlayingCard.cpp - Functions for using a Vegas style playing card

#include "PlayingCard.hpp"

namespace hw2
{
  PlayingCard::PlayingCard() {};
  
  PlayingCard::PlayingCard(Suit suit, Rank rank):
    suit(suit), rank(rank)
  {
  }
  
  PlayingCard::Suit PlayingCard::getSuit() const
  {
    return this->suit;
  }
  
  PlayingCard::Rank PlayingCard::getRank() const
  {
    return this->rank;
  }
  
  /*
  std::string PlayingCard::str() const
  {
    const std::string RANK = PlayingCard::rankToStr[this->rank];
    const std::string SUIT = PlayingCard::suitToStr[this->suit];
    return SUIT + " of " + RANK;
  }
  */
  
  
}; // namespace hw2
