#ifndef OPPONENT_HPP_
#define OPPONENT_HPP_

#include <utility>
#include <string>

#include "gameboard.hpp"
#include "tile.hpp"

class Opponent
{
public:
  Opponent(const std::string&, Tile::State, const bool, const Gameboard*);
  std::pair<int, int> makeMove();
  Tile::State getSymbol() const;
  const std::string getName();
  
private:
  const static int DIMENSIONS = 2;
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
#endif //OPPONENT_HPP_
