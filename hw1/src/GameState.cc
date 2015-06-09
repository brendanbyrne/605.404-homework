// GameState.cc
//
#include <iostream>
#include <utility>
#include <string>
#include <algorithm>

#include "GameState.hpp"

namespace hw1
{
  
GameState::GameState(const int size): // the size of the tictactoe grid
  gameboard(size)
{
  
}

//******************************************************************
// void startGame()
// Purpose: Manage the human or AI interactions with the TicTacToe
//          game
// Input: None, but there must be at least one player added to start
//        the game
// Output: None
//******************************************************************
void GameState::startGame()
{  
  
  if (opponents.size() < 1)
  {
    std::cout << "Add more players" << std::endl;
    return;
  }
  
  //this->gameboard.printTo(std::cout);
  this->player = opponents.begin();
    
  //Print board
  this->gameboard.printTo(std::cout);
  
  std::vector<Opponent>::iterator winner_ptr;
  std::pair<int, int> coordinate;  
  do
  { 
    //Player input
    std::cout << this->player->getName() << ", make your move" << std::endl;
    coordinate = this->player->makeMove();
    
    //Apply selection
    this->gameboard.setTileState(coordinate.first,
				 coordinate.second,
				 this->player->getSymbol());
    //Print board
    this->gameboard.printTo(std::cout);
    
    //switch player
    ++this->player;
    if (this->player == opponents.end())
    {
      this->player = opponents.begin();
    }
    
    // continue playing until game is over
  } while ( this->isGameOver(winner_ptr, coordinate) != true );

  if (winner_ptr == this->opponents.end())
  {
    std::cout << "Tie Game" << std::endl;
  }
  else 
  {
    std::cout << winner_ptr->getName() << " has won!" << std::endl;
  }    
}

//******************************************************************
// const Gameboard* getGameboardPtr()
// Purpose: Allow others to view the tictactoe grid
// Input: None
// Output: A constant point to the grid
//******************************************************************
const Gameboard* GameState::getGameboardPtr()
{
  return &this->gameboard;
}

//******************************************************************
// void addPlayer()
// Purpose: add participants to the game. The total number of
//          must not excede the number of states defined by
//          the Tile::State enum
// Input: An Opponent object
// Output: None
//******************************************************************
void GameState::addPlayer(Opponent& player)
{
  this->opponents.push_back(player);
}

//******************************************************************
// void sequenceHasWin()
// Purpose: Check a slice of the gameboard for a win condition
// Input: None, but there must be at least 1 player to start the game
// Output: true, if a win state is detected
//******************************************************************
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

//******************************************************************
// bool isGameOver()
// Purpose: Check the tictactoe board for a win state
// Input: iterator container to capture the potential winner
//        location of the last played move
// Output: true, if a win state is detecte
//******************************************************************
bool GameState::isGameOver(std::vector<Opponent>::iterator& winner_ptr,
			   std::pair<int, int> coordinate)
{
  const int size = this->gameboard.getSize();

  // the mark from the last move made
  const Tile::State symbol = this->gameboard.getTileState(coordinate.first, coordinate.second);
  
  // the last person to move
  winner_ptr = std::find_if(this->opponents.begin(), this->opponents.end(),
			    [symbol](Opponent& op) -> bool
			    {
			      return op.getSymbol() == symbol;
			    });
  
  std::vector<Tile::State> sequence;
  sequence.reserve(size);
  
  // check all effected columns for a win state
  for (int col = 0; col < size; col++)
  {
    sequence.push_back(gameboard.getTileState(coordinate.first, col));
  }
  if (sequenceHasWin(sequence))
  {
    return true;
  }
  sequence.clear();
  sequence.reserve(size);

  // check all effected rows for a win state
  for (int row = 0; row < size; row++)
  {
    sequence.push_back(gameboard.getTileState(row, coordinate.second));
  }
  if (sequenceHasWin(sequence))
  {
    return true;
  }
  sequence.clear();
  sequence.reserve(size);

  // check top left to bottom right diagonal
  // for a win state
  if (coordinate.first == coordinate.second)
  {
    for (int i = 0; i < size; i++)
    {
      sequence.push_back(gameboard.getTileState(i, i));
    } 
    if (sequenceHasWin(sequence))
    {
      return true;
    }
  }
  sequence.clear();
  sequence.reserve(size);
  
  // check bottom left to top right diagonal
  // for a win state
  int offset = 2;
  if ( (coordinate.first + coordinate.second + offset) == 2*(size - 1))
  {
    for (int i = 0; i < size; i++)
    {
      sequence.push_back(gameboard.getTileState(size - i - 1, i));
    }
    if (sequenceHasWin(sequence))
    {
      return true;
    }
  }
  
  // test for a tie game
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

  // if tie set winner to sential value
  if (empty_tiles == 0)
  {
    winner_ptr = this->opponents.end();
    return true;
  }

  // if all other checks fail then there has not been a win state
  return false;
}

} // namespace hw1
