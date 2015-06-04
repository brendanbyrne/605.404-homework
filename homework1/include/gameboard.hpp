#ifndef GAMEBOARD_HPP_
#define GAMEBOARD_HPP_

#include <vector>
#include <ostream>
#include <utility>

#include "gridspace.hpp"

class Gameboard {
public:
  std::vector<std::vector<Gridspace>> GetBoard();
  
  Gameboard(int size);
  int GetSize();
  std::vector<std::pair<int,int>> GetOpenGrids();
  
  void print(std::ostream& output_stream);
  
  
private:
  std::vector< std::vector<Gridspace> > board;
};

#endif // GAMEBOARD_HPP_
