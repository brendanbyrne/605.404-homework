#ifndef GRIDSPACE_H_
#define GRIDSPACE_H_

#include <ostream>
#include <map>

class Gridspace {
public:
  enum State {kEmpty, kCross, kCircle};
  State GetState();
  void SetState( State state );
  void str( std::ostream& output_stream );

private:
  State state = kEmpty;
  std::map<State, const char> gs2c_map = {{kEmpty,' '}, {kCross,'X'}, {kCircle,'O'}};
  
};
  

#endif //GRIDSPACE_H_
