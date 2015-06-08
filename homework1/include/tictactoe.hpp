#ifndef TICTACTOE_HPP_
#define TICTACTOE_HPP_

#include <ostream>
#include <map>

#include "gameboard.hpp"
#include "tile.hpp"

class TicTacToe
{
public:
  enum Player {NOONE, PLAYER_ONE, PLAYER_TWO};
  
  TicTacToe(int);
  void StartGame();

private:
  const static int DIMENSIONS = 2;
  Gameboard gameboard;
  Player current_player;
  std::map<Player, Tile::State> player_to_state = {{PLAYER_ONE, Tile::State::CROSS},
						 {PLAYER_TWO, Tile::State::CIRCLE}};
  std::map<Tile::State, Player> state_to_player = {{Tile::State::CROSS, PLAYER_ONE},
						 {Tile::State::CIRCLE, PLAYER_TWO}};
  
  bool isValidInt(const std::string&, int&);
  bool isInBounds(const int);
  bool isValidUserInput(const std::string&, std::pair<int, int>&);
  bool isGameOver(Player&);
  bool isGameOver(Player&, std::pair<int, int>);
  std::pair<int, int> getPlayerInput();
  
};

#endif //TICTACTOE_HPP_
