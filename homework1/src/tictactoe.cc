#include <iostream>
#include <utility>
#include <string>
#include <algorithm>

#include "tictactoe.hpp"

TicTacToe::TicTacToe(const int size):
  gameboard(size)
{
  
}

void TicTacToe::startGame()
{  
  
  if (opponents.size() < 1)
  {
    std::cout << "Add more players" << std::endl;
    return;
  }
  
  //this->gameboard.printTo(std::cout);
  this->current_player = PLAYER_ONE;
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

Gameboard* TicTacToe::getGameboardPtr()
{
  return &this->gameboard;
}

void TicTacToe::addPlayer(Opponent& player)
{
  this->opponents.push_back(player);
}

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
  
bool TicTacToe::isGameOver(std::vector<Opponent>::iterator& winner_ptr,
			   std::pair<int, int> coordinate)
{
  const int size = this->gameboard.getSize();
  const Tile::State symbol = this->gameboard.getTileState(coordinate.first, coordinate.second);
  winner_ptr = std::find_if(this->opponents.begin(), this->opponents.end(),
			    [symbol](Opponent& op) -> bool
			    {
			      return op.getSymbol() == symbol;
			    });
  
  std::vector<Tile::State> sequence;
  sequence.reserve(size);
  
  // check column
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

  // check row
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

  // top left to bottom right diagonal
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
  
  // bottom left to top right diagonal
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
  
  // tie
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
  
  if (empty_tiles == 0)
  {
    winner_ptr = this->opponents.end();
    return true;
  }

  return false;
}
