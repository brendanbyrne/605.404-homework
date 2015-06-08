#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <stdexcept>

#include <boost/algorithm/string.hpp>

#include "tictactoe.hpp"

TicTacToe::TicTacToe(int size):
  gameboard(size)
{

}

void TicTacToe::StartGame()
{  

  this->gameboard.printTo(std::cout);
  this->current_player = PLAYER_ONE;

  //Print board
  Player winner;
  std::pair<int, int> coordinate;  
  do
  {   
    //Player input
    coordinate = getPlayerInput();

    //Apply selection
    this->gameboard.setTileState(coordinate.first,
				 coordinate.second,
				 player_to_state[this->current_player]);
    
    this->gameboard.printTo(std::cout);

    //switch player
    this->current_player = this->current_player == PLAYER_ONE ? PLAYER_TWO : PLAYER_ONE;    
    
  }
  while ( isGameOver(winner, coordinate) != true );
  
  if (winner == NOONE)
  {
    std::cout << "Tie Game" << std::endl;
  }
  else 
  {
    std::cout << "Player " << winner << " has won!" << std::endl;
  }    
  
}

bool TicTacToe::isValidInt(const std::string& str, int& candidate)
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

bool TicTacToe::isInBounds(const int candidate)
{
  if (1 <= candidate && candidate <= this->gameboard.getSize())
  {
    return true;
  }
  else
  {
    return false;
  }
}

std::pair<int, int> TicTacToe::getPlayerInput()
{
  
  std::pair<int, int> coordinate;
  std::cout << "\nPlayer " << this->current_player << std::endl;

  std::string user_input;
  
  // do while input is invalid
  do
  {
    // Prompt user
    std::cout << "Input desired row and column location ex. \"1 1\": ";
    getline(std::cin, user_input);
  
  } while(isValidUserInput(user_input, coordinate) != true);

  return coordinate;
}

bool TicTacToe::isValidUserInput(const std::string& user_input, std::pair<int, int>& coordinate)
{
  const std::string delimiters = " ";

  std::vector<std::string> tokens;
  boost::split(tokens, user_input, boost::is_any_of(delimiters));

  if (tokens.size() != this->DIMENSIONS)
  {
    std::cout << "Incorrect number of inputs" << std::endl;
    return false;
  }

  std::vector<int> valid_inputs;
  for (auto& str : tokens)
  {
    int candidate;
    if (isValidInt(str, candidate))
    {
      if (isInBounds(candidate))
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
  
  
  coordinate = std::pair<int,int>(valid_inputs[0]-1, valid_inputs[1]-1); //minus 1 because collection starts at 0 not 1
  
  if (this->gameboard.getTileState(coordinate.first, coordinate.second) != Tile::State::EMPTY)
  {
    std::cout << "Space already taken" << std::endl;
    return false;
  }

  return true;
}

bool sequenceHasWin(const std::vector<Tile::State>& sequence)
{
  Tile::State target = sequence[0];
  for (auto& state : sequence)
  {
    if (state == Tile::State::EMPTY)
    {
      return false;
    }
    else if (state == target)
    {
      continue;
    }
    else
    {
      return false;
    }
  }
  return true;
}

bool TicTacToe::isGameOver(Player& winner, std::pair<int, int> coordinate)
{
  const int size = this->gameboard.getSize();
  std::vector<Tile::State> sequence;
  sequence.reserve(size);
  
  // check column
  int row = coordinate.first;
  for (int col = 0; col < size; col++)
  {
    sequence.push_back(gameboard.getTileState(row, col));
  }
  
  if (sequenceHasWin(sequence))
  {
    winner = state_to_player[this->gameboard.getTileState(coordinate.first, coordinate.second)];
    return true;
  }

  sequence.clear();
  sequence.reserve(size);

  // check row
  int col = coordinate.second;
  for (int row = 0; row < size; row++)
  {
    sequence.push_back(gameboard.getTileState(row, col));
  }
  
  if (sequenceHasWin(sequence))
  {
    winner = state_to_player[this->gameboard.getTileState(coordinate.first, coordinate.second)];
    return true;
  }
  
  sequence.clear();
  sequence.reserve(size);

  // top left to bottom right diagonal
  if (coordinate.first == coordinate.second)
  {
    for (int i = 0; i < size; i++)
    {
      sequence.push_back(gameboard.getTileState(i, i));
    }
    
    if (sequenceHasWin(sequence))
    {
      winner = state_to_player[this->gameboard.getTileState(coordinate.first, coordinate.second)];
      return true;
    }

  }
  
  sequence.clear();
  sequence.reserve(size);
  
  // bottom left to top right diagonal
  int offset = 1;
  if ( (coordinate.first + coordinate.second + 2) == 2*(size - offset))
  {
    for (int i = 0; i < size; i++)
    {
      sequence.push_back(gameboard.getTileState(size - i - 1, i));
    }

    if (sequenceHasWin(sequence))
    {
      winner = state_to_player[this->gameboard.getTileState(coordinate.first, coordinate.second)];
      return true;
    }

  }
  
  // tie
  int empty_tiles = 0;
  for (int row = 0; row < size; row++)
  {
    for (int col = 0; col < size; col++)
    {
      if (this->gameboard.getTileState(row,col) == Tile::State::EMPTY)
      {
	empty_tiles++;
      }
    }
  }
  
  if (empty_tiles == 0)
  {
    winner = NOONE;
    return true;
  }

  return false;
}

bool TicTacToe::isGameOver(Player& winner)
{
  
  const int size = this->gameboard.getSize();
  std::vector<Tile::State> sequence;
  sequence.reserve(size);
  
  // check rows
  for (int row = 0; row < size; row++)
  {
    for (int col = 0; col < size; col++)
    {
      sequence.push_back(gameboard.getTileState(row, col));
    }
  
    if (sequenceHasWin(sequence))
    {
      return true;
    }
    
    sequence.clear();
    sequence.reserve(size);
    
  }
   
  // check columns
  for (int col = 0; col < size; col++)
  {
    for (int row = 0; row < size; row++)
    {
      sequence.push_back(gameboard.getTileState(row, col));
    }
  
    if (sequenceHasWin(sequence))
    {
      return true;
    }

    sequence.clear();
    sequence.reserve(size);
    
  }
  
  // check diagonals
  for (int i = 0; i < size; i++)
  {
    sequence.push_back(gameboard.getTileState(i, i));
  }
  
  
  if (sequenceHasWin(sequence))
  {
    return true;
  }

  sequence.clear();
  sequence.reserve(size);
  
  for (int i = 0; i < size; i++)
  {
    sequence.push_back(gameboard.getTileState(size - i - 1, i));
  }
  

  if (sequenceHasWin(sequence))
  {
    return true;
  }

  return false;
}
