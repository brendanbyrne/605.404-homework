#include <string>
#include <algorithm>
#include <sstream>

#include <boost/algorithm/string/join.hpp>

#include "gameboard.h"

Gameboard::Gameboard(int boardsize)
{
  this->board.resize(boardsize);
  
  for (auto &row : this->board)
  {
    row.resize(this->board.size());
    for (auto &square : row)
    {
      square.SetState(Gridspace::State::kCross);//Empty); <== this is for testing only
    }
  }
}

int Gameboard::GetSize()
{
  return this->board.size();
}

// Should this return a pointer?
std::vector<std::vector<Gridspace>> Gameboard::GetBoard()
{
  return this->board;
}

std::string GridspaceToString(Gridspace gs)
{
  std::stringstream ss;
  gs.print(ss);
  return ss.str();
}

std::string ExtractRowString(std::vector<Gridspace> row)
{
  std::vector<std::string> grid_str (row.size());
  std::transform(row.begin(), row.end(), grid_str.begin(), GridspaceToString);
  return boost::algorithm::join(grid_str, "|");
}

void Gameboard::print(std::ostream& output_stream)
{
  std::vector<std::string> rows_str (this->board.size());
  std::transform(this->board.begin(), this->board.end(), rows_str.begin(), ExtractRowString);
  std::string delimiter = "\n" + std::string(this->board.size()*4-1, '=') + "\n";
  
  output_stream << boost::algorithm::join(rows_str, delimiter);
}
