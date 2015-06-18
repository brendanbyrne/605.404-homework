// GoogleHistoryParser.cpp

#include "GoogleHistoryParser.hpp"

namespace hw3
{

  /*============================================================================
    GoogleHistoryParser
        Default constructor

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
  GoogleHistoryParser::GoogleHistoryParser():
    filePath("")
  {
  }

  /*============================================================================
    GoogleHistoryParser
        Constructor for a given input file path

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
  GoogleHistoryParser::GoogleHistoryParser(const std::string& filePath):
    filePath(filePath)
  {  
  }

  /*============================================================================
   parse 
        attempt to parse the input file

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
  PriceHistory GoogleHistoryParser::parse()
  {
    
  }



} // namespace hw3
