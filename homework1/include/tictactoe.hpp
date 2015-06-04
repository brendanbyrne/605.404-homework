#ifndef TICTACTOE_HPP_
#define TICTACTOE_HPP_

#include <ostream>

#include "gameboard.hpp"

class TicTacToe
{
public:
  enum State {kContinue, kP1Wins, kP2Wins, kTie};
  
  TicTacToe(std::ostream&, int);
  ~TicTacToe();
  void StartGame();
  
  State GetState();
  void SetState(State); 

private:
  std::ostream& output_stream;
  Gameboard* board_ptr;
  State state;
};

#endif //TICTACTOE_HPP_
