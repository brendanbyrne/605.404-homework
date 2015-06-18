/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 17 June, 2015
  
  Revision History
      17 June, 2015 - class created
  
  Class Name: GoogleHistoryParser.hpp
  
  Intent: Parse a daily pricing history csv from google finances
  
  Description: Google finance's pricing history is released in a particular
               csv format.  This class parses that data and creates a pricing
               history that can be used to preform further analysis.  The class
               has a series of flags that when set to high indicate an error
               occured with a particular operation.
*///============================================================================

#ifndef GOOGLEHISTORYPARSER_HPP
#define GOOGLEHISTORYPARSER_HPP

#include <string>

#include <boost/date_time/gregorian/gregorian_types.hpp> // date
namespace greg = boost::gregorian;

#include "StockDayStats.hpp"

namespace hw3
{    
  class GoogleHistoryParser
  {    
  public:    
    GoogleHistoryParser(); // default constructor

    bool getDateErrorFlag() const; // date flag getter
    bool getFileErrorFlag() const; // file flag getter
    bool getLineErrorFlag() const; // line flag getter
    bool wasSuccessful() const; // checks if ANY flags were set
    
    // parse the file at "filePath"
    PriceHistory parse(const std::string& filePath);
    
  private:    
    // attempt to parse a line into a StockDayStats object
    StockDayStats lineToStats(const std::string& line);
    
    // attempt to parse a string into a boost::gregorian::date object
    greg::date toDate(const std::string& string);

    bool fileErrorFlag;
    bool lineErrorFlag;
    bool dateErrorFlag;
    
  }; // GoogleHistoryParser

  /*============================================================================
    getDateErrorFlag
        returns the state of the dateErrorFlag

    Revision History
        18 June, 2015 - function created
  *///==========================================================================
  inline bool GoogleHistoryParser::getDateErrorFlag() const
  {
    return this->dateErrorFlag;
  }

  /*============================================================================
    getFileErrorFlag
        returns the state of the fileErrorFlag

    Revision History
        18 June, 2015 - function created
  *///==========================================================================
  inline bool GoogleHistoryParser::getFileErrorFlag() const
  {
    return this->fileErrorFlag;
  }

  /*============================================================================
    getLineErrorFlag
        returns the state of the lineErrorFlag

    Revision History
        18 June, 2015 - function created
  *///==========================================================================
  inline bool GoogleHistoryParser::getLineErrorFlag() const
  {
    return this->lineErrorFlag;
  }

  /*============================================================================
    wasSuccessful
        If all flags are false, then this returns true indicating a successful
        attempt at parsing.

    Revision History
        18 June, 2015 - function created
  *///==========================================================================
  inline bool GoogleHistoryParser::wasSuccessful() const
  {
    //return !this->fileErrorFlag && !this->lineErrorFlag && !this->dateErrorFlag;
    return true;
  }
} // namespace hw3

#endif // GOOGLEHISTORYPARSER_HPP
