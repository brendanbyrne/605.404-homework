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
    GoogleHistoryParser(std::string filePath); // constructor with filename
    std::string getFilePath() const;
    void setFilePath(std::string filePath);
    PriceHistory parseFile();
    
  private:
    std::string filePath;
    
  }; // GoogleHistoryParser
} // namespace hw3

#endif // GOOGLEHISTORYPARSER_HPP
