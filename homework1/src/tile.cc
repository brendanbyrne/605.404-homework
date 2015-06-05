#include "tile.hpp"

Tile::Tile(){}

Tile::Tile(State state)
{
  this->state = state;
}

Tile::State Tile::GetState()
{
  return this->state;
}

void Tile::SetState(State state)
{
  this->state = state;
}

void Tile::print(std::ostream& output_stream)
{
  output_stream << " " << this->ts2c_map[this->state] << " ";
}
