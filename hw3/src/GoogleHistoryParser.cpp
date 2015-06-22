// GoogleHistoryParser.cpp

#include <vector>
#include <fstream>
#include <algorithm> // reverse

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
    fileErrorFlag(true), lineErrorFlag(true), dateErrorFlag(true)
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
  StockDayStats GoogleHistoryParser::lineToStats(const std::string& line) 
  {    
    StockDayStats dayStats;
    
    // which tokens coorespond to which pieces of data
    const int DATE_INDEX   = 0;
    const int OPEN_INDEX   = 1;
    const int HIGH_INDEX   = 2;
    const int LOW_INDEX    = 3;
    const int CLOSE_INDEX  = 4;
    const int VOLUME_INDEX = 5;

    // split line around commas
    const int EXPECTED_TOKEN_SIZE = 6;
    std::string delimiters = ",";
    std::vector<std::string> tokens;
    boost::split(tokens, line, boost::is_any_of(delimiters));
    
    // check the token's properties for anomalies and continue
    // parsing as long as things look good
    if (tokens.size() == EXPECTED_TOKEN_SIZE)
    {
      greg::date date = toDate(tokens[DATE_INDEX]);
      if (!this->dateErrorFlag)
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
          this->lineErrorFlag = true;
        } // try
      } // if dateErrorFlag
    }
    else
    {
      this->lineErrorFlag = true;
    }// if tokens.size() 
    
    return dayStats;
  }
  
  /*============================================================================
    parse 
        Attempts to parse the file at the location described filePath.  The 
        priceHistory is the container for the data. The output is true if the
        parsing completed succuessfully.

    Revision History
        18 June, 2015 - function created
  *///==========================================================================
                                          // path to the input
  PriceHistory GoogleHistoryParser::parse(const std::string& filePath)
  {
    // reset the error flags
    this->fileErrorFlag = false; 
    this->lineErrorFlag = false;
    this->dateErrorFlag = false;
    
    PriceHistory priceHistory;    
    
    std::ifstream file(filePath);
    
    // if file successfully opened    
    if (file)
    {
      std::string line;
      getline(file, line); // skip over the header
      // while there is data in the file to parse
      while (getline(file, line))
      {       
        StockDayStats dayStats = this->lineToStats(line);
        // if the line was parsed correctly
        if (!this->lineErrorFlag && !this->dateErrorFlag)
        {
          priceHistory.push_back(dayStats);
        }
        else
        {
          break;
        }
      } // while
      file.close();
    }
    else
    {
      // raise flag for an error with file operations
      this->fileErrorFlag = true;
    } // if (file)

    priceHistory.shrink_to_fit();
    std::reverse(priceHistory.begin(), priceHistory.end());
    
    return priceHistory;
  }

  /*============================================================================
    toDate
        Attempts to a date from a string and use that string to create a 
        boost::gregorian::date object

    Revision History
        18 June, 2015 - function created
  *///==========================================================================
                                         // extract date from here
  greg::date GoogleHistoryParser::toDate(const std::string& string)
  {    
    greg::date date;
    
    // expected locations of date information
    const int DAY_INDEX   = 0;
    const int MONTH_INDEX = 1;
    const int YEAR_INDEX  = 2;

    // grab the date components
    const int EXPECTED_TOKEN_SIZE = 3;
    std::vector<std::string> tokens;
    std::string delimiters = "-";
    boost::split(tokens, string, boost::is_any_of(delimiters));
    
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
        // raise error with date parsing
        this->dateErrorFlag = true;
      }
    }
    else
    {
      // raise error with date parsing
      this->dateErrorFlag = true;
    }
    
    return date;
  }
  
} // namespace hw3
