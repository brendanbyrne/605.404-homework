/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 4 July, 2015
  
  Revision History
      6 July, 2015 - class created
  
  Class Name: Part
  
  Intent: A class to track the usage of a part throughout different kits
  
  Description: The description and part number are unique to the part but many
               kits can have the part and it varying quantities.

*///============================================================================

#ifndef PART_HPP
#define PART_HPP

#include <ostream>
#include <utility>
#include <vector>
#include <string>

namespace hw5
{
  // container for holding the parts relations with different kits
  typedef std::vector< std::pair<std::string, int> > KitList;
  
  class Part
  {
  public:
    Part(const std::string& partNumber = "Null",
         const std::string& description = "Not a part"); // constructor
    
    // adds part info about a particular bill of materials
    void addToKits(const std::pair<std::string, int>& kitDetails);

    // getters
    std::string getDescription() const;
    KitList getKits() const;
    std::string getPartNumber() const;
    
  private:
    std::string partNumber; // the name of the part
    std::string description; // the description of the part
    KitList kits; // different kits and the amount for each
    
  }; // class Part
  
  // insertion overload
  std::ostream& operator<<(std::ostream& out, const Part& part);
  
  /*============================================================================
    addToKits
        adds a bill of materials and quantity to the part's KitList
        
    Revision History
        6 July 2015 - Function created
  *///==========================================================================
  //                          the information about a parts inclusion
  //                          in a bill of materials
  inline void Part::addToKits(const std::pair<std::string, int>& kitDetails)
  {
    this->kits.push_back(kitDetails);
  }

  /*============================================================================
    getDescription
        returns the description of the part
        
    Revision History
        6 July 2015 - Function created
  *///==========================================================================
  inline std::string Part::getDescription() const
  {
    return this->description;
  }
      
  /*============================================================================
    getKits
        returns the kits, and the amount need, that part of is in
        
    Revision History
        6 July 2015 - Function created
  *///==========================================================================
  inline KitList Part::getKits() const
  {
    return this->kits;
  }
  
  /*============================================================================
    getPartNumber
        returns part number of said part
        
    Revision History
        6 July 2015 - Function created
  *///==========================================================================
  inline std::string Part::getPartNumber() const
  {
    return this->partNumber;
  }

} // namespace hw5

#endif // PART_HAPP
