// Building.cpp

#include <algorithm> // any_if

#include "Building.hpp"

// for testing
#include <iostream>
#include <string>

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
    
    std::cout << "Making new request!" << std::endl;
    Request request = std::make_tuple(person.getStartTime(),
				      person.getStartFloor(),
				      goalDirection);
    this->requests.add(request);

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
    
    std::cout << std::string(80, '=') << std::endl;
    
    
    // for each elevator, run it's state machine
    for (auto & elevator : this->elevators)
    {
      std::cout << elevator << std::endl;
      std::cout << this->floors[4] << std::endl;
      
      // run through the elevator state machine
      switch (elevator.getState())
      {
      case Elevator::State::MOVE:
        this->handleMoving(elevator, this->floors[elevator.getCurrentFloor()]);
        break;

      case Elevator::State::STOP:
        this->handleStopped(elevator, this->floors[elevator.getCurrentFloor()]);
        break;
        
      case Elevator::State::UNLOAD:
        this->handleUnloading(elevator,
                              this->floors[elevator.getCurrentFloor()],
                              time);
        break;
        
      case Elevator::State::LOAD:
        this->handleLoading(elevator, this->floors[elevator.getCurrentFloor()]);
        break;
        
      default:
        // this is a bad place to be
        break;
      }
      
    } // for loop
    
  } // advance

  void Building::handleLoading(Elevator& elevator,
                               Floor& floor)
  {
    // while there is room and people wanting to ride
    while (elevator.hasRoom() &&
           !floor.getLine(elevator.getGoalDirection()).empty())
    {
      elevator.board(floor.getNextInLine(elevator.getGoalDirection()));
    }
    
    // if the queue is empty,  clear any assiocated requests
    if (floor.getLine(elevator.getGoalDirection()).empty())
    {
      Request clearKey = std::make_tuple(0,
                                         floor.getNumber(),
                                         elevator.getGoalDirection());
      this->requests.clear(clearKey);
    }
    // else resubmit the elevator request
    else
    {
      // get the next person in line
      Passenger person = floor.getLine(elevator.getGoalDirection()).front();
      Request resubmission = std::make_tuple(person.getStartTime(),
                                             floor.getNumber(),
                                             elevator.getGoalDirection());
      this->requests.update(resubmission);
    }
    
    if (!elevator.isEmpty())
    {
      elevator.updateGoalFloor();
      elevator.setState(Elevator::State::MOVE);
    }
    else
    {
      elevator.setState(Elevator::State::STOP);
    }

  } // handleLoading
  
  /*============================================================================
    handleMoving
        control the movement of an elevator9
        
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
      else if (elevator.getGoalDirection() == elevator.getMoveDirection() &&
	       elevator.hasRoom())
      {
        // if going down and passengers are waiting to go down
        if (!floor.getLine(elevator.getMoveDirection()).empty())
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
        figure out if elevator should load, unload, or just sit
        
    Revision History 
        14 July 2015 - Function created
  *///==========================================================================
  void Building::handleStopped(Elevator& elevator,
                               Floor& floor)
  {
    // if there are people on board see if they want to get off
    if (!elevator.isEmpty())
    {
      elevator.setState(Elevator::State::UNLOAD);
      return;
    }
    // if not, then see if elevator can go straight to unloading
    else if (!floor.getLine(elevator.getGoalDirection()).empty())
    {
      elevator.setState(Elevator::State::LOAD);
      return;
    }
    // else just sit, twiddle thumbs, and wait for work
    else
    {
      // if elevator wants work and there is work
      if (elevator.isEmpty() && !elevator.getGoalSet() &&
	  this->requests.size() != 0)
      {
	int floor;
	Direction direction;
        
        std::cout << "Fetching request!" << std::endl;
        
        std::tie(std::ignore, floor, direction) = this->requests.front();
        this->requests.pop();
	
        elevator.setGoal(floor, direction);        
      }
      return;
    } 
    
  } // handleStopped
  
  
  void Building::handleUnloading(Elevator& elevator,
                                 Floor& floor,
                                 const int time)
  {
    // lets passengers off if they desire
    Group leaving = elevator.exit();
    std::cout << "size of leaving: " << leaving.size() << std::endl;
    for (auto & passenger : leaving)
    {
      std::cout << "Passenger: " << passenger << " is leaving"
                << std::endl;
      passenger.setEndTime(time);
      this->exitResults.push_back(passenger);
    }
    
    
    
    // if there are people to pick up then attempt to load them
    if (!floor.getLine(elevator.getGoalDirection()).empty())
    {
      elevator.setState(Elevator::State::LOAD);
    }
    else
    {
      // if there there more people to drop off
      if(!elevator.isEmpty())
      {
        elevator.updateGoalFloor();
        elevator.setState(Elevator::State::MOVE);
      }
      // else just stop and wait
      else
      {
        elevator.setState(Elevator::State::STOP);
      }
    }
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

  } // isEmpty
  
    
} // namespace hw6
