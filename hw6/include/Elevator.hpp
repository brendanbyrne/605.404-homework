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

#include "Passenger.hpp"

namespace hw6
{ 
  class Elevator
  {  
  public:
    enum State {MOVING, STOPPING, STOPPED};
    enum Direction {NONE, UP, DOWN};
    
    Elevator(const int timeToFloor = 10,
             const int startFloor = 0,
             const int stopTime = 2,
	     const int capacity = 8,
             State state = STOPPED,
             Direction direction = NONE); // constructor
    
    void board(const Passenger& passenger); // let passenger on board
    bool hasRoom() const; // return if elevator has room
    Group exit(); // have passengers attempt to exit

    // getters
    Group getOnBoard() const;
    
    void stateMachine();

  private:
    int timeToFloor; // time it takes to move to an adjacent floor
    int stopTime; // time it takes to come to complete stop
    int capacity; // maximum number of passengers allowed on
    
    // location is broken up into two parts the floor and
    // how much the elevator is aligned with the floor, 0 is aligned
    int currentFloor; // current location of the elevator
    int currentAlignment; // [0 - timeToFloor-1]
    int goalFloor; // where the elevator is trying to go
    Group onBoard; // people that are on the elevator    
    int stopProgress; // [0 - stopTime-1]
    State state; // current state of the elevator
    Direction direction; // current direction of the elevator
    
    void handleMoving(); // what to do when the state is MOVING
    void handleStopping(); // what to do when the state is STOPPING
    void handleStopped(); // what to do when the state is STOPPED
    void move(); // move elevator one unit in it's current direction
    void updateGoalFloor(); // given current riders, finds closest desired floor
    
  }; // Elevator

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
    getOnBoard
        returns value of onBoard data member
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline Group Elevator::getOnBoard() const
  {
    return this->onBoard;
  }
  
} // Namespace hw6

#endif // ELEVATOR_HPP
