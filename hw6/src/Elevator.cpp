// Elevator.cpp

#include <algorithm> // for_each

#include "Elevator.hpp"

namespace hw6
{
  /*============================================================================
    Elevator
        Default constructor for the class
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  Elevator::Elevator(const int timeToFloor, // time to move between floor
                     const int startFloor, // starting location of the elevator
                     const int stopTime, // time to stop completely
		     const int capacity, // how many people the elevator can hold
                     const State state, // current state of elevator
                     const Direction direction): // current direction elevator
    currentFloor(startFloor),
    currentAlignment(0),
    timeToFloor(timeToFloor),
    stopTime(stopTime),
    stopProgress(0),
    capacity(capacity),
    state(state),
    direction(direction)
  {
  }

  /*============================================================================
    board
        add passenger to elevator
        
    Revision History
        9 July 2015 - Function created
  *///==========================================================================
  //                          passenger trying to board
  inline void Elevator::board(const Passenger& passenger)
  {
    onBoard.push_back(passenger);
    this->updateGoalFloor();
  }
  
  /*============================================================================
    exit
        passengers exit the elevator
        
    Revision History
        9 July 2015 - Function created
  *///==========================================================================
  Group Elevator::exit()
  {
    Group leaving;
    
    if (this->state == State::STOPPED &&
	this->currentAlignment == 0)
    {
      Group::iterator iter;
      // for all occupents on board
      for (iter = this->onBoard.begin(); iter != this->onBoard.end(); ++iter)
      {
        if (iter->getEndFloor() == this->currentFloor)
        {
          leaving.push_back(*iter);
          this->onBoard.erase(iter);
        }
      }
    }
    
    return leaving;
  }
 
  /*============================================================================
    handleMoving
        move the elevator until it reaches the goalFloor
        
    Revision History
        11 July 2015 - Function created
  *///==========================================================================
  void Elevator::handleMoving()
  {
    // if aligned with currentFloor and has
    if (currentAlignment == 0 &&
	this->currentFloor == this->goalFloor)
    {
      this->state = State::STOPPING;
    }
    else
    {
      move();	
    }
  }

  /*============================================================================
    handleStopping
        slows the eleveator to a stop
        
    Revision History
        11 July 2015 - Function created
  *///==========================================================================
  void Elevator::handleStopping()
  {
    ++this->stopProgress;
    if (this->stopProgress >= this->stopTime)
    {
      this->state = State::STOPPED;
      this->stopProgress = 0;
    }
  }
  
  /*============================================================================
    handleStopped
        stops the elevator and clears it's direction
        
    Revision History
        11 July 2015 - Function created
  *///==========================================================================
  void Elevator::handleStopped()
  {
    // // Does anything need to be done while stopped?
    // if (this->direction == UP ||
    //     this->direction == DOWN)
    // {
    //   this->direction = NONE;
    // }
  }

  /*============================================================================
    move
        moves the elevator one units worth of distance in it's current direction
        
    Revision History
        11 July 2015 - Function created
  *///==========================================================================
  void Elevator::move()
  {
    if (this->direction == Direction::UP)
    {
      ++this->currentAlignment;
      if (this->currentAlignment >= this->timeToFloor)
      {
	++this->currentFloor;
	this->currentAlignment = 0;
      }      
    }
    else if (this->direction == Direction::DOWN)
    {
      --this->currentAlignment;
      if (this->currentAlignment < 0)
      {
	--this->currentFloor;
	this->currentAlignment = this->timeToFloor - 1;
      }
    }
  }

  /*============================================================================
    stateMachine
        general enterace into the elevator state machine
        
    Revision History
        11 July 2015 - Function created
  *///==========================================================================
  void Elevator::stateMachine()
  {
    switch (this->state)
    {
    case State::MOVING:
      handleMoving();
      break;
    
    case State::STOPPING:
      handleStopping();
      break;
      
    case State::STOPPED:
      handleStopped();
      break;
      
    default:
      break;
      // should never end up here
    }
  }
  
  /*============================================================================
    updateGoalFloor
        // find the closest desired floor, set it as the new goalFloor
        
    Revision History
        11 July 2015 - Function created
  *///==========================================================================
  void Elevator::updateGoalFloor()
  {
    // find the minimum floor
    if (this->direction == Direction::UP)
    {
      int minFloor = this->goalFloor;
      
      std::for_each(this->onBoard.begin(), this->onBoard.end(),
		    [&minFloor](const Passenger& person)
		    {
		      if (person.getEndFloor() < minFloor)
		      {
			minFloor = person.getEndFloor();
		      }
		    });
      
      this->goalFloor = minFloor;
    }
    
    // find the maximum floor
    else if (this->direction == Direction::DOWN)
    {
      int maxFloor = this->goalFloor;
      
      std::for_each(this->onBoard.begin(), this->onBoard.end(),
		    [&maxFloor](const Passenger& person)
		    {
		      if (person.getEndFloor() > maxFloor)
		      {
			maxFloor = person.getEndFloor();
		      }
		    });
      
      this->goalFloor = maxFloor;
    }
  }
}
