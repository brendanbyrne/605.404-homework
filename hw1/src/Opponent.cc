//Opponent.cc
//
#include <stdexcept>
#include <iostream>
#include <random>
#include <boost/algorithm/string.hpp>

#include "Opponent.hpp"

namespace hw1
{
  
Opponent::Opponent(const std::string& name,
		   Tile::State symbol,
		   const bool isAI,
		   const Gameboard* gameboard):
  name(name), isAI(isAI), board_ptr(gameboard)
{
  this->symbol = symbol;
}

//******************************************************************
// std::pair<int, int> makeMove()
// Purpose: Ask either a human or the AI for their next move
// Input: None
// Output: A set of coordinates (row, column)
//******************************************************************
std::pair<int, int> Opponent::makeMove()
{
  std::pair<int, int> coordinate;
  if (this->isAI)
  {
    this->getAIInput(coordinate);
  }
  else
  {
    this->getHumanInput(coordinate);
  }
  return coordinate;
}

//******************************************************************
// Tile::State getSymbol()
// Purpose: return the Tile::State that is associated with a player
// Input: None
// Output: The Tile::State that this player will
//******************************************************************
Tile::State Opponent::getSymbol() const
{
  return this->symbol;
}

//******************************************************************
// const std::string getName()
// Purpose: supply a human friendly name of the player
// Input: None
// Output: a string with the name
//******************************************************************
const std::string Opponent::getName()
{
  return this->name;
}

//******************************************************************
// void getAIInput(std::pair<int, int>& coordinate)
// Purpose: Choose the location for the AI to make its moves
// Input: a referenced (row, col) coordinate
// Output: Nothing returned, choice is saved to referenced input
//******************************************************************
void Opponent::getAIInput(std::pair<int, int>& coordinate)
{
  // Find the open spaces in on the board
  std::vector<std::pair<int, int>> open_tiles = this->board_ptr->getOpenTiles();

  //choose a random one
  int random_index = rand() % open_tiles.size();

  // and assign it as the AI decision
  coordinate = open_tiles[random_index];  
}

//******************************************************************
// void getHumanInput(std::pair<int, int>& coordinate)
// Purpose: ask a human where they want to move
// Input: a referenced (row, col) coordinate
// Output: Nothing returned, choice is saved to referenced input
//******************************************************************
void Opponent::getHumanInput(std::pair<int, int>& coordinate)
{
  std::string input;
  
  // do while input is invalid
  do
  {
    // Prompt user
    std::cout << "Input desired row and column location ex. \"1 1\": ";
    getline(std::cin, input);
  
  } while(this->isValidInput(input, coordinate) != true);
}

//******************************************************************
// bool isValidInput(const std::string& input, std::pair<int,int>& coordinate)
// Purpose: check to see if the received human input is valid
// Input: the human input and a container to receive the validated location
// Output: a bool that is true if the input is vaild
//******************************************************************
bool Opponent::isValidInput(const std::string& input, std::pair<int, int>& coordinate)
{
  const std::string delimiters = " ";
  
  // split input up by spaces
  std::vector<std::string> tokens;
  boost::split(tokens, input, boost::is_any_of(delimiters));

  // make sure there are enough inputs
  if (tokens.size() != Gameboard::NUM_DIMENSIONS)
  {
    std::cout << "Incorrect number of inputs" << std::endl;
    return false;
  }

  // check all the parsed tokens
  std::vector<int> valid_inputs;
  for (auto& str : tokens)
  {
    // if the token is an int
    int candidate;
    if (this->isValidInt(str, candidate))
    {
      // and is within the range of the gameboard
      if (this->isInBounds(candidate))
      {
	valid_inputs.push_back(candidate);
      }
      else
      {
	std::cout << "An input is too large or small" << std::endl;
	return false;
      }
    }
    else
    {
      std::cout << "Input contains a non integer value" << std::endl;
      return false;
    }
  }
  
  //convert from input space [1...] to [0...]
  coordinate = std::pair<int,int>(valid_inputs[0]-1, valid_inputs[1]-1);
  
  // finally, make sure the space is free
  if (this->board_ptr->getTileState(coordinate.first, coordinate.second) != Tile::State::EMPTY)
  {
    std::cout << "Space already taken" << std::endl;
    return false;
  }

  return true;
}


//******************************************************************
// bool isValidInt(const std::string& input, int& candidate)
// Purpose: check to see if part of the received human input is an int
// Input: a token parseed from the human input
//        a container to receive the validated int
// Output: a bool that is true if the str is an int
//******************************************************************
bool Opponent::isValidInt(const std::string& str, int& candidate)
{
  try
  {
    candidate = stoi(str);
  }
  catch(...)
  {
    return false;
  }
  return true;
}

//******************************************************************
// bool isInBounds(const int candidate)
// Purpose: check to see if value is within range of gameboard
// Input: potential row or column value
// Output: a bool that is true when the value is within the bounds
//******************************************************************
bool Opponent::isInBounds(const int candidate)
{
  if (1 <= candidate && candidate <= this->board_ptr->getSize())
  {
    return true;
  }
  else
  {
    return false;
  }
}

} // namespace hw1
