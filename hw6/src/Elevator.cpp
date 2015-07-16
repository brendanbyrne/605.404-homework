// Elevator.cpp

#include <algorithm> // for_each

#include "Elevator.hpp"

#include <iostream>

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
		     const int capacity): // how many people elevator can hold
    timeToFloor(timeToFloor),
    currentFloor(startFloor),
    stopTime(stopTime),
    momentum(stopTime),
    capacity(capacity)
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
    
    if (this->state == State::UNLOAD &&
	this->alignment == 0)
    {
      Group::iterator iter;
      // for all occupents on board
      for (iter = this->onBoard.begin(); iter != this->onBoard.end(); ++iter)
      {
        std::cout << "foo: " << iter->getEndFloor() << " " << this->currentFloor << std::endl;
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
    // have elevator lose momentum
    --this->momentum;
    // if it is stopped
    if (this->momentum <= 0)
    {
      this->state = State::STOP;
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
    operator<<
        insertion operator overload for an elevator

    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, const Elevator& e)
  {
    out << std::boolalpha;
    
    out << "Elevator" << "\n";
    
    out << "state: " << e.getState() << ", "
        << "floor: " << e.getCurrentFloor() << ", "
        << "align: " << e.getAlignment() << ", "
        << "speed: " << e.getMomentum() << ", "
        << "isEmpty: " << e.isEmpty()  << ", "
        << "move dir: " << e.getMoveDirection() << "\n";
    
    out << "hasGoal: " << std::boolalpha << e.getGoalSet() << ", "
        << "Goal floor: " << e.getGoalFloor() << ", "
        << "Goal dir: " << e.getGoalDirection() << "\n";
      
    out << std::noboolalpha;
    
    out << "On board" << "\n";
    for (auto & person : e.getOnBoard())
    {
      out << person << " ";
    }
    return out;
  }
  
  /*============================================================================
    operator<<
        insertion operator overload for a state

    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, const Elevator::State& state)
  {
    switch (state)
    {
    case Elevator::State::MOVE:
      out << "Moving";
      break;
      
    case Elevator::State::STOP:
      out << "Stopped";
      break;
      
    case Elevator::State::UNLOAD:
      out << "Unloading";
      break;
      
    case Elevator::State::LOAD:
      out << "Loading";
      break;
      
    default:
      out << "error";
    }
    return out;
  }
  /*============================================================================
    setGoal
        sets the value of the goalFloor data member and propagates the impact of
        this change to the goalSet and movingDirection data members
        
    Revision History
        14 July 2015 - Function created
  *///==========================================================================
  Elevator& Elevator::setGoal(const int floor, // desired floor
                              const Direction& direction) //desired direction
  {
    this->goalFloor = floor;
    this->goalDirection = direction;
    this->goalSet = true;
    this->state = State::MOVE;
    this->momentum = this->stopTime;
    
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
    
    return *this;
  }
    
  /*============================================================================
    updateGoalFloor
        find the closest desired floor, set it as the new goalFloor
        
    Revision History
        11 July 2015 - Function created
  *///==========================================================================
  void Elevator::updateGoalFloor()
  {
    int newFloorNumber;
    // find the minimum floor
    if (this->goalDirection == Direction::UP)
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
      
      newFloorNumber = minFloor;
    }
    
    // find the maximum floor
    else if (this->goalDirection == Direction::DOWN)
    {      
      int maxFloor = 0;
      
      std::for_each(this->onBoard.begin(), this->onBoard.end(),
		    [&maxFloor](const Passenger& person)
		    {
		      if (person.getEndFloor() > maxFloor)
		      {
			maxFloor = person.getEndFloor();
		      }
                      
		    });
      
      
      newFloorNumber = maxFloor;
    }
    
    this->setGoal(newFloorNumber, this->goalDirection);
  }
  
} // namespace hw6
