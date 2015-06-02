#ifndef TICTACTOE_GAMESTATE_H_
#define TICTACTOE_GAMESTATE_H_

#include <ostream>
#include <map>

class TicTacToeGameState {
 private:
  enum GameState {kTie, kPOneWins, kPTwoWins};
  enum GridState {kEmpty, kCross, kCircle};
  
  const static std::map<GridState, const char> gs2c;
  gs2c[kEmpty]=' ';// = {{kEmpty,' '},{kCross,'X'},{kCircle,'O'}};
  const static int kBoardSize = 3;
  int board[kBoardSize][kBoardSize];  
  
 public:
  TicTacToeGameState();
  void printboard( std::ostream& output_stream );
};
#endif // TICTACTOE_BOARD_H_
