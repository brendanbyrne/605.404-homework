#include "Part.hpp"

namespace hw5
{
  /*============================================================================
    Part
        class constructor
        
    Revision History
        6 July 2015 - Function created
  *///==========================================================================
  Part::Part(const std::string& partNumber, // the name of the part
             const std::string& description): // part description
    partNumber(partNumber), description(description)
  {
  }
  
  /*============================================================================
    operator<<
        the insertion operator overload
        
    Revision History
        6 July 2015 - Function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, const Part& part)
  {
    out << "Part Number: " << part.getPartNumber() << "\n";
    out << "  Description: " << part.getDescription() << "\n\n";
    out << "  Kits that include this part:\n";
    
    for (auto kitInfo : part.getKits())
    {
      out << "    Kit Name: " << kitInfo.first << "\n";
      out << "      Required: " << kitInfo.second << "\n";
    }
    
    return out;
  }
  
} // namespace hw5
