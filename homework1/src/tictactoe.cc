#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <stdexcept>

#include <boost/algorithm/string.hpp>

#include "tictactoe.hpp"

TicTacToe::TicTacToe(int size)
{
  this->board_ptr = new Gameboard(size);
  this->state = kInitialized;
}

TicTacToe::~TicTacToe()
{
  delete this->board_ptr;
}

bool IsValidInt(const std::string& str, int& candidate)
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

bool IsInBounds(const int candidate, int size)
{
  if (1 <= candidate && candidate <= size)
  {
    return true;
  }
  else
  {
    std::cout << "An input is too large or small" << std::endl;
    return false;
  }
}

bool IsValidUserInput(const std::string& user_input, Coordinate& coordinate, const int board_size)
{
  const std::string delimiters = " ";

  std::vector<std::string> tokens;
  boost::split(tokens, user_input, boost::is_any_of(delimiters));

  int num_dimensions = 2;
  if (tokens.size() != num_dimensions)
  {
    std::cout << "Incorrect number of inputs" << std::endl;
    return false;
  }

  std::vector<int> valid_inputs;
  
  for (auto& str : tokens)
  {    
    int candidate;
    if (IsValidInt(str, candidate) && IsInBounds(candidate, board_size))
    {
      valid_inputs.push_back(candidate);
    }
    else
    {
      std::cout << "Input contains a non integer value" << std::endl;
      return false;
    }
  }

  coordinate = Coordinate(valid_inputs[0]-1, valid_inputs[1]-1);
  return true;    
}

Coordinate GetPlayerInput(const TicTacToe::Player current_player, const int board_size)
{
  
  Coordinate coordinate;
  std::cout << "\nPlayer " << current_player << std::endl;

  std::string user_input;
  
  // do while input is invalid  
  do
  {
    // Prompt user
    std::cout << "Input desired row and col location ex. \"1 1\": ";
    getline(std::cin, user_input);
  }// check if input is valid
  while (IsValidUserInput(user_input, coordinate, board_size) != true);
  // return coordinate as pair
  return coordinate;
}

void TicTacToe::StartGame()
{
  
  this->current_player = kPlayerOne;
  this->state = kPlaying;
  
  while(this->state == kPlaying)
  {
    //Print board
    this->board_ptr->print(std::cout);
    
    //Player input
    Coordinate coordinate = GetPlayerInput(this->current_player, this->board_ptr->GetSize());

    //Apply selection
    this->board_ptr->SetTile(coordinate.first,
			     coordinate.second,
			     player_symbol[this->current_player]);

    //check for win condition
    
    //switch player
    current_player = 
  }
  //Print board
}

Gameboard* TicTacToe::GetBoardPtr()
{
  return this->board_ptr;
}

void TicTacToe::SetBoardPtr(Gameboard* board_ptr)
{
  this->board_ptr = board_ptr;
}

TicTacToe::State TicTacToe::GetState()
{
  return this->state;
}

void TicTacToe::SetState(State state)
{
  this->state = state;
}
