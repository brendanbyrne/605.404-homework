/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 17 June, 2015
  
  Revision History
      17 June, 2015 - class created
  
  Class Name: StockDayStats.hpp
  
  Intent: Organize the statistics from a day of trading
  
  Description: StockDayStats holds the information that describes the state of
               a stock after of a of day of trading
*///============================================================================

#ifndef STOCKDAYSTATS_HPP
#define STOCKDAYSTATS_HPP

#include <string>
#include <ostream>
#include <vector>

#include <boost/date_time/gregorian/gregorian.hpp> // date
namespace greg = boost::gregorian;

namespace hw3
{
  class StockDayStats
  {    
  public:
    StockDayStats(); // default constructor
    StockDayStats(const greg::date& date, // date  full constructor
                  const double openPrice, // open
                  const double highPrice, // high
                  const double lowPrice, // low
                  const double closePrice, // close
                  const int volumeTraded); // volume
    
    // Data Member Getters
    double getClose() const;
    greg::date getDate() const;
    double getHigh() const;
    double getLow() const;
    double getOpen() const;
    int getVolume() const;
    
    // Data Member Setters
    StockDayStats& setClose(const double newClosePrice);
    StockDayStats& setDate(const greg::date& newDate);
    StockDayStats& setHigh(const double newHighPrice);
    StockDayStats& setLow(const double newLowPrice);
    StockDayStats& setOpen(const double newOpenPrice);
    StockDayStats& setVolume(const int newVolume);
    
  private:
    double closePrice; // the closing price after a day of trading
    greg::date date; // the day the data is from
    double highPrice; // the highest price the stock traded for that day
    double lowPrice; // the lowest price the stock traded for that day
    double openPrice; // the opening price of the 
    int volumeTraded; // the number of shares traded that day
    
  }; // class StockDayStats

  // convenience typedef for a collection of StockDayStats
  typedef std::vector<StockDayStats> PriceHistory;
  
  /*============================================================================
    getClose
        Returns the closing value of the stock

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
  inline double StockDayStats::getClose() const
  {
    return this->closePrice;
  }

  /*============================================================================
    getDate
        Returns the date when the recording were taken

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
  inline greg::date StockDayStats::getDate() const
  {
    return this->date;
  }

  /*============================================================================
    getHigh
        Returns the highest amount the stock traded for that day

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
  inline double StockDayStats::getHigh() const
  {
    return this->highPrice;
  }

  /*============================================================================
    getLow
        Returns the lowest amount the stock traded for that day

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
  inline double StockDayStats::getLow() const
  {
    return this->lowPrice;
  }

  /*============================================================================
    getOpen
    Returns the price that the stock opened for that day

    Revision History
    17 June, 2015 - function created
  *///==========================================================================
  inline double StockDayStats::getOpen() const
  {
    return this->openPrice;
  }

  /*============================================================================
    getVolume
        Returns the number of shares that were trade that day

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
  inline int StockDayStats::getVolume() const
  {
    return this->volumeTraded;
  }

  /*============================================================================
    setClose
        Set the closing value of the stock

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
                                                // new price
  inline StockDayStats& StockDayStats::setClose(const double newClosePrice) 
  {
    this->closePrice = newClosePrice;
    return *this;
  }

  /*============================================================================
    setDate
        Sets the date when the recording were taken

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
                                               // new price
  inline StockDayStats& StockDayStats::setDate(const greg::date& newDate) 
  {
    this->date = newDate;
    return *this;
  }

  /*============================================================================
    setHigh
        Sets the highest amount the stock traded for that day

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
                                               // new price
  inline StockDayStats& StockDayStats::setHigh(const double newHighPrice)
  {
    this->highPrice = newHighPrice;
    return *this;
  }

  /*============================================================================
    setLow
        Sets the lowest amount the stock traded for that day

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
                                              // new price
  inline StockDayStats& StockDayStats::setLow(const double newLowPrice)
  {
    this->lowPrice = newLowPrice;
    return *this;
  }

  /*============================================================================
    setOpen
        Sets the price that the stock opened for that day

    Revision History
    17 June, 2015 - function created
  *///==========================================================================
                                               // new price
  inline StockDayStats& StockDayStats::setOpen(const double newOpenPrice)
  {
    this->openPrice = newOpenPrice;
    return *this;
  }
  
  /*============================================================================
    setVolume
        Sets the number of shares that were trade that day

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
                                                 // new traded volume
  inline StockDayStats& StockDayStats::setVolume(const int newVolume) 
  {
    this->volumeTraded = newVolume;
    return *this;
  }
  
  // Overload for insertion operator
  std::ostream& operator<<(std::ostream&, const StockDayStats&);
  
} // namespace hw3

#endif // STOCKDAYSTATS_HPP
