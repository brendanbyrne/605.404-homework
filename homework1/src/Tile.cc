// Tile.cc
//
#include <sstream>

#include "Tile.hpp"

namespace hw1
{

Tile::Tile(State state)
{
  this->state = state;
}

//******************************************************************
// Tile::State getState()
// Purpose: report the state of the tile
//******************************************************************
Tile::State Tile::getState() const
{
  return this->state;
}

//******************************************************************
// void setState()
// Purpose: set the state of the tile
// Input: The desired tile state
//******************************************************************
void Tile::setState(State state)
{
  this->state = state;
}

//******************************************************************
// void str()
// Purpose: return the tile state as a string
// Note: The string forms are expressed as cases in the switch
//******************************************************************
// I originally implimented this with a map : state -> string
// but I couldn't figure out the complaints I was getting
// because this is a const function
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
    
  default:
    ss << "ERROR";
  }
  ss << " ";
  return ss.str();
}

} // namespace hw1
