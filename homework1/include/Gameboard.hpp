// Gameboard.hpp
//
#ifndef GAMEBOARD_HPP_
#define GAMEBOARD_HPP_

#include <vector>
#include <ostream>
#include <utility>
#include <string>

#include "Tile.hpp"

namespace hw1
{
  
class Gameboard
{
public:
  const static int NUM_DIMENSIONS = 2;
  
  std::vector<std::vector<Tile>>* GetBoard();
  
  Gameboard(const int);
  void setTileState(const int, const int, const Tile::State); 
  Tile::State getTileState(const int, const int) const;
  std::vector<std::pair<int,int>> getOpenTiles() const;  
  bool rowHasWin(const int);
  void printTo(std::ostream&) const;
  int getSize() const;

private:
  const static int PRETTY_PRINT_FACTOR = 4; // found experimentally
  std::vector< std::vector<Tile> > board;
};

} // hw1
#endif // GAMEBOARD_HPP_
