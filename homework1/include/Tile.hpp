/////////// Tile.hpp
//
#ifndef TILE_HPP_
#define TILE_HPP_

#include <string>

namespace hw1
{
  
class Tile {
public:
  enum State {EMPTY, CROSS, CIRCLE};  // possible states of a tile.  There must be a
                                      // unique non empty state for every player
  
  Tile(State);
  State getState() const;
  void setState(State);
  std::string str() const;

private:
  State state;
};
  
} // namespace hw1
#endif //TILE_HPP_
