#ifndef TILE_HPP_
#define TILE_HPP_

#include <ostream>
#include <map>

class Tile {
public:
  enum State {kEmpty, kCross, kCircle};

  Tile();
  Tile(State);
  State GetState();
  void SetState( State );
  void print( std::ostream& );

private:
  State state = kEmpty;
  std::map<State, const char> ts2c_map = {{kEmpty,' '}, {kCross,'X'}, {kCircle,'O'}};
};
  

#endif //TILE_HPP_
