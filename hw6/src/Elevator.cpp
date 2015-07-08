// Elevator.cpp

#include "Elevator.hpp"

namespace hw6
{
  /*============================================================================
    Elevator
        Default constructor for the class
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  Elevator::Elevator(const int startFloor, // starting location of the elevator
                     const int timeToFloor, // time to move between floor
                     const int stopTime, // time to stop completely
                     const State state, // current state of elevator
                     const Direction direction): // current direction elevator
    currentFloor(startFloor),
    timeToFloor(timeToFloor),
    stopTime(stopTime),
    state(state),
    direction(direction)
  { 
  }
}
