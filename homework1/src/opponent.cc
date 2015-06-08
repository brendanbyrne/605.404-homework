#include <stdexcept>
#include <iostream>
#include <random>
#include <boost/algorithm/string.hpp>

#include "opponent.hpp"

Opponent::Opponent(const std::string& name,
		   Tile::State symbol,
		   const bool isAI,
		   const Gameboard* gameboard):
  name(name), isAI(isAI), board_ptr(gameboard)
{
  this->symbol = symbol;
}

std::pair<int, int> Opponent::makeMove()
{
  std::pair<int, int> coordinate;
  if (isAI)
  {
    this->getAIInput(coordinate);
  }
  else
  {
    this->getHumanInput(coordinate);
  }
  return coordinate;
}

Tile::State Opponent::getSymbol() const
{
  return this->symbol;
}

const std::string Opponent::getName()
{
  return this->name;
}

void Opponent::getAIInput(std::pair<int, int>& coordinate)
{
  std::vector<std::pair<int, int>> open_tiles = this->board_ptr->getOpenTiles();
  int random_index = rand() % open_tiles.size();
  coordinate = open_tiles[random_index];  
}

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

bool Opponent::isValidInput(const std::string& input, std::pair<int, int>& coordinate)
{
  const std::string delimiters = " ";

  std::vector<std::string> tokens;
  boost::split(tokens, input, boost::is_any_of(delimiters));

  if (tokens.size() != this->DIMENSIONS)
  {
    std::cout << "Incorrect number of inputs" << std::endl;
    return false;
  }

  std::vector<int> valid_inputs;
  for (auto& str : tokens)
  {
    int candidate;
    if (this->isValidInt(str, candidate))
    {
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
  
  //minus 1 because collection starts at 0 not 1
  coordinate = std::pair<int,int>(valid_inputs[0]-1, valid_inputs[1]-1);
  
  if (this->board_ptr->getTileState(coordinate.first, coordinate.second) != Tile::State::EMPTY)
  {
    std::cout << "Space already taken" << std::endl;
    return false;
  }

  return true;
}

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
