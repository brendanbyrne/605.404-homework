#include <string>
#include <algorithm>
#include <sstream>

#include <boost/algorithm/string/join.hpp>

#include "gameboard.hpp"

Gameboard::Gameboard(int board_size)
{
  Tile tile;
  tile.SetState(Tile::State::kEmpty);
  std::vector<Tile> row(board_size, tile);
  
  this->board.assign(board_size, row);
}

int Gameboard::GetSize()
{
  return this->board.size();
}

// Should this return a pointer?
std::vector<std::vector<Tile>>* Gameboard::GetBoard()
{
  return &this->board;
}

void Gameboard::SetTile(int row, int col, Tile::State new_state)
{
  this->board[row][col].SetState(new_state);
}

std::string TileToString(Tile tile)
{
  std::stringstream ss;
  tile.print(ss);
  return ss.str();
}

std::string ExtractRowString(std::vector<Tile> row)
{
  std::vector<std::string> tiles_str (row.size());
  std::transform(row.begin(), row.end(), tiles_str.begin(), TileToString);
  return boost::algorithm::join(tiles_str, "|");
}

void Gameboard::print(std::ostream& output_stream)
{
  int pretty_print_multiplier = 4; //found experimentally
  
  std::vector<std::string> rows_str (this->board.size());
  std::transform(this->board.begin(), this->board.end(), rows_str.begin(), ExtractRowString);
  std::string delimiter = "\n" + std::string(this->board.size()*pretty_print_multiplier-1, '-') + "\n";
  
  output_stream << boost::algorithm::join(rows_str, delimiter);
}

std::vector<std::pair<int,int>> Gameboard::GetOpenTiles()
{
  std::vector<std::pair<int,int>> open_tiles;
  open_tiles.reserve( this->board.size() * this->board.size() );
  
  int row_num = 0;
  for (auto &row : this->board)
  {
    int col_num = 0;
    for (auto &tile : row)
    {
      if (tile.GetState() == Tile::State::kEmpty)
      {
	std::pair<int,int> coordinate = {row_num, col_num};
	open_tiles.push_back(coordinate);
      }
      ++col_num;
    }
    ++row_num;
  }
  return open_tiles;
}
