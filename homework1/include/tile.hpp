#ifndef TILE_HPP_
#define TILE_HPP_

#include <ostream>
#include <map>
#include <string>

class Tile {
public:
  enum State {EMPTY, CROSS, CIRCLE};
  
  Tile();
  Tile(State);
  State getState();
  void setState(State);
  std::string str();

private:
  State state;
  std::map<State, const char*> ts2c_map = {{EMPTY, " "}, {CROSS, "X"}, {CIRCLE, "O"}};
};
  

#endif //TILE_HPP_
