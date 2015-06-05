#include "tictactoe.hpp"

// Test includes
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <vector>

int main()
{
  int board_size = 3;
  
  TicTacToe game(board_size);
  game.StartGame();  
  
  return 0;
}
