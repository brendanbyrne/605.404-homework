#include <iostream>

#include "tictactoe_gamestate.h"

int main()
{  
  TicTacToeGameState *game_ptr = new TicTacToeGameState();
  game_ptr->PrintBoard(std::cout);
  return 0;  
}
