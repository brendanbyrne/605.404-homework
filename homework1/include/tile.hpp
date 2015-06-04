#ifndef TILE_HPP_
#define TILE_HPP_

#include <ostream>
#include <map>

class Tile {
public:
  enum State {kEmpty, kCross, kCircle};
  State GetState();
  void SetState( State state );
  void print( std::ostream& output_stream );

private:
  State state = kEmpty;
  std::map<State, const char> ts2c_map = {{kEmpty,' '}, {kCross,'X'}, {kCircle,'O'}};
};
  

#endif //TILE_HPP_