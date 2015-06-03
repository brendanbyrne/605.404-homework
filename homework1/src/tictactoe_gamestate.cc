#include "tictactoe_gamestate.h"

TicTacToeGameState::TicTacToeGameState() {
  
  for (int row = 0; row < kBoardSize; row++) {
    for (int col = 0; col < kBoardSize; col++) {
      board[row][col] = kEmpty;
    }
  }
  
}


void TicTacToeGameState::PrintBoard( std::ostream& output_stream ) {  
  for (int row = 0; row < kBoardSize-1; row++){
    for (int col = 0; col < kBoardSize-1; col++){
      output_stream << GridToStr(row, col) << "|";
    }
    
    output_stream << GridToStr(row, kBoardSize-1) << std::endl;
    
    for (int i = 0; i < kBoardSize*4-1; i++){
      output_stream << "-";
    }
    output_stream << std::endl;
  }
  
  for (int col = 0; col < kBoardSize-1; col++){
    output_stream << GridToStr(kBoardSize-1, col) << "|";
  }
  output_stream << GridToStr(kBoardSize-1, kBoardSize-1) << std::endl;
}

std::string TicTacToeGameState::GridToStr(int row, int col) {
  return " " + std::to_string(gs2cm[board[row][col]]) + " ";
}
