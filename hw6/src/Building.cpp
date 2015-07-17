// Building.cpp

#include <algorithm> // any_if

#include "Building.hpp"

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
  void Building::addPerson(const Passenger& person) // person to add to building
  {
    Direction goalDirection;
    
    // figure out if they are going up or down
    int numberDirection = person.getEndFloor() - person.getStartFloor();
    if (numberDirection > 0)
    {
      goalDirection = Direction::UP;
    }
    else if (numberDirection < 0)
    {
      goalDirection = Direction::DOWN;
    }
    
    // request an elevator and add it to the request mananger
    Request request = std::make_tuple(person.getStartTime(),
                                      person.getStartFloor(),
                                      goalDirection);

    
    this->requests.add(request);

    // have them state waiting in line
    this->floors[person.getStartFloor()].waitInLine(person);
   
  } // addPerson
  
  /*============================================================================
    advance
        advance the state of the building and all the components inside of it
        
    Revision History
        14 July 2015 - Function created
  *///==========================================================================
  void Building::advance(int time) // the current time
  {        
    // for each elevator, run it's state machine
    for (auto & elevator : this->elevators)
    { 
      
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
        this->handleLoading(elevator,
                            this->floors[elevator.getCurrentFloor()],
                            time);
        break;
        
      default:
        // this is a bad place to be
        break;
      } // switch
      
    } // for loop
    
  } // advance

  /*============================================================================
    handleLoading
        control out passengers get on the elevator
        
    Revision History 
        14 July 2015 - Function created
  *///==========================================================================
  void Building::handleLoading(Elevator& elevator, // current elevator
                               Floor& floor,
                               const int time) // current floor
  {
    // while there is room and people wanting to ride
    while (elevator.hasRoom() &&
           !floor.getLine(elevator.getGoalDirection()).empty())
    {
      Passenger boarding = floor.getNextInLine(elevator.getGoalDirection());
      elevator.board(boarding, time);
    }
    
    // if the queue is empty, clear any assiocated requests
    if (floor.getLine(elevator.getGoalDirection()).empty())
    {
      // key to match requests against
      Request clearMatch = std::make_tuple(0,
                                           floor.getNumber(),
                                           elevator.getGoalDirection());
      // clear requests that match
      this->requests.clear(clearMatch);
    }
    // if people are still left waiting, else resubmit the elevator request
    else
    {
      // get the next person in line
      Passenger person = floor.getLine(elevator.getGoalDirection()).front();
      Request resubmission = std::make_tuple(person.getStartTime(),
                                             floor.getNumber(),
                                             elevator.getGoalDirection());
      this->requests.update(resubmission);
    }

    // if the elevator is not empty, keep moving
    if (!elevator.isEmpty())
    {
      elevator.updateGoalFloor();
      elevator.setState(Elevator::State::MOVE);
    }
    // else stop
    else
    {
      elevator.setState(Elevator::State::STOP);
    }

  } // handleLoading
  
  /*============================================================================
    handleMoving
        control the movement of an elevator
        
    Revision History
        14 July 2015 - Function created
  *///==========================================================================
  void Building::handleMoving(Elevator& elevator, // current elevator
                              const Floor& floor) // current elevator
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
      // if elevator can pickup extra passengers
      else if (elevator.getGoalDirection() == elevator.getMoveDirection() &&
               elevator.hasRoom())
      {
        // if there are people who want to be picked up
        if (!floor.getLine(elevator.getMoveDirection()).empty())
        {
          shouldStop = true;
        }
      } // if should pick up or drop off people
    } // if on floor
    
    // begin stopping if necessary, else just keep moving
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
  void Building::handleStopped(Elevator& elevator, // current elevator
                               Floor& floor) // current floor
  {
    // if at requested floor or empty and no is onboard, clear request status
    if ((elevator.getCurrentFloor() == elevator.getRequestFloor()) || 
        (elevator.getCurrentFloor() == elevator.getGoalFloor() &&
         elevator.getMoveDirection() == Direction::NONE))
    {
      elevator.requestHandled();
    }
    
    // check if elevator goal should be updated
    if (elevator.getCurrentFloor() == elevator.getGoalFloor())
    {
      elevator.updateGoalFloor();
    }
    
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
      if (elevator.isEmpty() && !elevator.getHandlingRequest() &&
          this->requests.size() != 0)
      {
        int floorNumber;
        Direction direction;
        
        // unpack an elevator request
        std::tie(std::ignore, floorNumber, direction) = this->requests.front();
        this->requests.pop();
        
        elevator.takeRequest(floorNumber, direction);
        elevator.setGoal(floorNumber, direction);        
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
    for (auto & passenger : leaving)
    {
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
