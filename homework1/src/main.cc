#include <iostream>

#include "gridspace.hpp"
#include "gameboard.hpp"

int main()
{ 
  int board_size = 3;
  
  Gameboard *board_ptr = new Gameboard(board_size);
  board_ptr->print(std::cout);
  std::cout<<std::endl;
  
  
  
  delete board_ptr;
  
  return 0;
}
