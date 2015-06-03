#include <iostream>

#include "gridspace.h"
#include "gameboard.h"

int main()
{  
  Gridspace *gridspace_prt = new Gridspace();
  gridspace_prt->str(std::cout);
  
  gridspace_prt->SetState(Gridspace::State::kCross);
  gridspace_prt->str(std::cout);

  gridspace_prt->SetState(Gridspace::State::kCircle);
  gridspace_prt->str(std::cout);
  
  return 0;
}
