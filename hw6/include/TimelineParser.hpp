/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 7 July, 2015
  
  Revision History
      7 July, 2015 - class created
  
  Class Name: TimelineParser
  
  Intent: Parser to extract the passenger arrival timeline
  
  Description: 

*///============================================================================

#ifndef TIMELINEPARSER_HPP
#define TIMELINEPARSER_HPP

#include <string>
#include <vector>

#include "Passenger.hpp"

namespace hw6
{
  class TimelineParser
  {
  public:
    Line parse(std::string filepath); // parse file at path
    
    bool getFileFlag(); // returns value of fileFlag
    
  private:
    bool fileFlag; // error flag
    
    static const int TIME_INDEX = 0;
    static const int START_INDEX = 1;
    static const int GOAL_INDEX = 2;
   
    Passenger parseLine(std::string line); // parse csv line to passenger object
    
  }; // class TimelineParser
  
  /*============================================================================
    getFileFlag
        get the value of the fileFlag data member, true means flag was thrown

    Revision History
        7 July 2015 - Function created
  *///==========================================================================
  inline bool TimelineParser::getFileFlag()
  {
    return this->fileFlag;
  }
  
} // namespace hw6

#endif // TIMELINEPARSER_HPP
