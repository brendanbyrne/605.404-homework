#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include <vector>
#include <ostream>

#include "gridspace.h"

class Gameboard {
private:
  std::vector< std::vector<Gridspace> > board;
  const int size;
  
public:
  Gameboard(int);
  int GetSize();
  std::vector<std::vector<Gridspace>> GetBoard();
  void str(std::ostream& output_stream);
};

#endif // GAMEBOARD_H_
