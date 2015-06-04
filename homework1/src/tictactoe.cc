#include "tictactoe.hpp"

TicTacToe::TicTacToe(std::ostream output_stream, int boardsize):
  output_stream(output_stream)
{
  this->board_ptr = new Gameboard(boardsize);
  this->state = kContinue;
}

TicTacToe::~TicTacToe()
{
  delete this->board_ptr;
}

void TicTacToe::StartGame()
{
  while(this->state == kContinue)
  {
    this->state = kP1Wins;
  }
}

TicTacToe::State TicTacToe::GetState()
{
  return this->state;
}

void TicTacToe::SetState(State state)
{
  this->state = state;
}
