#include "tictactoe.hpp"
#include "tile.hpp"

//test includes

int main()
{
  int board_size = 3;

  // initialize game
  TicTacToe game(board_size);

  // build players
  Opponent me("Human", Tile::State::CROSS, false, game.getGameboardPtr());
  Opponent ai("Computer", Tile::State::CIRCLE, true, game.getGameboardPtr());
  
  game.addPlayer(me);
  game.addPlayer(ai);

  game.startGame();  
  
  return 0;
}
