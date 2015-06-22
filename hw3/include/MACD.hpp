/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 18 June, 2015
  
  Revision History
      18 June, 2015 - class created
  
  Class Name: MACD
  
  Intent: Given a history of a stock's price, calculate the Moving Average
          Convergence Divergence metric
  
  Description:  Computes a MACD analsys over the given input data set and
                returns a vector of type AnalysisEntry.  After the analsys
                several flags can be set.  These flags coorspond to errors in
                the analizing process.  The see *Size data members describe the
                how far back the each EMA look up goes.

*///============================================================================

#ifndef MACD_HPP
#define MACD_HPP

#include "StockDayStats.hpp"
#include "AnalysisEntry.hpp"

namespace hw3
{  
  class MACD
  {
  public:

    // default window sizes for the different calculations
    static const int DEFAULT_FAST_SIZE = 12;
    static const int DEFAULT_SLOW_SIZE = 26;
    static const int DEFAULT_SIGNAL_SIZE = 9;
    
    MACD(const int fastEMASize = DEFAULT_FAST_SIZE, 
         const int slowEMASize = DEFAULT_SLOW_SIZE,
         const int signalSize = DEFAULT_SIGNAL_SIZE); // full constructor

    // perform MACD analysis
    FullAnalysis analyze(const PriceHistory& priceHistory);
    // checks for properly sized input data
    void checkRanges(const PriceHistory& priceHistory);
    
    int getFastEMASize() const; // fast EMA window size getter
    int getSlowEMASize() const; // slow EMA window size getter
    int getSignalSize() const; // signal window size getter
    bool hasErrors() const; // returns true if there is an error flag set
    void setFastEMASize(const int newFastEMASize); // fast EMA window size setter
    void setSlowEMASize(const int newSlowEMASize); // slow EMA window size setter
    void setSignalSize(const int newSignalSize); // signal window size setter
    
  private:
    // analysis window size parameters
    int fastEMASize;
    int slowEMASize;
    int signalSize;

    // error flags, false mean no error
    bool fastSizeError;
    bool slowSizeError;
    bool signalSizeError;    

    // attempt 
    double closePriceEMA(double closePrice,
                         double previousEMA,
                         int windowSize,
                         PriceHistory::const_iterator start,
                         PriceHistory::const_iterator end);
  }; // class MACD
  
  /*============================================================================
    getFastEMASize
        Returns the value of the fastEMA data member

    Revision History
        19 June, 2015 - function created
  *///==========================================================================
  inline int MACD::getFastEMASize() const
  {
    return this->fastEMASize;
  }

  /*============================================================================
    getSlowEMASize
        Returns the value of the slowEMASize data member

    Revision History
        19 June, 2015 - function created
  *///==========================================================================
  inline int MACD::getSlowEMASize() const
  {
    return this->slowEMASize;
  }
  
  /*============================================================================
    getSignalSize
        Returns the value of the signal data member

    Revision History
        19 June, 2015 - function created
  *///==========================================================================
  inline int MACD::getSignalSize() const
  {
    return this->signalSize;
  }

  /*============================================================================
    hasErrors
        Returns whether or not the analyzer has an error flag set to true

    Revision History
        20 June, 2015 - function created
  *///==========================================================================
  inline bool MACD::hasErrors() const
  {
    return this->fastSizeError || this->slowSizeError || this->signalSizeError;
  }
  
  /*============================================================================
    setFastEMASize
        Sets the value of the fastEMASize data member to input value

    Revision History
        19 June, 2015 - function created
  *///==========================================================================
                                   // new value for fastEMASize
  inline void MACD::setFastEMASize(const int newFastEMASize) 
  {
    this->fastEMASize = newFastEMASize;
  }

  /*============================================================================
    setSlowEMASize
        Sets the value of the slowEMASize data member to input value

    Revision History
        19 June, 2015 - function created
  *///==========================================================================
                                  // new value for slowEMASize
  inline void MACD::setSlowEMASize(const int newSlowEMASize)
  {
    this->slowEMASize = newSlowEMASize;
  }

  /*============================================================================
    setSignal
        Sets the value of the signal data member to input value

    Revision History
        19 June, 2015 - function created
  *///==========================================================================
                                  // new value for signalSize
  inline void MACD::setSignalSize(const int newSignalSize)
  {
    this->signalSize = newSignalSize;
  }
} // namespace hw3

#endif // MACD_HPP
