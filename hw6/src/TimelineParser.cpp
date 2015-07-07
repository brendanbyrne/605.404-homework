// TimelineParser.cpp

#include <fstream>
#include <algorithm> // any_of

#include <boost/algorithm/string.hpp> // split, is_any_of

#include "TimelineParser.hpp"

namespace hw6
{
  /*============================================================================
    parseLine
        given a line from a csv file, parse it into a Passenger object

    Revision History
        7 July 2015 - Function created
  *///==========================================================================
  Passenger TimelineParser::parseLine(std::string line) // csv line from file
  {
    // delete carrige return
    if (std::any_of(line.begin(), line.end(),
                    [](char str) -> bool
                    {
                      return str == '\r';
                    }))
    {
      line.pop_back();
    }
    
    std::vector<std::string> tokens;
    boost::split(tokens, line, boost::is_any_of(","));
    
    int time = std::atoi(tokens[TimelineParser::TIME_INDEX].c_str());
    int start = std::atoi(tokens[TimelineParser::START_INDEX].c_str());
    int goal = std::atoi(tokens[TimelineParser::GOAL_INDEX].c_str());
    
    Passenger passenger(time, start, goal);    
 
    return passenger;
  }
  
  /*============================================================================
    parse
        given an input file, parse out the passenger timeline

    Revision History
        7 July 2015 - Function created
  *///==========================================================================
  Timeline TimelineParser::parse(std::string filePath)
  {
    Timeline output;
    
    // reset the error flags
    this->fileFlag = false;
    
    std::ifstream file(filePath);
    
    if (file)
    {
      std::string line;
      
      getline(file, line); // skip header
      
      while (getline(file, line))
      {
        output.push_back(parseLine(line));
      }
      
    }
    else
    {
      this->fileFlag = true;
    }
    
    return output;
    
  }
} // namespace hw6
