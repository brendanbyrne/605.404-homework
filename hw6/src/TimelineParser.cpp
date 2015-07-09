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
  bool TimelineParser::parseLine(std::string& line, // csv line
                                 Passenger& passenger)
  {
    bool successful = true;
    
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
    

    int time;
    int start;
    int goal;
    
    // try to parse the line
    try
    {
      time = std::stoi(tokens[TimelineParser::TIME_INDEX]);
      start = std::stoi(tokens[TimelineParser::START_INDEX]);
      goal = std::stoi(tokens[TimelineParser::GOAL_INDEX]);
      
      // minus 1 to convert to 0 indexed system.
      passenger.setStartTime(time)
               .setStartFloor(start - 1)
               .setEndFloor(goal - 1);
    }
    //abort if any error occurs
    catch (...)
    {
      successful = false;
    }
 
    return successful;
  }
  
  /*============================================================================
    parse
        given an input file, parse out the passenger timeline

    Revision History
        7 July 2015 - Function created
  *///==========================================================================
  Line TimelineParser::parse(std::string filePath)
  {
    Line output;
    
    // reset the error flags
    this->fileFlag = false;
    this->lineFlag = false;
    
    std::ifstream file(filePath);
    
    if (file)
    {
      std::string line;
      
      getline(file, line); // skip header
      
      Passenger passenger;
      bool lineSuccessful;
      
      while (getline(file, line))
      {
        lineSuccessful = parseLine(line, passenger);
        if (lineSuccessful)
        {
          output.push(passenger);
        }
        else
        {
          // flag not already set
          if (!this->lineFlag)
          {
            // raise the flag
            this->lineFlag= true;
          }
        } // lineSuccessful
      }// while
      
    }
    else
    {
      this->fileFlag = true;
    }
    
    return output;
    
  }
} // namespace hw6
