#include "gridspace.h"

Gridspace::State Gridspace::GetState()
{
  return this->state;
}

void Gridspace::SetState(State state)
{
  this->state = state;
}

void Gridspace::str(std::ostream& output_stream)
{
  output_stream << " " << this->gs2c_map[this->state] << " " << std::endl;
}
