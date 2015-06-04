#include <iostream>
#include <utility>

#include "gameboard.hpp"
#include "tictactoe.hpp"

int main()
{ 
  int board_size = 3;
  std::ostream *output = &std::cout;
  TicTacToe* game_ptr = new TicTacToe(output, board_size);
  
  game_ptr->StartGame();
  
  
  Gameboard* board_ptr = new Gameboard(board_size);
  
  board_ptr->SetTile(1,1,Tile::State::kCross);  
  
  board_ptr->print(std::cout);
  std::cout << std::endl;
  
  std::vector<std::pair<int,int>> open_tiles = board_ptr->GetOpenTiles();
  
  for (std::pair<int,int>& coordinate: open_tiles)
  {
    std::cout << coordinate.first << " " << coordinate.second << std::endl;
  }
  
  delete board_ptr;
  delete game_ptr;

  return 0;
}
