#ifndef OPPONENT_HPP_
#define OPPONENT_HPP_

#include "tile.hpp"

class Opponent
{
public:
  std::pair<int,int> ChooseNextPosition(std::vector<std::vector<Tile>>);
  
  

#endif //OPPONENT_HPP_
