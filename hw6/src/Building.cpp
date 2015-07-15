// Building.cpp

#include <algorithm> // any_if

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

    // if this is first request from floor for the desired direction
    if (this->floors[person.getStartFloor()].getLine(goalDirection).empty())
    {
      Request request = std::make_tuple(person.getStartTime(),
				      person.getEndFloor(),
				      goalDirection);
      this->requests.push_back(request);
    }

    this->floors[person.getStartFloor()].waitInLine(person);

  }
  
  /*============================================================================
    advance
        advance the state of the building and all the components inside of it
        
    Revision History
        14 July 2015 - Function created
  *///==========================================================================
  void Building::advance(int time)
  {
    // for each elevator, run it's state machine
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
        elevator.setGoalDirection(direction);
      }
      
      // run through the elevator state machine
      switch (elevator.getState())
      {
      case Elevator::State::MOVE:
        this->handleMoving(elevator, this->floors[elevator.getCurrentFloor()]);
        break;

      case Elevator::State::STOP:
        this->handleStopped(elevator,
			    this->floors[elevator.getCurrentFloor()],
			    time);
        break;
        
      default:
        // this is a bad place to be
        break;
      }
      
    } // for loop
    
  } // advance

  /*============================================================================
    handleMoving
        control the movement of an elevator
        
    Revision History
        14 July 2015 - Function created
  *///==========================================================================
  void Building::handleMoving(Elevator& elevator,
                              const Floor& floor)
  {
    // should the elevator start stopping
    bool shouldStop = false;
    
    // if elevator is at any floor
    if (elevator.getAlignment() == 0)
    {
      // has elevator reached the destination
      if (elevator.getGoalFloor() == elevator.getCurrentFloor())
      {
        shouldStop = true;
      }
      // if elevator should pickup extra passengers
      else if (elevator.getGoalDirection() == elevator.getMovingDirection() &&
	       elevator.hasRoom())
      {
        // if going down and passengers are waiting to go down
        if (!floor.getLine(elevator.getMovingDirection()).empty())
        {
          shouldStop = true;
        }

      } // if should pick up or drop off people
    } // if on floor
    
    if (shouldStop)
    {
      elevator.slowDown();
    }
    else
    {
      elevator.move();
    }
  } // handleMoving
  
  
  /*============================================================================
    handleStopped
        manage the interactions between passengers, floors, and elevators
        
    Revision History 
        14 July 2015 - Function created
  *///==========================================================================
  void Building::handleStopped(Elevator& elevator,
                               Floor& floor,
			       int time)
  {
    // if elevator has intent to pickup or drop off
    if (elevator.getGoalSet())
    {
      // lets passengers off if they desire
      Group leaving = elevator.exit();
      for (auto & passenger : leaving)
      {
	passenger.setEndTime(time);
	this->exitResults.push_back(passenger);
      }
      
      // while there is room and people wanting to ride
      while (elevator.hasRoom() &&
	     !floor.getLine(elevator.getGoalDirection()).empty())
      {
	elevator.board(floor.getNextInLine(elevator.getGoalDirection()));
      }
            
      // if not empty resubmit the elevator request
      if (!floor.getLine(elevator.getGoalDirection()).empty())
      {
	// get the next person in line
	Passenger person = floor.getLine(elevator.getGoalDirection()).front();
	Request resubmission = std::make_tuple(person.getStartTime(),
					       person.getEndFloor(),
					       elevator.getGoalDirection());
	this->requests.push_back(resubmission);
	this->requests.sort();
      }

      elevator.updateGoalFloor();
    }

    
    
  } // handleStopped
  
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

  } // isEmpty
    
} // namespace hw6
