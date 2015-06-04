#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include <vector>
#include <ostream>

#include "gridspace.h"

class Gameboard {
public:
  Gameboard(int size);
  int GetSize();
  std::vector<std::vector<Gridspace>> GetBoard();
  void print(std::ostream& output_stream);
  
private:
  std::vector< std::vector<Gridspace> > board;
};

#endif // GAMEBOARD_H_
