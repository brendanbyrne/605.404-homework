#ifndef GAMEBOARD_HPP_
#define GAMEBOARD_HPP_

#include <vector>
#include <ostream>
#include <utility>

#include "tile.hpp"

class Gameboard {
public:
  std::vector<std::vector<Tile>> GetBoard();
  
  Gameboard(int size);
  int GetSize();
  std::vector<std::pair<int,int>> GetOpenTiles();
  
  void print(std::ostream& output_stream);
  
  
private:
  std::vector< std::vector<Tile> > board;
};

#endif // GAMEBOARD_HPP_
