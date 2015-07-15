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
    timeToFloor(timeToFloor),
    stopTime(stopTime),
    capacity(capacity),
    state(state),
    movingDirection(direction)
  {
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
    
    if (this->state == State::STOP &&
	this->alignment == 0)
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
    slowDown
        slows the eleveator to a stop
        
    Revision History
        11 July 2015 - Function created
  *///==========================================================================
  void Elevator::slowDown()
  {
    ++this->stopProgress;
    if (this->stopProgress >= this->stopTime)
    {
      this->state = State::STOP;
      this->stopProgress = 0;
    }
  }
  
  /*============================================================================
    move
        moves the elevator one units worth of distance in it's current direction
        
    Revision History
        11 July 2015 - Function created
  *///==========================================================================
  void Elevator::move()
  {
    if (this->movingDirection == Direction::UP)
    {
      ++this->alignment;
      if (this->alignment >= this->timeToFloor)
      {
	++this->currentFloor;
	this->alignment = 0;
      }      
    }
    else if (this->movingDirection == Direction::DOWN)
    {
      --this->alignment;
      if (this->alignment < 0)
      {
	--this->currentFloor;
	this->alignment = this->timeToFloor - 1;
      }
    }
  }
  
  /*============================================================================
    setGoalFloor
        sets the value of the goalFloor data member and propagates the impact of
        this change to the goalSet and movingDirection data members
        
    Revision History
        14 July 2015 - Function created
  *///==========================================================================
  void Elevator::setGoalFloor(const int floor) // new goalFloor value
  {
    this->goalFloor = floor;
    this->goalSet = true;
    
    // if floor is above
    if (this->goalFloor > this->currentFloor)
    {
      this->movingDirection = Direction::UP;
    }
    // if floor is below
    else if (this->goalFloor < this->currentFloor)
    {
      this->movingDirection = Direction::DOWN;
    }
    // if same floor, check the alignment
    else
    {
      // if not aligned move down
      if (this->alignment > 0)
      {
        this->movingDirection = Direction::DOWN;
      }
      // if aligned don't move
      else
      {
        this->movingDirection = Direction::NONE;
      }
    }
  }
    
  /*============================================================================
    updateGoalFloor
        find the closest desired floor, set it as the new goalFloor
        
    Revision History
        11 July 2015 - Function created
  *///==========================================================================
  void Elevator::updateGoalFloor()
  {
    // if no one is riding
    if (this->isEmpty())
    {
      this->goalFloor = 0;
      this->goalSet = false;
    }
    // find the minimum floor
    else if (this->goalDirection == Direction::UP)
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
    else if (this->goalDirection == Direction::DOWN)
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
