/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 17 June, 2015
  
  Revision History
      17 June, 2015 - class created
  
  Class Name: GoogleHistoryParser.hpp
  
  Intent: Parse daily pricing history from google finances
  
  Description: Google finance's pricing history is released in a particular
               csv format.  This class parses that data and creates a pricing
               history that can be used to preform further analysis
*///============================================================================

#ifndef GOOGLEHISTORYPARSER_HPP
#define GOOGLEHISTORYPARSER_HPP

#include <fstream>
#include <string>

#include <boost/date_time/gregorian/gregorian_types.hpp> // date

#include "StockDayStats.hpp"

namespace hw3
{  
  class GoogleHistoryParser
  {
    
  public:
    GoogleHistoryParser(); // default constructor
    GoogleHistoryParser(const std::string& filePath); // constructor with filename
    std::string getFilePath() const; // return the input file path
    void setFilePath(const std::string& filePath); // set the input file path
    PriceHistory parse(); // parse the data in current file path
    
  private:
    std::string filePath; // path to the input file
    
  }; // GoogleHistoryParser

  /*============================================================================
    getFilePath
        Returns path to the input file

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
  inline std::string GoogleHistoryParser::getFilePath() const
  {
    return this->filePath;
  }
  
  /*============================================================================
    setFilePath
        Change the path of the input file

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
  inline void GoogleHistoryParser::setFilePath(const std::string& filePath)
                                               // path to the new input file
  {
    this->filePath = filePath;
  }
  
} // namespace hw3

#endif // GOOGLEHISTORYPARSER_HPP
