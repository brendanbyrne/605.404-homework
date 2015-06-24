/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 18 June, 2015
  
  Revision History
      18 June, 2015 - class created
  
  Class Name: AnalysisEntry
  
  Intent: A row of analysis data from the MACD analysis
  
  Description: As the MACD analysis is run row by row, a collection of this
               class would be used to capture the output row by row.  Comes 
               loaded with left shit overloading for easy displaying.  The
               double typed NaN is used as a sentinal to denote empty values.

*///============================================================================

#ifndef ANALYSIS_ENTRY_HPP
#define ANALYSIS_ENTRY_HPP

#include <vector>
#include <ostream>
#include <limits>
using nld = std::numeric_limits<double>;

#include <boost/date_time/gregorian/gregorian.hpp> // date
namespace greg = boost::gregorian;

#include "StockDayStats.hpp"

namespace hw3
{ 
  class AnalysisEntry
  {
  public:
    AnalysisEntry(const greg::date& date = greg::date(),
                  const double fastEMA = nld::quiet_NaN(),
                  const double slowEMA = nld::quiet_NaN(),
                  const double MACD = nld::quiet_NaN(),
                  const double signal = nld::quiet_NaN(),
                  const double histogram = nld::quiet_NaN());  // full constructor
    
    // Data Member Getters
    greg::date getDate() const;
    double getFastEMA() const;
    double getHistogram() const;
    double getMACD() const;
    double getSignal() const;
    double getSlowEMA() const;

    // Data Member Setters
    AnalysisEntry& setDate(const greg::date& newDate);
    AnalysisEntry& setFastEMA(const double newFastEMA);
    AnalysisEntry& setHistogram(const double newHistogram);
    AnalysisEntry& setMACD(const double newMACD);
    AnalysisEntry& setSignal(const double newSignal);
    AnalysisEntry& setSlowEMA(const double newSlowEMA);
    
  private:
    greg::date date; // date that the analysis data is for
    double fastEMA; // fast expontial moving average value
    double slowEMA; // slow expontial moving average value
    double MACD; // value of the Moving average convergence divergence analysis
    double signal; // value of the signal portion of the MACD analysis
    double histogram; // value of the histogram portion of the MACD analsis
    
  }; // AnalysisEntry
  
  /*============================================================================
    getDate
        returns the value of the date data member
        
    Revision History
        19 June, 2015 - Function created
  *///==========================================================================
  inline greg::date AnalysisEntry::getDate() const
  {
    return this->date;
  }
  
  /*============================================================================
    getFastEMA
        returns the value of the fastEMA data member

    Revision History
        19 June, 2015 - Function created
  *///==========================================================================
  inline double AnalysisEntry::getFastEMA() const
  {
    return this->fastEMA;
  }
  
  /*============================================================================
    getHistogram
        returns the value of the histogram data member

    Revision History
        19 June, 2015 - Function created
  *///==========================================================================
  inline double AnalysisEntry::getHistogram() const
  {
    return this->histogram;
  }
  
  /*============================================================================
    getMACD
        returns the value of the MACD data member

    Revision History
        19 June, 2015 - Function created
  *///==========================================================================
  inline double AnalysisEntry::getMACD() const
  {
    return this->MACD;
  }
  
  /*============================================================================
    getSignal
        returns the value of the signal data member

    Revision History
        19 June, 2015 - Function created
  *///==========================================================================
  inline double AnalysisEntry::getSignal() const
  {
    return this->signal;
  }

  /*============================================================================
    getSlowEMA
        returns the value of the slowEMA data member

    Revision History
        19 June, 2015 - Function created
  *///==========================================================================
  inline double AnalysisEntry::getSlowEMA() const
  {
    return this->slowEMA;
  }

  /*============================================================================
    setDate
        sets the value of the date data member

    Revision History
        19 June, 2015 - Function created
  *///==========================================================================
                                        // new value for the date
  inline AnalysisEntry& AnalysisEntry::setDate(const greg::date& newDate)
  {
    this->date = newDate;
    return *this;
  }

  /*============================================================================
    setFastEMA
        sets the value of the fastEMA data member

    Revision History
        19 June, 2015 - Function created
  *///==========================================================================
                                           // new value for the fastEMA
  inline AnalysisEntry& AnalysisEntry::setFastEMA(const double newFastEMA)
  {
    this->fastEMA = newFastEMA;
    return *this;
  }

  /*============================================================================
    setHistogram
        sets the value of the Histogram data member

    Revision History
        19 June, 2015 - Function created
  *///==========================================================================
                                                    // new value for the MACD
  inline AnalysisEntry& AnalysisEntry::setHistogram(const double newHistogram)
  {
    this->histogram = newHistogram;
    return *this;
  }
  
  /*============================================================================
    setMACD
        sets the value of the MACD data member

    Revision History
        19 June, 2015 - Function created
  *///==========================================================================
                                        // new value for the MACD
  inline AnalysisEntry& AnalysisEntry::setMACD(const double newMACD)
  {
    this->MACD = newMACD;
    return *this;
  }

  /*============================================================================
    setSignal
        sets the value of the signal data member

    Revision History
        19 June, 2015 - Function created
  *///==========================================================================
                                          // new value for the signal
  inline AnalysisEntry& AnalysisEntry::setSignal(const double newSignal)
  {
    this->signal = newSignal;
    return *this;
  }

  /*============================================================================
    setSlowEMA
        sets the value of the slowEMA data member

    Revision History
        19 June, 2015 - Function created
  *///==========================================================================
                                           // new value for the slowEMA
  inline AnalysisEntry& AnalysisEntry::setSlowEMA(const double newSlowEMA)
  {
    this->slowEMA = newSlowEMA;
    return *this;
  }
  
  // conveniene typedef for using the class
  typedef std::vector<AnalysisEntry> FullAnalysis;

  // operator overloads
  std::ostream& operator<<(std::ostream& out, const AnalysisEntry& entry);

} // namespace hw3

#endif // ANALYSIS_ENTRY_HPP
