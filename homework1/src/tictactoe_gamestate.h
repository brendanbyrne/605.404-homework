#ifndef TICTACTOE_GAMESTATE_H_
#define TICTACTOE_GAMESTATE_H_


#include <ostream>
#include <map>
#include <string>

class TicTacToeGameState {
 private:
  enum GameState {kTie, kPOneWins, kPTwoWins};
  enum GridState {kEmpty, kCross, kCircle};
  
  const std::map<GridState, const char> gs2cm = {{kEmpty,' '}, {kCross,'X'}, {kCircle,'O'}};
  
  const static int kBoardSize = 3;
  int board[kBoardSize][kBoardSize];  
  
  std::string GridToStr( int row, int col );

 public:
  TicTacToeGameState();
  void PrintBoard( std::ostream& output_stream );
};
#endif // TICTACTOE_GAMESTATE_H_
