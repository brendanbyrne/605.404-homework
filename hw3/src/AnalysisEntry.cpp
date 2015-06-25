// AnalysisEntry.cpp

#include "AnalysisEntry.hpp"

namespace hw3
{
  /*============================================================================
    AnalysisEntry
        full constructor

    Revision History
        19 June, 2015 - Function created
  *///==========================================================================
  AnalysisEntry::AnalysisEntry(const greg::date& date, // desired date of entry
                               const double fastEMA, // calculated fastEMA
                               const double slowEMA, // calculated slowEMA
                               const double MACD, // calculated MACD
                               const double signal, // calculated signal
                               const double histogram): // calculated histogram
    date(date), fastEMA(fastEMA), slowEMA(slowEMA),
    MACD(MACD), signal(signal), histogram(histogram)
  {
  }

  /*============================================================================
    AnalysisEntry
        constructor that intializes the date of the of the entry

    Revision History
        19 June, 2015 - Function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, // desired output stream
                           const AnalysisEntry& entry) // entry to output
  {
    out << entry.getDate() << "," << entry.getFastEMA()
        << "," << entry.getSlowEMA()
        << "," << entry.getMACD()
        << "," << entry.getSignal()
        << "," << entry.getHistogram();
    return out;
  }  
} // namespace hw3
