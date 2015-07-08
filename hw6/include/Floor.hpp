/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 8 July, 2015
  
  Revision History
      8 July, 2015 - class created
  
  Class Name: Floor
  
  Intent: Simulate the movement of passengers on and off the floor
  
  Description: 

*///============================================================================

#ifndef FLOOR_HPP
#define FLOOR_HPP

#include <ostream>

#include "Passenger.hpp"

namespace hw6
{  
  class Floor
  {
  public:
    Floor(int floorNumber = 0); // constructor
    
    // getters
    int getFloorNumber() const;
    Group getGoingUp() const;
    Group getGoingDown() const;
    
  private:
    int floorNumber; // what number the floor is
    Group goingUp; // the group of people who want to go up
    Group goingDown; // the group of people who
    
  }; // class Floor
  
  // output overloads
  std::ostream& operator<<(std::ostream& out, const Group& group);
  std::ostream& operator<<(std::ostream& out, const Floor& floor);

  /*============================================================================
    getFloorNumber
        return value of the floorNumber data member
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline int Floor::getFloorNumber() const
  {
    return this->floorNumber;
  }
  
  /*============================================================================
    getGoingDown
        return value of the goingDown data member
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline Group Floor::getGoingDown() const
  {
    return this->goingDown;
  }

  /*============================================================================
    getGoingUp
        return value of the goingUp data member
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline Group Floor::getGoingUp() const
  {
    return this->goingUp;
  }
  
} // namespace hw6

#endif // FLOOR_HPP
