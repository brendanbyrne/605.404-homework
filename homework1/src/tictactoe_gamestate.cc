#include "tictactoe_gamestate.h"

TicTacToeGameState::TicTacToeGameState() {
  
  for (int row = 0; row < kBoardSize; row++) {
    for (int col = 0; col < kBoardSize; col++) {
      board[row][col] = kEmpty;
    }
  }
  
}


void TicTacToeGameState::printboard( std::ostream& output_stream ) {  
  for (int row = 0; row < kBoardSize-1; row++){
    for (int col = 0; col < kBoardSize-1; col++){
      output_stream << " " << board[row][col] << " |";
    }
    
    output_stream << " " << board[row][kBoardSize-1] << std::endl;
    
    for (int i = 0; i < kBoardSize*4-1; i++){
      output_stream << "-";
    }
    output_stream << std::endl;
  }
  
  for (int col = 0; col < kBoardSize-1; col++){
    output_stream << " " << board[kBoardSize-1][col] << " |";
  }
  output_stream << " " << board[kBoardSize-1][kBoardSize-1] << std::endl;
}
