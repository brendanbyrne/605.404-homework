#include "gridspace.hpp"

Gridspace::State Gridspace::GetState()
{
  return this->state;
}

void Gridspace::SetState(State state)
{
  this->state = state;
}

void Gridspace::print(std::ostream& output_stream)
{
  output_stream << " " << this->gs2c_map[this->state] << " ";
}
