#ifndef GAMEBOARD_HPP_
#define GAMEBOARD_HPP_

#include <vector>
#include <ostream>
#include <utility>

#include "tile.hpp"

class Gameboard {
public:
  std::vector<std::vector<Tile>>* GetBoard();
  
  Gameboard(int);
  int GetSize();
  void SetTile(int, int, Tile::State);
  std::vector<std::pair<int,int>> GetOpenTiles();
  std::vector<std::pair<int,int>> TestOpenTiles();
  
  void print(std::ostream&);  
  
private:
  std::vector< std::vector<Tile> > board;
};

#endif // GAMEBOARD_HPP_
