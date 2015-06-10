/*==============================================================================

Author: Brendan Byrne

Date: 9 June, 2015

Revision History:
    9 June, 2015 - class created

Class Name: PlayingCard.hpp

Intent: To contain and organize state information about a playing card

Description: This file contains the class Card which maintains the state
             information of a traditional vegas style playing card.  A Card has
	     a Suit and Value, both expressed as enums.

*///============================================================================

#ifndef PLAYING_CARD_HPP
#define PLAYING_CARD_HPP

#include <string>
#include <map>
#include <boost/assign/list_of.hpp> // for 'map_list_of'

namespace hw2
{

  class PlayingCard
  {
  public:
    enum class Suit {SPADES, CLUBS, HEARTS, DIAMONDS};
    
    enum class Rank {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
	             EIGHT, NINE, TEN, JACK, QUEEN, KING};
    
    typedef std::map<Suit, std::string> SuitMap;
    typedef std::map<Rank, std::string> RankMap;

    

    PlayingCard();
    PlayingCard(Suit, Rank);
    PlayingCard::Suit getSuit() const;
    //void setSuit();
    PlayingCard::Rank getRank() const;
    //void setRank(Rank);
    //std::string str() const;
    
  private:
    
    static const SuitMap suitToStr = boost::assign::map_list_of(Suit::SPADES, "Spades");
      //(Suit::CLUBS, "Clubs"), (Suit::HEARTS, "Hearts") (Suit::DIAMONDS, "Diamonds");
    
    
    static const RankMap rankToStr = { {Rank::ACE, "Ace"} };/*,
				       {Rank::TWO, "2"},
				       {Rank::THREE, "3"},
				       {Rank::FOUR, "4"},
				       {Rank::FIVE, "5"},
				       {Rank::SIX, "6"},
				       {Rank::SEVEN, "7"},
				       {Rank::EIGHT, "8"},
				       {Rank::NINE, "9"},
				       {Rank::TEN, "10"},
				       {Rank::JACK, "Jack"},
				       {Rank::QUEEN, "Queen"},
				       {Rank::KING, "King"} };
    */
    Suit suit;
    Rank rank;
  }; //PlayingCard

} // namespace hw2

#endif // PLAYING_CARD_HPP
