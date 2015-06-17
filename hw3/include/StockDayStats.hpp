/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 17 June, 2015
  
  Revision History
      17 June, 2015 - class created
  
  Class Name: StockDayStats.hpp
  
  Intent: Organize the statistics from a day of trading
  
  Description: This file defines the StockDayStats class which maintains the
               information from day  
  
*///============================================================================

#ifndef STOCKDAYSTATS_HPP
#define STOCKDAYSTATS_HPP

#include <string>
#include <ostream>

#include <boost/date_time/gregorian/gregorian.hpp> // date
namespace greg = boost::gregorian;

namespace hw3
{
  class StockDayStats
  {
  public:
    StockDayStats();
    StockDayStats(std::string);
    double getClose();
    greg::date getDate();
    double getHigh();
    double getLow();
    double getOpen(); 
    int getVolume();

  private:
    double closePrice;
    greg::date date;
    double highPrice;
    double lowPrice;
    double openPrice;
    int volumeTraded;
    
  }; // class StockDayStats

  /*============================================================================
    setSuit
        Sets the "suit" data member to the input value

    Revision History
        14 June, 2015 - function created
  *///==========================================================================
  inline double StockDayStats::getClose()
  {
    return this->closePrice;
  }

  /*============================================================================
    setSuit
        Sets the "suit" data member to the input value

    Revision History
        14 June, 2015 - function created
  *///==========================================================================
  inline greg::date getDate()
  {
    return this->date;
  }

  /*============================================================================
    setSuit
        Sets the "suit" data member to the input value

    Revision History
        14 June, 2015 - function created
  *///==========================================================================
  inline double getHigh()
  {
    return this->highPrice;
  }

  /*============================================================================
    setSuit
        Sets the "suit" data member to the input value

    Revision History
        14 June, 2015 - function created
  *///==========================================================================
  inline double getLow()
  {
    return this->lowPrice;
  }

  /*============================================================================
    setSuit
        Sets the "suit" data member to the input value

    Revision History
        14 June, 2015 - function created
  *///==========================================================================
  inline double getOpen()
  {
    return this->openPrice;
  }

  /*============================================================================
    setSuit
        Sets the "suit" data member to the input value

    Revision History
        14 June, 2015 - function created
  *///==========================================================================
  inline int getVolume()
  {
    return this->volumeTraded;
  }
  
  std::ostream& operator<<(std::ostream&, const StockDayStats);
}; // namespace hw3

#endif // STOCKDAYSTATS_HPP
