// GameState.hpp
//
#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <ostream>
#include <map>
#include <vector>

#include "Gameboard.hpp"
#include "Tile.hpp"
#include "Opponent.hpp"

namespace hw1
{
  
class GameState
{
public:  
  GameState(const int);
  void startGame();
  void addPlayer(Opponent&);
  const Gameboard* getGameboardPtr();
  
private:
  Gameboard gameboard;
  std::vector<Opponent> opponents;
  std::vector<Opponent>::iterator player;
    
  bool isValidInt(const std::string&, int&);
  bool isInBounds(const int);
  bool isValidUserInput(const std::string&, std::pair<int, int>&);
  bool isGameOver(std::vector<Opponent>::iterator&, std::pair<int, int>);
  
};

} // namespace hw1
#endif //GAMESTATE_HPP_
