#include <string>
#include <algorithm>
#include <sstream>

#include <boost/algorithm/string/join.hpp>

#include "gameboard.h"

Gameboard::Gameboard(int size):
  size(size) 
{
  this->board.resize(size);
  
  for (auto &row : this->board)
  {
    row.resize(size);
    for (auto &square : row)
    {
      square.SetState(Gridspace::State::kEmpty);
    }
  }
}

int Gameboard::GetSize()
{
  return this->size;
}

// Should this return a pointer?
std::vector<std::vector<Gridspace>> Gameboard::GetBoard()
{
  return this->board;
}

std::string gs2s (Gridspace gs)
{
  std::stringstream ss;
  gs.str(ss); 
  return ss.str();
}

void Gameboard::str(std::ostream& output_stream)
{
  std::vector<std::string> rows_str (this->size);
  
  for (auto &row : this->board)
  {
    std::vector<std::string> grid_str (this->size);
    std::transform(row.begin(), row.end(), grid_str.begin(), gs2s);
  }
}
