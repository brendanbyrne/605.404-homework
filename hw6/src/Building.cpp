// Building.cpp

#include "Building.hpp"

// for testing
#include <iostream>
#include <memory>

namespace hw6
{
  /*============================================================================
    Building
        default constructor for the Building class
        
    Revision History
        12 July 2015 - Function created
  *///==========================================================================
  Building::Building()
  {
  }
  
  /*============================================================================
    Building
        full constructor for the Building class
        
    Revision History
        12 July 2015 - Function created
  *///==========================================================================
  Building::Building(const Floors& floors, // the layout of the floors
		     const Elevators& elevators): // the buildings elevators
    floors(floors), elevators(elevators),
    controller(std::shared_ptr<Floors>(&this->floors),
	       std::shared_ptr<Elevators>(&this->elevators))
  {    
  }
  
  /*============================================================================
    addPerson
        add a person to the building who needs to ride an elevator
        
    Revision History
        12 July 2015 - Function created
  *///==========================================================================
  void Building::addPerson(const Passenger& person)
  {
    Request request = this->floors[person.getStartFloor()].waitInLine(person);
    this->controller.makeRequest(request);
  }
  
  /*============================================================================
    isEmpty
        returns true if there is any passengers still inside the building, on a
	floor, or in an elevator
        
    Revision History
        12 July 2015 - Function created
  *///==========================================================================
  bool Building::isEmpty()
  {
    bool isEmpty = true;
    
    // check all floors for people still waiting
    Floors::iterator floorIter = this->floors.begin();
    while (isEmpty && floorIter != this->floors.end())
    {
      if (!floorIter->getGoingUp().empty() ||
          !floorIter->getGoingDown().empty())
      {
	isEmpty = false;
      }
      else
      {
        ++floorIter;
      }
    }
    
    // check all elevators for people still riding
    Elevators::iterator elevatorIter = this->elevators.begin();
    while (isEmpty && elevatorIter != this->elevators.end())
    {
      if (elevatorIter->getOnBoard().size() > 0)
      {	
	isEmpty = false;
      }
      else
      {
        ++elevatorIter;
      }
    }
    
    return isEmpty;

  }
  
  /*============================================================================
    carryOutCommands
        takes the commands issued from the controller and carry them out
        
    Revision History
        13 July 2015 - Function created
  *///==========================================================================
  void Building::carryOutCommands()
  {

  }
  
} // namespace hw6
