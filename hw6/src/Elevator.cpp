// Elevator.cpp

#include <algorithm> // for_each, swap

#include "Elevator.hpp"

namespace hw6
{
  /*============================================================================
    Elevator
        Default constructor for the class
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  Elevator::Elevator(const int id, // id number of the elevator
                     const int timeToFloor, // time to move between floor
                     const int minFloorNumber, // bottom floor of building
                     const int maxFloorNumber, // top floor of building
                     const int startFloor, // starting location of the elevator
                     const int stopTime, // time to stop completely
                     const int capacity): // how many people elevator can hold
    id(id),
    timeToFloor(timeToFloor),
    minFloorNumber(minFloorNumber),
    maxFloorNumber(maxFloorNumber),
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
      for (iter = this->onBoard.end()-1; iter != this->onBoard.begin()-1; --iter)
      {
        // if person wants to get off on this floor
        if (iter->getEndFloor() == this->currentFloor)
        {
          // since onBoard isn't sorted, additional performance is gained
          // via swap, pop_back, and leveraging move operations
          leaving.push_back(*iter);
          std::swap(*iter, this->onBoard.back());
          this->onBoard.pop_back();
        }
      }
    } // if could unload
    
    return leaving;
  } // exit
 
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
    // if moving up, continue up
    if (this->movingDirection == Direction::UP)
    {
      ++this->alignment;
      // if at next floor
      if (this->alignment >= this->timeToFloor)
      {
        ++this->currentFloor;
        this->alignment = 0;
      }      
    }
    // if moving down, confinue down
    else if (this->movingDirection == Direction::DOWN)
    {
      --this->alignment;
      // if at next floor
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
  std::ostream& operator<<(std::ostream& out, // desired output stream
                           const Elevator& elevator) // object to display
  {
    out << std::boolalpha;
    
    out << "Elevator " << elevator.getID() << "\n";
    
    out << "state: " << elevator.getState() << ", "
        << "floor: " << elevator.getCurrentFloor() << ", "
        << "align: " << elevator.getAlignment() << ", "
        << "speed: " << elevator.getMomentum() << ", "
        << "isEmpty: " << elevator.isEmpty()  << ", "
        << "move dir: " << elevator.getMoveDirection() << "\n";
    
    out << "handlingRequest: " << elevator.getHandlingRequest() << ", "
        << "Goal floor: " << elevator.getGoalFloor() << ", "
        << "Goal dir: " << elevator.getGoalDirection() << ", "
        << "Request floor: " << elevator.getRequestFloor() << "\n";
      
    out << std::noboolalpha;
    
    out << "On board" << "\n";
    for (auto & person : elevator.getOnBoard())
    {
      out << person << " ";
    }
    
    return out;
  } // operator<<
  
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
    int newFloorNumber = this->currentFloor;
    
    // if going up, find the minimum floor
    if (this->goalDirection == Direction::UP)
    {
      int minFloor = this->maxFloorNumber;
      
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
    
    // if going down, find the maximum floor
    else if (this->goalDirection == Direction::DOWN)
    {      
      int maxFloor = this->minFloorNumber;
      
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
