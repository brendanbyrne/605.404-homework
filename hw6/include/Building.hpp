/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 8 July, 2015
  
  Revision History
      8 July, 2015 - class created
  
  Class Name: Building
  
  Intent: Controls interaction between the different systems inside the building
  
  Description: Manages how people move from floor to elevator, elevator to floor
               and contains the elevator controller.  The classes allows for
	       easy communication between all the components of the Building

*///============================================================================

#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <list>
#include <tuple>

#include "Elevator.hpp"
#include "Floor.hpp"
#include "Passenger.hpp"

namespace hw6
{  
  class Building
  {
  public:
    // time, startFloor, desired direction
    typedef std::tuple<int, int, Direction> Request;

    Building(); // default constructor
    Building(const Floors& floors,
	     const Elevators& elevators); // full constructor
    
    void addPerson(const Passenger& person); // put a passenger on a floor
    bool isEmpty(); // any passengers on a floor or in a elevator
    
    // testing purposes
    void advance();
    
    // getters
    Elevators getElevators() const;
    Floors getFloors() const;
    
    // state machine handlers
    void handleMoving(Elevator& elevator, const Floor& floor);
    void handleStopped(Elevator& elevator, Floor& floor);
    
    // setters
    Building& setElevators(const Elevators& elevators);
    Building& setFloors(const Floors& floors);

  private:
    Elevators elevators; // elevators in the building
    Floors floors; // the floors in the building
    std::list<Request> requests; // stores the requests for elevators
    
    
  }; // class Building
  
  /*============================================================================
    getElevators
        return the value of the elevators data member
        
    Revision History
        12 July 2015 - Function created
  *///==========================================================================
  inline Elevators Building::getElevators() const
  {
    return this->elevators;
  }

  /*============================================================================
    getFloors
        return the value of the floors data member
        
    Revision History
        12 July 2015 - Function created
  *///==========================================================================
  inline Floors Building::getFloors() const
  {
    return this->floors;
  }
  
  /*============================================================================
    setElevators
        set the value of the elevators data member
        
    Revision History
        12 July 2015 - Function created
  *///==========================================================================
  inline Building& Building::setElevators(const Elevators& elevators)
  {
    this->elevators = elevators;
    return *this;
  }
  
  /*============================================================================
    setFloors
        set the value of the floors data member
        
    Revision History
        12 July 2015 - Function created
  *///==========================================================================
  inline Building& Building::setFloors(const Floors& floors)
  {
    this->floors = floors;
    return *this;
  }
  
} // namespace hw6

#endif // BUILDING_HPP
