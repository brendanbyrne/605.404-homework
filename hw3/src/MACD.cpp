// MACP.cpp

#include <algorithm> // for_each
#include <cmath> // for isnan

#include "MACD.hpp"

// for testing
#include <iostream>

namespace hw3
{
  /*============================================================================
    MACD
        full constructor

    Revision History
        19 June, 2015 - Function created
  *///==========================================================================
  MACD::MACD(const int fastEMASize, // look up size for fast average
             const int slowEMASize, // look up size for slow average
             const int signalSize): // look up size for signal
    fastEMASize(fastEMASize), slowEMASize(slowEMASize), signalSize(signalSize),
    fastSizeError(true)
  {
  }

  /*============================================================================
    analyze
        perform the MACD analysis on the given data set
    
    Revision History
        20 June, 2015 - Function created
  *///==========================================================================
  FullAnalysis MACD::analyze(const PriceHistory& priceHistory) // date to analyze
  {    
    //reset the error flag
    this->fastSizeError = false;
    this->slowSizeError = false;
    this->signalSizeError = false;
    
    FullAnalysis analysisOutput;

    // check if analysis is ok to run
    this->checkRanges(priceHistory);
    if (this->hasErrors())
    {
      return analysisOutput;
    }
    
    // setup output
    analysisOutput.reserve(priceHistory.size());
    
    // initialize variables
    double fastEMA;
    double slowEMA;
    double signal;

    int i = 0;
    // loop through the price data and perform the analysis
    PriceHistory::const_iterator phIT = priceHistory.begin();
    FullAnalysis::iterator faIT = analysisOutput.begin();
    while (phIT < priceHistory.end())
    {
      //Begin building an entry
      AnalysisEntry entry(phIT->getDate());

      std::cout << i++ << ": " << phIT->getClose() << std::endl;
      
      // if there is enough room to perform the smaller sized EMA
      if (phIT - this->fastEMASize+1 >= priceHistory.begin())
      {
        PriceHistory::const_iterator start = phIT - this->fastEMASize + 1;
        PriceHistory::const_iterator end = phIT + 1;        
        
        fastEMA = this->closePriceEMA(phIT->getClose(),
                                      (faIT-1)->getFastEMA(),
                                      this->fastEMASize,
                                      start,
                                      end);
        entry.setFastEMA(fastEMA);
      }

      // if there is enough data to do a larger sized EMA
      if (phIT - this->slowEMASize + 1 >= priceHistory.begin())
      {
        PriceHistory::const_iterator start = phIT - this->slowEMASize + 1;
        PriceHistory::const_iterator end = phIT + 1;

        slowEMA = this->closePriceEMA(phIT->getClose(),
                                      (faIT-1)->getSlowEMA(),
                                      this->slowEMASize,
                                      start,
                                      end);
        entry.setSlowEMA(slowEMA);
        entry.setMACD(entry.getFastEMA() - entry.getSlowEMA());
      }

      // if there is enough data to find the signal
      int windowSize = this->slowEMASize + this->signalSize - 1;
      if (phIT - windowSize >= priceHistory.begin())
      {
        // calc signal and histogram
        std::cout << "here" << std::endl;
        double previousSignal = (faIT-1)->getSignal();
        FullAnalysis::const_iterator start;
        start = faIT - windowSize;
        FullAnalysis::const_iterator end = faIT + 1;
        
        if (!std::isnan(previousSignal))
        {
          signal = entry.getMACD() * (2.0 / (windowSize + 1.0)) +
                   previousSignal * (1.0 - (2.0 / (windowSize + 1)));
        }
        else
        {
          double sum = 0.0;
          std::for_each(start, end,
                        [&sum](const AnalysisEntry& ae)
                        {
                          sum += ae.getMACD();
                        });
          signal = sum / static_cast<double>(end - start);
        }
        
        entry.setSignal(signal);
        entry.setHistogram(entry.getMACD() - entry.getSignal());
        break;
      }

      *faIT = entry;
      
      ++phIT;
      ++faIT;
    }
    
    return analysisOutput;
  }
  
  /*============================================================================
    checkRanges
        makes sure there is enough data to perform the analysis
    
    Revision History
        20 June, 2015 - Function created
  *///==========================================================================
  void MACD::checkRanges(const PriceHistory& priceHistory)
  {
    if (priceHistory.size() < this->fastEMASize)
    {
      this->fastSizeError = true;
    }
    
    if (priceHistory.size() < this->slowEMASize)
    {
      this->slowSizeError = true;
    }

    // - 1 to account of the slowEMA and signal overlap
    if (priceHistory.size() < this->slowEMASize + this->signalSize - 1)
    {
      this->signalSizeError = true;
    } 
  }

  /*============================================================================
    closePriceEMA
        returns an exponential moving average or a simple arithmetic mean based
        on what data has already been calculated
    
    Revision History
        22 June, 2015 - Function created
  *///==========================================================================
  double MACD::closePriceEMA(double closePrice,
                             double previousEMA,
                             int windowSize,
                             PriceHistory::const_iterator start,
                             PriceHistory::const_iterator end)
  {
    double emaPrice;
    
    // if a previous EMA has been calculated
    if (!std::isnan(previousEMA))
    {
      // find the exponential moving average
      emaPrice = closePrice * (2.0 / (windowSize + 1.0)) +
                 previousEMA * (1.0 - (2.0 / (windowSize + 1)));
    }
    else
    {      
      // find arithmetic mean
      double sum = 0.0;
      std::for_each(start, end,
                    [&sum](const StockDayStats& stats)
                    {
                      sum += stats.getClose();
                    });
      
      emaPrice = sum / static_cast<double>(end-start);
    }
    
    return emaPrice;
  }
  
} // namespace hw3
