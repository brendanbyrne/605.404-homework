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
  Elevator::Elevator(const int timeToFloor, // time to move between floor
                     const int startFloor, // starting location of the elevator
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
  
  /*============================================================================
    exit
        passengers exit the elevator
        
    Revision History
        9 July 2015 - Function created
  *///==========================================================================
  Occupents Elevator::exit()
  {
    Occupents leaving;
    
    if (this->state == STOPPED)
    {
      Occupents::iterator iter;
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
  
}
