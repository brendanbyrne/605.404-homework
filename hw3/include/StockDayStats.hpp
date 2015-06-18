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
    double getClose() const;  // return the closing trade price
    greg::date getDate() const; // return the date of the data point
    double getHigh() const; // return the highest trade price
    double getLow() const; // return the lowest trade price
    double getOpen() const; // return the opening trade price
    int getVolume() const; // return the number of trades made that day
    void setClose(const double newClosePrice); // set the closing price
    void setDate(const greg::date& newDate); // set the date of the data point
    void setHigh(const double newHighPrice); // set the highest trade price
    void setLow(const double newLowPrice); // set the lowest trade price
    void setOpen(const double newOpenPrice); // set the opening trade price
    void setVolume(const int newVolume); // set the number of trades made that day
    
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
    getSClose
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
  inline void StockDayStats::setClose(const double newClosePrice) // new price
  {
    this->closePrice = newClosePrice;
  }

  /*============================================================================
    setDate
        Sets the date when the recording were taken

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
  inline void StockDayStats::setDate(const greg::date& newDate) // new price
  {
    this->date = newDate;
  }

  /*============================================================================
    setHigh
        Sets the highest amount the stock traded for that day

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
  inline void StockDayStats::setHigh(const double newHighPrice) // new price
  {
    this->highPrice = newHighPrice;
  }

  /*============================================================================
    setLow
        Sets the lowest amount the stock traded for that day

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
  inline void StockDayStats::setLow(const double newLowPrice) // new price
  {
    this->lowPrice = newLowPrice;
  }

  /*============================================================================
    setOpen
        Sets the price that the stock opened for that day

    Revision History
    17 June, 2015 - function created
  *///==========================================================================
  inline void StockDayStats::setOpen(const double newOpenPrice) // new price
  {
    this->openPrice = newOpenPrice;
  }
  
  /*============================================================================
    setVolume
        Sets the number of shares that were trade that day

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
  inline void StockDayStats::setVolume(const int newVolume) // new traded volume
  {
    this->volumeTraded = newVolume;
  }
  
  // Overload for insertion operator
  std::ostream& operator<<(std::ostream&, const StockDayStats);
  
} // namespace hw3

#endif // STOCKDAYSTATS_HPP
