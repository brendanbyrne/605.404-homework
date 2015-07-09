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
  // contains the riders of the elevator
  typedef std::vector<Passenger> Occupents;
  
  class Elevator
  {  
  public:
    enum State {MOVING, STOPPING, STOPPED};
    enum Direction {NONE, UP, DOWN};
    
    Elevator(const int timeToFloor = 8,
             const int startFloor = 0,
             const int stopTime = 2,
             const State state = STOPPED,
             const Direction direction = NONE);
    
    void board(const Passenger& passenger); // let passenger to board    
    Occupents exit(); // have passengers attempt to exit
    
    // getters
    Occupents getOnBoard() const;
    
  private:
    int currentFloor; // current location of the elevator
    Occupents onBoard; // people that are on the elevator
    int timeToFloor; // time it takes to move to an adjacent floor
    int stopTime; // time it takes to come to complete stop
    State state; // current state of the elevator
    Direction direction; // current direction of the ele
    
  }; // Elevator
  
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
    getOnBoard
        returns value of onBoard data member
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline Occupents Elevator::getOnBoard() const
  {
    return this->onBoard;
  }
  
} // namespace hw6

#endif // ELEVATOR_HPP
