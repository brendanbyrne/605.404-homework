#ifndef TICTACTOE_HPP_
#define TICTACTOE_HPP_

#include <ostream>

#include "gameboard.hpp"

class TicTacToe
{
public:
  enum State {kInitialized, kPlaying, kP1Wins, kP2Wins, kTie};
  enum Player {kPlayerOne=1, kPlayerTwo};
  
  TicTacToe(int);
  ~TicTacToe();
  void StartGame();
  
  Gameboard* GetBoardPtr();
  void SetBoardPtr(Gameboard*);
  State GetState();
  void SetState(State); 

private:
  Gameboard* board_ptr;
  State state;
};

#endif //TICTACTOE_HPP_
