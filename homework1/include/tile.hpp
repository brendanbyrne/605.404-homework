#ifndef TILE_HPP_
#define TILE_HPP_

#include <string>

class Tile {
public:
  enum State {EMPTY, CROSS, CIRCLE};
  
  Tile();
  Tile(State);
  State getState() const;
  void setState(State);
  std::string str() const;

private:
  State state;
};
  

#endif //TILE_HPP_
