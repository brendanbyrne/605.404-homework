#include <iostream>
#include <utility>

#include "gameboard.hpp"

int main()
{ 
  int board_size = 3;
  
  Gameboard *board_ptr = new Gameboard(board_size);
  board_ptr->print(std::cout);
  //std::vector<std::pair<int,int>> opentiles;
  //opentiles = board_ptr->GetOpenTiles();
  
  delete board_ptr;
  
  return 0;
}
