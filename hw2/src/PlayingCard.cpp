// PlayingCard.cpp - Functions for using a Vegas style playing card

#include <string>

#include "PlayingCard.hpp"

namespace hw2
{
  /*============================================================================
    PlayingCard
        Default Constructor for a PlayingCard object
	
    Revision History:
        15 June, 2015 - function created

    Note:
        Added for support of Hand typedef in the pokerhand class
  *///==========================================================================
  PlayingCard::PlayingCard(){}
  
  /*============================================================================
    PlayingCard
        Constructor for a PlayingCard object
	
    Revision History:
        9 June, 2015 - function created
  *///==========================================================================
  PlayingCard::PlayingCard(Rank rank, // The desired rank of the card
   			   Suit suit):// the desired suit of the card
    rank(rank), suit(suit)
   {
   }

  /*============================================================================
    PlayingCard
        Constructor for a PlayingCard object that takes in ints and converts to
	the correct enum types
	
    Revision History:
        11 June, 2015 - function created
  *///==========================================================================
  PlayingCard::PlayingCard(const int rankNumber, //Desired rank as an int
  			   const int suitNumber)://Desired rank as an int
    PlayingCard(static_cast<Rank>(rankNumber),
  		static_cast<Suit>(suitNumber))
  {
  }
  
  /*============================================================================
    operator<<
        Returns a human readable representation of a card's rank

    Note:
        Only works inside hw2 namespace useless combined with "using"

    Revision History:
       10 June, 2015 - function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, // the desired output stream
			   const PlayingCard::Rank& rank) // the rank to output
  {
    std::string name;
    switch(rank)
    {
    case PlayingCard::Rank::ACE:
      name = "Ace";
      break;

    case PlayingCard::Rank::TWO:
      name = "2";
      break;

    case PlayingCard::Rank::THREE:
      name = "3";
      break;

    case PlayingCard::Rank::FOUR:
      name = "4";
      break;

    case PlayingCard::Rank::FIVE:
      name = "5";
      break;
      
    case PlayingCard::Rank::SIX:
      name = "6";
      break;

    case PlayingCard::Rank::SEVEN:
      name = "7";
      break;

    case PlayingCard::Rank::EIGHT:
      name = "8";
      break;

    case PlayingCard::Rank::NINE:
      name = "9";
      break;

    case PlayingCard::Rank::TEN:
      name = "10";
      break;

    case PlayingCard::Rank::JACK:
      name = "Jack";
      break;
      
    case PlayingCard::Rank::QUEEN:
      name = "Queen";
      break;

    case PlayingCard::Rank::KING:
      name = "King";
      break;

    default:
      name = "Rank does not have a name";
    }

    out << name;
    return out;    
  }

  /*============================================================================
    operator<<
        Returns a human readable representation of a card's suit

    Note:
        Only works inside hw2 namespace useless combined with "using"

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, // the desired output stream
			   const PlayingCard::Suit& suit) // the suit to output
  {
    std::string name;
    switch (suit)
    {
    case PlayingCard::Suit::SPADES:
      name = "Spades";
      break;

    case PlayingCard::Suit::CLUBS:
      name = "Clubs";
      break;

    case PlayingCard::Suit::HEARTS:
      name = "Hearts";
      break;
      
    case PlayingCard::Suit::DIAMONDS:
      name = "Diamonds";
      break;
      
    default:
      name = "Suit does not have a name";
    }

    out << name;
    return out;
  }
  
  /*============================================================================
    operator<<
        Returns a human readable representation of the card

    Note:
        Only works inside hw2 namespace useless combined with "using"

    Revision History:
        10 June, 2015 - function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, // desired output stream
			   const PlayingCard& card) // card object to output
  {
    out << card.getRank() << " of " << card.getSuit();
    return out;
  }
  
}; // namespace hw2
