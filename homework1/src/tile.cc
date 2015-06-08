#include <sstream>

#include "tile.hpp"

Tile::Tile(){}

Tile::Tile(State state)
{
  this->state = state;
}

Tile::State Tile::getState()
{
  return this->state;
}

void Tile::setState(State state)
{
  this->state = state;
}

std::string Tile::str()
{
  std::stringstream ss;
  ss << " " << this->ts2c_map[this->state] << " ";
  return ss.str();
}
