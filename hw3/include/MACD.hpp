/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 18 June, 2015
  
  Revision History
      18 June, 2015 - class created
  
  Class Name: MACD.hpp
  
  Intent: Given a history of a stock's price, calculate the Moving Average
          Convergence Divergence metric
  
  Description:  The construction of this object se

*///============================================================================

#ifndef MACD_HPP
#define MACD_HPP

#include "StockDayStats.hpp"

namespace hw3
{
  class MACD
  {
  public:
    MACD(); // default constructor
    MACD(int fastEMA, int slowEMA, int signal); // full constructor
    
    void analyze(PriceHistory priceHistory);
    
    int getFastEMA();
    int getSlowEMA();
    int getSignal();
    void setFastEMA(const int newValue);
    void setSlowEMA(const int newValue);
    void setSignal(const int newValue);
    
    bool wasSuccessful();
    
  private:
    int fastEMA;
    int slowEMA;
    int signal;
    
  }; // class MACD
  
  /*============================================================================
    GoogleHistoryParser
        Default constructor

    Revision History
        17 June, 2015 - function created
  *///==========================================================================
  
} // namespace hw3
