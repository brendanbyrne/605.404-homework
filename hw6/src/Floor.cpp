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
    getNextInLine
        return next person in line going either up or down
        
    Revision History
        14 July 2015 - Function created
  *///==========================================================================
  Passenger Floor::getNextInLine(const Direction& direction)
  {
    Passenger passenger;
    if (direction == Direction::UP)
    {
      passenger = this->goingUp.front();
      this->goingUp.pop();
    }
    else
    {
      passenger = this->goingDown.front();
      this->goingDown.pop();
    }
    
    return passenger;
  }  

  /*============================================================================
    getLine
        return value of the goingUp or goingDown
        
    Revision History
        14 July 2015 - Function created
  *///==========================================================================
  Line Floor::getLine(const Direction& direction) const
  {
    if (direction == Direction::UP)
    {
      return this->goingUp;
    }
    else if (direction == Direction::DOWN)
    {
      return this->goingDown;
    }
    else
    {
      Line line;
      return line;
    }
  }

  /*============================================================================
    operator<<
        insertion operator overload for a Floor object
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, // desired output stream
                           Line line) // object to display
  {
    // set up string receiving container
    std::vector<std::string> strPassVect;
    strPassVect.reserve(line.size());
    
    // retrieve all items from the queue
    while (!line.empty())
    {
      std::stringstream ss;
      ss << line.front();
      line.pop();
      
      strPassVect.push_back(ss.str());
    }
    
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
  
  /*============================================================================
    waitInLine
        add passenger to a line
        
    Revision History
        9 July 2015 - Function created
  *///==========================================================================
  void Floor::waitInLine(const Passenger& passenger) // person needing elevator
  {  
    int direction = passenger.getEndFloor() - passenger.getStartFloor();
    
    if (direction > 0)
    {      
      this->goingUp.push(passenger);
    }
    else if (direction < 0)
    {
      this->goingDown.push(passenger);
    }
  }
                           
} // namespace hw6
