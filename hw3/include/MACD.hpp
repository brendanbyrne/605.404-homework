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
    MACD();
    MACD(int fastEMA, int slowEMA, int signal);
    analyze(PriceHistory priceHistory);
    

  private:
    int fastEMA;
    int slowEMA;
    int signal;
    
  }; // class MACD
    
} // namespace hw3
