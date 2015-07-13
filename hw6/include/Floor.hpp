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
    Line getGoingUp() const;
    Line getGoingDown() const;
    
    Passenger getOnUp(); // have going up passenger get on elevator
    Passenger getOnDown(); // have going down passenger get on elevator
    void waitInLine(const Passenger& passenger); // have passenger wait in line
    
  private:
    int floorNumber; // what number the floor is
    Line goingUp; // a line of people who want to go up
    Line goingDown; // a line of people who want to go down
    
  }; // class Floor
  
  // convenience alias
  typedef std::vector<Floor> Floors;

  // output overloads
  std::ostream& operator<<(std::ostream& out, Line line);
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
  inline Line Floor::getGoingDown() const
  {
    return this->goingDown;
  }

  /*============================================================================
    getGoingUp
        return value of the goingUp data member
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline Line Floor::getGoingUp() const
  {
    return this->goingUp;
  }
  
  /*============================================================================
    getOnUp
        return next person in line going up
        
    Revision History
        9 July 2015 - Function created
  *///==========================================================================
  inline Passenger Floor::getOnUp()
  {
    Passenger passenger = this->goingUp.front();
    this->goingUp.pop();
    return passenger;
  }
  
  /*============================================================================
    getOnDown
        return next person in line going down
        
    Revision History
        9 July 2015 - Function created
  *///==========================================================================
  inline Passenger Floor::getOnDown()
  {
    Passenger passenger = this->goingDown.front();
    this->goingDown.pop();
    return passenger;
  }  
  
} // namespace hw6

#endif // FLOOR_HPP
