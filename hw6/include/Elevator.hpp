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

#include <array>

#include "Passenger.hpp"

namespace hw6
{
  
  typedef std::array<Passenger, 8> Occupents;
  
  class Elevator
  {
  public:
    enum State {MOVE, STOP};
    enum Direction {NONE, UP, DOWN};

    Elevator(const int startFloor = 0,
             const int timeToFloor = 8,
             const int stopTime = 2,
             const State state = STOP,
             const Direction direction = NONE);

  private:
    int currentFloor; // current location of the elevator
    Occupents onBoard; // people that are on the elevator
    int timeToFloor; // time it takes to move to an adjacent floor
    int stopTime; // time it takes to come to complete stop
    State state; // current state of the elevator
    Direction direction; // current direction of the ele
    
  }; // Elevator

} // namespace hw6

#endif // ELEVATOR_HPP
