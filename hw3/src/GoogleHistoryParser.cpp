// GoogleHistoryParser.cpp

#include <vector>
#include <fstream>

#include <boost/algorithm/string.hpp> // split, is_any_of

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
                                           // location of file with data
  GoogleHistoryParser::GoogleHistoryParser(const std::string& filePath):
    filePath(filePath)
  {  
  }
  
  /*============================================================================
    lineToStats
        Attempts to parse a line from the file at the location described by the
        data member filePath. Takes in the line to be parsed and the container
        to store the data in assuming a successful parse.  Returns the success
        of the line parsing as a bool.

    Revision History
        18 June, 2015 - function created
  *///==========================================================================
                                        // the line to parse
  bool GoogleHistoryParser::lineToStats(const std::string& line,
                                        // container to capture output
                                        StockDayStats& dayStats)
  {
    const int EXPECTED_TOKEN_SIZE = 6;
    
    // which tokens coorespond to which pieces of data
    const int DATE_INDEX   = 0;
    const int OPEN_INDEX   = 1;
    const int HIGH_INDEX   = 2;
    const int LOW_INDEX    = 3;
    const int CLOSE_INDEX  = 4;
    const int VOLUME_INDEX = 5;
    
    bool wasSuccessful = true;

    // split a line around commas
    std::string delimiters = ",";
    std::vector<std::string> tokens;
    boost::split(tokens, line, boost::is_any_of(delimiters));

    // check the token's properties for anomalies and continue
    // parsing as long as things look good
    if (tokens.size() == EXPECTED_TOKEN_SIZE)
    {
      greg::date date;
      if (toDate(tokens[DATE_INDEX], date))
      {
        // attempt to convert strings to numbers
        try
        {
          double openPrice  = stod(tokens[OPEN_INDEX]);
          double highPrice  = stod(tokens[HIGH_INDEX]);
          double lowPrice   = stod(tokens[LOW_INDEX]);
          double closePrice = stod(tokens[CLOSE_INDEX]);
          int volumeTraded  = stoi(tokens[VOLUME_INDEX]);

          // assign the values to the StockDayStats object
          dayStats.setDate(date)
                  .setOpen(openPrice)
                  .setHigh(highPrice)
                  .setLow(lowPrice)
                  .setClose(closePrice)
                  .setVolume(volumeTraded);
        }
        catch (...)
        {
          wasSuccessful = false;
        }
        
      }
      else
      {
        wasSuccessful = false;
      } // if toDate
    }
    else
    {
      wasSuccessful = false;
    }// if tokens.size() 
    
    return wasSuccessful;
  }
  
  /*============================================================================
    parse 
        Attempts to parse the file at the location described by the data member
        filePath.  The input is the container for the data and the output is
        true if the parsing completed succuessfully.

    Revision History
        18 June, 2015 - function created
  *///==========================================================================
                                  // container to capture output
  bool GoogleHistoryParser::parse(PriceHistory& priceHistory) const
  {
    // sanitize inputs
    priceHistory.clear();
    
    bool wasSuccessful = true;
    
    std::ifstream file(this->filePath);

    // if file successfully opened

    
    if (file)
    {
      // while there is data in the file to parse
      std::string line;
      getline(file, line); // skip over the header
      while (getline(file, line))
      {
        
        // if the line was parsed correctly
        StockDayStats dayStats;
        if (GoogleHistoryParser::lineToStats(line, dayStats))
        {
          priceHistory.push_back(dayStats);
        }
        else
        {
          wasSuccessful = false;
          break;
        }
      } // while
      file.close();
    }
    else
    {
      wasSuccessful = false;
    } // if (file)
    
    return wasSuccessful;
  }
  
                                   // extract date from here
  bool GoogleHistoryParser::toDate(const std::string& string,
                                   greg::date& date) // store parsed data here
  {
    bool wasSuccessful = true;
    
    // expected locations of date information
    const int DAY_INDEX   = 0;
    const int MONTH_INDEX = 1;
    const int YEAR_INDEX  = 2;
    
    std::vector<std::string> tokens;
    std::string delimiters = "-";
    boost::split(tokens, string, boost::is_any_of(delimiters));

    const int EXPECTED_TOKEN_SIZE = 3;
    if (tokens.size() == EXPECTED_TOKEN_SIZE)
    {
      // Y3K bug!!! tsk tsk google
      std::string dateStr = "20"  + tokens[YEAR_INDEX]
                            + "-" + tokens[MONTH_INDEX]
                            + "-" + tokens[DAY_INDEX];
      try
      {
        date = greg::date(greg::from_string(dateStr));
      }
      catch (...)
      {
        wasSuccessful = false;
      }
    }
    else
    {
      wasSuccessful = false;
    }
    
    return wasSuccessful;
  }
  
} // namespace hw3
