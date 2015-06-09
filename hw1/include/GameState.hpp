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
  Gameboard gameboard;  // where the state of the board is stored
  std::vector<Opponent> opponents; // the different people playing
  std::vector<Opponent>::iterator player; // the user whos turn turn it is
    
  bool isValidInt(const std::string&, int&);
  bool isInBounds(const int);
  bool isValidUserInput(const std::string&, std::pair<int, int>&);
  bool isGameOver(std::vector<Opponent>::iterator&, std::pair<int, int>);
  
};

} // namespace hw1
#endif //GAMESTATE_HPP_
