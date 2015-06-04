#include <string>
#include <algorithm>
#include <sstream>

#include <boost/algorithm/string/join.hpp>

#include "gameboard.hpp"

Gameboard::Gameboard(int boardsize)
{
  this->board.resize(boardsize);
  
  for (auto &row : this->board)
  {
    row.resize(this->board.size());
    for (auto &square : row)
    {
      square.SetState(Tile::State::kEmpty);
    }
  }
}

int Gameboard::GetSize()
{
  return this->board.size();
}

// Should this return a pointer?
std::vector<std::vector<Tile>> Gameboard::GetBoard()
{
  return this->board;
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
  //int row = 0;
  //std::for_each(this->board.begin(), this->board.end(), LoopTilesInRow(
}
