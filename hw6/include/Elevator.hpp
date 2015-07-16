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
    enum class State {MOVE, STOP, UNLOAD, LOAD};
    
    Elevator(const int timeToFloor = 10,
             const int startFloor = 0,
             const int stopTime = 2,
	     const int capacity = 8); // constructor
    
    void board(const Passenger& passenger); // let passenger on board
    bool hasRoom() const; // return if elevator has room
    bool isEmpty() const;
    Group exit(); // have passengers attempt to exit

    // getters
    int getAlignment() const;
    int getCurrentFloor() const;
    int getGoalFloor() const;
    int getRequestFloor() const;
    bool getGoalSet() const;
    bool getHandlingRequest() const;
    Group getOnBoard() const;
    State getState() const;
    Direction getMoveDirection() const;
    Direction getGoalDirection() const;
    int getMomentum() const;
    
    void move(); // move elevator one unit in it's current direction
    void slowDown(); // what to do when stopping
    void requestHandled(); // request handled
    
    // setters
    Elevator& setGoal(const int floor, const Direction& direction);
    Elevator& setRequest(const int floor, const Direction& direction);
    Elevator& setMovingDirection(const Direction& direction);
    Elevator& setState(const Elevator::State state);
    void updateGoalFloor(); // given current riders, finds closest desired floor
    
  private:
    int timeToFloor; // time it takes to move to an adjacent floor
    int stopTime; // time it takes to come to complete stop
    int capacity; // maximum number of passengers allowed on
    
    // these values can be thought of as the "state vector" of the elevator
    int currentFloor = 0; // current location of the elevator
    int goalFloor = 0; // where the elevator is trying to go
    int requestFloor = 0; // location of request
    int alignment = 0; // [0 - timeToFloor-1] 0 is elevator level with floor
    int momentum = 0; // [stopTime - 0] elevator momentum 0 is stopped
    // current direction of the elevator
    Direction movingDirection = Direction::NONE; 
    // desired direction to the goal floor
    Direction goalDirection = Direction::NONE;
    // desired direction of request
    Direction requestDirection = Direction::NONE;
    Group onBoard; // people that are on the elevator
    State state = State::STOP; // current state of the elevator
    bool goalSet = false; // does the elevator have a goal  
    bool handlingRequest = false; // is elevator handling a request

  }; // Elevator

  // convenience aliases
  typedef std::vector<Elevator> Elevators;
  
  std::ostream& operator<<(std::ostream& out, const Elevator& elevator);
  std::ostream& operator<<(std::ostream& out, const Elevator::State& state);
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
    getMoveDirection
        returns value of moveDirection data member
        
    Revision History
        14 July 2015 - Function created
  *///==========================================================================
  inline Direction Elevator::getMoveDirection() const
  {
    return this->movingDirection;
  }
  
  /*============================================================================
    getMomentum
        returns value of the momentum data member
        
    Revision History
        14 July 2015 - Function created
  *///==========================================================================
  inline int Elevator::getMomentum() const
  {
    return this->momentum;
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
    getRequestFloor
        returns value of requestFloor data member
        
    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  inline int Elevator::getRequestFloor() const
  {
    return this->requestFloor;
  }
  
  /*============================================================================
    getState
        returns value of state data member
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline Elevator::State Elevator::getState() const
  {
    return this->state;
  }
  
  /*============================================================================
    hasRequest
        returns true if the elevator is handling a request

    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  inline bool Elevator::getHandlingRequest() const
  {
    return this->handlingRequest;
  }
  
  /*============================================================================
    requestHandled
        alerts elevator that request has been handled
    
    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  inline void Elevator::requestHandled()
  {
    this->requestFloor = 0;
    this->requestDirection = Direction::NONE;
    this->handlingRequest = false;
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
    setState
        sets the value of the state data member
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline Elevator& Elevator::setState(const State newState) // desired state
  {
    this->state = newState;
    return *this;
  }
  
  /*============================================================================
    setRequest
        set the value of the requestFloor, requestDirection, and hasRequest data
        members
        
    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  //                                    requested floor
  inline Elevator& Elevator::setRequest(const int floor, 
                                        // requested direction
                                        const Direction& direction)
  {
    this->requestFloor = floor;
    this->requestDirection = direction;
    this->handlingRequest = true;
    
    return *this;
  }
  
} // Namespace hw6

#endif // ELEVATOR_HPP
