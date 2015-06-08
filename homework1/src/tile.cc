#include <sstream>

#include "tile.hpp"

Tile::Tile(){}

Tile::Tile(State state)
{
  this->state = state;
}

Tile::State Tile::getState() const
{
  return this->state;
}

void Tile::setState(State state)
{
  this->state = state;
}

std::string Tile::str() const
{  
  std::stringstream ss;
  ss << " ";
  switch (this->state)
  {
  case(EMPTY):
    ss << " ";
    break;
  case(CROSS):
    ss << "X";
    break;
  case(CIRCLE):
    ss << "O";
    break;
  }
  ss << " ";
  return ss.str();
}
