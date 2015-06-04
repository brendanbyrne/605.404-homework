#include <iostream>

#include "gridspace.h"
#include "gameboard.h"

int main()
{  
  Gameboard *board_ptr = new Gameboard(3);
  board_ptr->print(std::cout);
  std::cout<<std::endl;
  delete board_ptr;
  
  return 0;
}
