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
  // pulled outside because passenger and elevators have an up/down value
  enum class Direction {NONE, UP, DOWN};
  
  class Elevator
  {  
  public:
    enum class State {MOVING, STOPPING, STOPPED};
    
    Elevator(const int timeToFloor = 10,
             const int startFloor = 0,
             const int stopTime = 2,
	     const int capacity = 8,
             State state = State::STOPPED,
             Direction direction = Direction::NONE); // constructor
    
    void board(const Passenger& passenger); // let passenger on board
    bool hasRoom() const; // return if elevator has room
    bool isEmpty() const;
    Group exit(); // have passengers attempt to exit

    // getters
    int getCurrentFloor() const;
    int getGoalFloor() const;
    bool getGoalSet() const;
    Group getOnBoard() const;
    State getState() const;
    
    // setters
    void setGoalFloor(const int floor);
    void setGoalDirection(const Direction& direction);

    void stateMachine();

  private:
    int timeToFloor; // time it takes to move to an adjacent floor
    int stopTime; // time it takes to come to complete stop
    int capacity; // maximum number of passengers allowed on
    
    // location is broken up into two parts the floor and
    // how much the elevator is aligned with the floor, 0 is aligned
    int currentFloor; // current location of the elevator
    int currentAlignment = 0; // [0 - timeToFloor-1]
    int stopProgress = 0; // [0 - stopTime-1]
    int goalFloor; // where the elevator is trying to go
    Direction goalDirection; // desired direction from the goal floor
    bool goalSet; // does the elevator have a goal  
    Group onBoard; // people that are on the elevator    
    State state; // current state of the elevator
    Direction movingDirection; // current direction of the elevator
    

    void handleMoving(); // what to do when the state is MOVING
    void handleStopping(); // what to do when the state is STOPPING
    void handleStopped(); // what to do when the state is STOPPED
    void move(); // move elevator one unit in it's current direction
    void updateGoalFloor(); // given current riders, finds closest desired floor
    
  }; // Elevator

  // convenience aliases
  typedef std::vector<Elevator> Elevators;
  
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
    getGoalFloor
        returns value of goalFloor data member
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline int Elevator::getGoalFloor() const
  {
    return this->goalFloor;
  }
  
  inline bool Elevator::getGoalSet() const
  {
    return this->goalSet;
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
  
  inline bool Elevator::isEmpty() const
  {
    return this->onBoard.size() == 0;
  }

  inline void Elevator::setGoalFloor(const int floor)
  {
    this->goalFloor = floor;
    this->goalSet = true;
  }

  inline void Elevator::setGoalDirection(const Direction& direction)
  {
    
  }

} // Namespace hw6

#endif // ELEVATOR_HPP
