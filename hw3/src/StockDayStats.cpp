// StockDayStats.cpp

#include "StockDayStats.hpp"

namespace hw3
{
  /*============================================================================
    StockDayStats
        Default constructor, everything is set to 0 except for date which
        defaults to "not_a_date_time"

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
  StockDayStats::StockDayStats():
    closePrice(0.0), highPrice(0.0), lowPrice(0.0),
    openPrice(0.0), volumeTraded(0)
  {
  }

  /*============================================================================
    StockDayStats
        Full constructor that take in values for all the data members

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
  StockDayStats::StockDayStats(const greg::date& date, // day of stock stats
                               const double openPrice, // opening stock price
                               const double highPrice, // highest stock price
                               const double lowPrice, // lowest stock price
                               const double closePrice, // closing stock price
                               const int volumeTraded): // volume traded that day
    closePrice(closePrice), date(date), highPrice(highPrice),
    lowPrice(lowPrice), volumeTraded(volumeTraded)
  {
  }
  
  /*============================================================================
    operator<<
        Returns the closing value of the stock

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
    std::ostream& operator<<(std::ostream& out, // desired output stream
                             const StockDayStats& sds) //StockDayStats object
  {
    out << sds.getDate() << ", " << sds.getOpen() << ", " << sds.getHigh()
        <<  ", " << sds.getLow() << ", " << sds.getClose() << ", "
        << sds.getVolume();
    
    return out;
  }
}
