/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 8 July, 2015
  
  Revision History
      8 July, 2015 - class created
  
  Class Name: Elevator
  
  Intent: Simulate the movement of an elevator, and passengers on and off 
  
  Description: 

*///============================================================================

#ifndef ELEVATOR_HPP
#define ELEVATOR_HPP

#include <vector>
#include <queue>

#include "Passenger.hpp"

namespace hw6
{   
  class Elevator
  {  
  public:
    enum class State {MOVE, STOP};
    
    Elevator(const int timeToFloor = 10,
             const int startFloor = 0,
             const int stopTime = 2,
	     const int capacity = 8,
             State state = State::STOP,
             Direction direction = Direction::NONE); // constructor
    
    void board(const Passenger& passenger); // let passenger on board
    bool hasRoom() const; // return if elevator has room
    bool isEmpty() const;
    Group exit(); // have passengers attempt to exit

    // getters
    int getAlignment() const;
    int getCurrentFloor() const;
    int getGoalFloor() const;
    bool getGoalSet() const;
    Group getOnBoard() const;
    State getState() const;
    Direction getMovingDirection() const;
    Direction getGoalDirection() const;
    
    void move(); // move elevator one unit in it's current direction
    void slowDown(); // what to do when stopping
    
    // setters
    void setGoalFloor(const int floor);
    void setGoalDirection(const Direction& direction);
    void setMovingDirection(const Direction& direction);
    
    void updateGoalFloor(); // given current riders, finds closest desired floor
    
  private:
    int timeToFloor; // time it takes to move to an adjacent floor
    int stopTime; // time it takes to come to complete stop
    int capacity; // maximum number of passengers allowed on
    
    // location is broken up into two parts the floor and
    // how much the elevator is aligned with the floor, 0 is aligned
    int currentFloor; // current location of the elevator
    int goalFloor; // where the elevator is trying to go
    int alignment = 0; // [0 - timeToFloor-1]
    int stopProgress = 0; // [0 - stopTime-1]
    
    Direction goalDirection; // desired direction from the goal floor
    Direction movingDirection; // current direction of the elevator
    bool goalSet; // does the elevator have a goal  
    Group onBoard; // people that are on the elevator    
    State state; // current state of the elevator

    
    
  }; // Elevator

  // convenience aliases
  typedef std::vector<Elevator> Elevators;
  
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
  }

  /*============================================================================
    getAlignment
        returns value of alignment data member
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline int Elevator::getAlignment() const
  {
    return this->alignment;
  }

  /*============================================================================
    getCurrentFloor
        returns value of currentFloor data member
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline int Elevator::getCurrentFloor() const
  {
    return this->currentFloor;
  }
  
  /*============================================================================
    getGoalDirection
        returns value of goalDirection data member
        
    Revision History
        14 July 2015 - Function created
  *///==========================================================================
  inline Direction Elevator::getGoalDirection() const
  {
    return this->goalDirection;
  }
  
  /*============================================================================
    getGoalFloor
        returns value of goalFloor data member
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline int Elevator::getGoalFloor() const
  {
    return this->goalFloor;
  }
  
  /*============================================================================
    getGoalSet
        returns value of goalSet data member
        
    Revision History
        14 July 2015 - Function created
  *///==========================================================================
  inline bool Elevator::getGoalSet() const
  {
    return this->goalSet;
  }
  
  /*============================================================================
    getMovingDirection
        returns value of goalDirection data member
        
    Revision History
        14 July 2015 - Function created
  *///==========================================================================
  inline Direction Elevator::getMovingDirection() const
  {
    return this->movingDirection;
  }
  
  /*============================================================================
    getOnBoard
        returns value of onBoard data member
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline Group Elevator::getOnBoard() const
  {
    return this->onBoard;
  }
  
  /*============================================================================
    getState
        returns value of currentFloor data member
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline Elevator::State Elevator::getState() const
  {
    return this->state;
  }
  
  /*============================================================================
    hasRoom
        returns true if the elevator has room

    Revision History
        9 July 2015 - Function created
  *///==========================================================================
  inline bool Elevator::hasRoom() const
  {
    return this->onBoard.size() < this->capacity;
  }
  
  /*============================================================================
    isEmpty
        returns true if the elevator has no passengers
        
    Revision History
        14 July 2015 - Function created
  *///==========================================================================
  inline bool Elevator::isEmpty() const
  {
    return this->onBoard.size() == 0;
  }
  
  /*============================================================================
    setGoalDirection
        sets the value of the goalDirection data member
        
    Revision History
        14 July 2015 - Function created
  *///==========================================================================
  //                                       new goal direction
  inline void Elevator::setGoalDirection(const Direction& direction)
  {
    this->goalDirection = direction;
  }
  
} // Namespace hw6

#endif // ELEVATOR_HPP
