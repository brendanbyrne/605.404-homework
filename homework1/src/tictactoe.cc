#include <iostream>
#include <utility>

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

std::pair<int,int> GetPlayerInput(TicTacToe::Player current_player)
{
  
  // do while input is invalid
  // player enter string
  // attmpet to parse string
  // check if string is valid
  // return coordinate as pair
  
  std::cout << "Player " << current_player << std::endl;
  do {
    //std::"Input coordinates row"
  } while (false);
  std::pair<int,int> coordinates {1,1}; // for testing only
  return coordinates;
}

void TicTacToe::StartGame()
{
  
  Player current_player = kPlayerOne;
  this->state = kPlaying;
  
  while(this->state == kPlaying)
  {
    //Print board
    //Player input
    std::pair<int,int> coordinate = GetPlayerInput(current_player);
    //Apply selection
    //check for win condition
    //switch player
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
