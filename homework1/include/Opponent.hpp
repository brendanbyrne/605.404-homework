// Opponent.hpp
//
#ifndef OPPONENT_HPP_
#define OPPONENT_HPP_

#include <utility>
#include <string>

#include "Gameboard.hpp"
#include "Tile.hpp"

namespace hw1
{
  
class Opponent
{
public:
  Opponent(const std::string&, Tile::State, const bool, const Gameboard*);
  std::pair<int, int> makeMove();
  Tile::State getSymbol() const;
  const std::string getName();
  
private:
  const std::string name; // human readable name of player
  Tile::State symbol;  // The Tile::State that is associated with the player
  const bool isAI; // flag for whether or not this player is a computer
  const Gameboard* board_ptr; // a pointer used to look at the game board
                              // used by the ai to help make decisions

  void getAIInput(std::pair<int, int>&);
  void getHumanInput(std::pair<int, int>&);
  bool isValidInput(const std::string&, std::pair<int, int>&);
  bool isValidInt(const std::string&, int& candidate);
  bool isInBounds(const int);
		    
};

} // namespace hw1

#endif //OPPONENT_HPP_
