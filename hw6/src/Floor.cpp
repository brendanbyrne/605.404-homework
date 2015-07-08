// Floor.cpp
#include <algorithm> // for_each
#include <vector>
#include <sstream>

#include <boost/algorithm/string/join.hpp>

#include "Floor.hpp"

namespace hw6
{
  /*============================================================================
    Floor
        The default constructor

    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  Floor::Floor(int floorNumber):
    floorNumber(floorNumber)
  {
  }
  
  /*============================================================================
    operator<<
        insertion operator overload for a Floor object
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, // desired output stream
                           const Group& group) // object to display
  {
    // set up string receiving container
    std::vector<std::string> strPassVect;
    strPassVect.reserve(group.size());
    
    // add string representation of  passengers to the vector
    std::for_each(group.begin(), group.end(),
                  [&strPassVect](const Passenger& pass)
                  {
                    std::stringstream ss;
                    ss << pass;
                    strPassVect.push_back(ss.str());
                  });
    
    out << boost::algorithm::join(strPassVect, " ");
    
    return out;
  }

  /*============================================================================
    operator<<
        insertion operator overload for a Floor object
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, // desired output stream
                           const Floor& floor) // object to display
  {
    out << "Floor " << floor.getFloorNumber() << "\n"
        << "  " << "Going Up" << "\n"
        << "    " << floor.getGoingUp() << "\n"
        << "  " << "Going Down" << "\n"
        << "    " << floor.getGoingDown();
    
    return out;
  }
                           
} // namespace hw6
