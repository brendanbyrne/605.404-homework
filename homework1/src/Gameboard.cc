// Gameboard.cc
//
#include <sstream>

#include <boost/algorithm/string/join.hpp>

#include "Gameboard.hpp"

namespace hw1
{
  
Gameboard::Gameboard(const int board_size)
{
  Tile tile(Tile::State::EMPTY);
  std::vector<Tile> row(board_size, tile);
  
  this->board.assign(board_size, row);
}

//******************************************************************
// void setTileState()
// Purpose: set a specified tile to a specified state
// Input: row and column location of the tile, the desired state
//******************************************************************
void Gameboard::setTileState(const int row, // first index in grid
			     const int col, // second index in grid
			     const Tile::State new_state) // the state to apply to the location
{
  this->board[row][col].setState(new_state);
}

//******************************************************************
// void startGame()
// Purpose: Manage the human or AI interactions with the TicTacToe
//          game
// Input: None, but there must be at least one player added to start
//        the game
// Output: None
// Postcondition: A game of TicTacToe has been played
//******************************************************************
Tile::State Gameboard::getTileState(const int row, // row location in grid
				    const int col) const // column location in grid
{
  return this->board[row][col].getState();
}

std::string buildRowString(const std::vector<Tile> row)
{
  std::vector<std::string> tiles_str (row.size());
  std::transform(row.begin(), row.end(), tiles_str.begin(), [](Tile t){return t.str();} );
  return boost::algorithm::join(tiles_str, "|");
}

void Gameboard::printTo(std::ostream& output_stream) const
{  
  std::vector<std::string> rows_str (this->board.size());
  std::transform(this->board.begin(), this->board.end(), rows_str.begin(), buildRowString);
  std::string row_delimiter = "\n" + std::string(this->board.size() * this->PRETTY_PRINT_FACTOR - 1, '-') + "\n";
  
  output_stream << boost::algorithm::join(rows_str, row_delimiter) << "\n";
}

std::vector<std::pair<int, int>> Gameboard::getOpenTiles() const
{
  std::vector<std::pair<int, int>> open_tiles;
  open_tiles.reserve( this->board.size() * this->board.size() );

  int row_num = 0;
  for (auto& row : this->board)
  {
    int col_num = 0;
    for (auto& tile : row)
    {
      if (tile.getState() == Tile::State::EMPTY)
      {
	std::pair<int, int> coordinate = {row_num, col_num};
	open_tiles.push_back(coordinate);
      }
      ++col_num;
    }
    ++row_num;
  }
  return open_tiles;
}

int Gameboard::getSize() const
{
  return this->board.size();
}

} // namespace hw1
