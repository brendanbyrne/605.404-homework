//********************************************************************
// TicTacToe.cc
// Author: Brendan Byrne
// Date: June 8, 2015
// Class: 605.404 Programming in C++
// Purpose: This program creates a game of TicTacToe
// Input: (from standard input) row and column
// Output: (to standard out) the state of the game
//********************************************************************

#include "GameState.hpp"
#include "Tile.hpp"

int main()
{
  static int board_size = 3; // N where NxN is the size of the gameboard
  static bool isNotAI = false;
  static bool isAI = true;

  // initialize game
  hw1::GameState game(board_size);

  // build players
  // number of players is limited by the number of unique Tile states minus 1
  hw1::Opponent me("Human", hw1::Tile::State::CROSS, isNotAI, game.getGameboardPtr());
  hw1::Opponent ai("The Computer", hw1::Tile::State::CIRCLE, isAI, game.getGameboardPtr());

  // Add players to game
  game.addPlayer(me);
  game.addPlayer(ai);

  // Start the game
  game.startGame();  
  
  return 0;
}
