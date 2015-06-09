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
  const std::string name;
  Tile::State symbol;
  const bool isAI;
  const Gameboard* board_ptr;

  void getAIInput(std::pair<int, int>&);
  void getHumanInput(std::pair<int, int>&);
  bool isValidInput(const std::string&, std::pair<int, int>&);
  bool isValidInt(const std::string&, int& candidate);
  bool isInBounds(const int);
		    
};

} // namespace hw1

#endif //OPPONENT_HPP_
