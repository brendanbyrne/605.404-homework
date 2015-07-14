// Building.cpp

#include "Building.hpp"

// for testing
#include <iostream>

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
    floors(floors), elevators(elevators)
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
    Direction goalDirection;
    
    int numberDirection = person.getEndFloor() - person.getStartFloor();
    if (numberDirection > 0)
    {
      goalDirection = Direction::UP;
    }
    else if (numberDirection < 0)
    {
      goalDirection = Direction::DOWN;
    }
    
    Request request = std::make_tuple(person.getStartTime(),
				      person.getEndFloor(),
				      goalDirection);
    
    this->floors[person.getStartFloor()].waitInLine(person);
  }
  
  void Building::advance()
  {
    for (auto & elevator : this->elevators)
    {
      // if elevator wants work and there is work
      if (elevator.isEmpty() && !elevator.getGoalSet() &&
	  this->requests.size() == 0)
      {
	int floor;
	Direction direction;
	std::tie(std::ignore, floor, direction) = this->requests.front();
	this->requests.pop_front();
	
	elevator.setGoalFloor(floor);
      }

      // run throught the state machine
      switch (elevator.getState())
      {
      case Elevator::State::MOVING:
	break;

      case Elevator::State::STOPPING:
	break;
	
      case Elevator::State::STOPPED:
	break;
	
      default:
	// this is a bad place to be
	std::cout << "Elevator state not found" << std::endl;
      } // switch state
      
    } // for loop
    
  } // advance

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
