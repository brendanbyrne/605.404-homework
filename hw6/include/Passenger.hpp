/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 7 July, 2015
  
  Revision History
      7 July, 2015 - class created
  
  Class Name: Passenger
  
  Intent: Simulate a person wanting to, riding on, and leaving an elevator
  
  Description: Not much more of a description, classes main job is to just hold
               on to the data

*///============================================================================

#ifndef PASSENGER_HPP
#define PASSENGER_HPP

#include <ostream>
#include <queue>
#include <vector>

namespace hw6
{
  // both Passengers and Elevators share a sense of direction
  enum class Direction {NONE, UP, DOWN};

  class Passenger
  {    
  public:
    Passenger(int arrivalTime = 0, 
              int goalTime = 0,
              int arrivalFloor = 0,
              int goalFloor = 0); // constructor
    
    // getters
    int getBoardTime() const;
    int getEndFloor() const;
    int getEndTime() const;
    int getStartFloor() const;
    int getStartTime() const;
    
    // setters
    Passenger& setBoardTime(const int time);
    Passenger& setEndFloor(const int floorNumber);
    Passenger& setEndTime(const int time);
    Passenger& setStartFloor(const int floorNumber);
    Passenger& setStartTime(const int time);
    
  private:
    int startTime; // time when passenger arrives at the starting floor
    int boardTime; // time when passenger boards the elevator
    int endTime; // time when passenger arrives at the ending floor
    int startFloor; // floor number that passenger start on
    int endFloor; // floor number that passenger is trying to get to 
    
  }; // class Passenger
  
  // convenience typedefs for working with collections of class
  typedef std::queue<Passenger> Line; // an ordered group of people
  typedef std::vector<Passenger> Group; // a disordered group of people

  // insertion overload 
  std::ostream& operator<<(std::ostream& out, const Passenger& passenger);
  std::ostream& operator<<(std::ostream& out, const Direction& direction);
  
  /*============================================================================
    getBoardTime
        return value of the boardTime data member

    Revision History
        7 July 2015 - Function created
  *///==========================================================================
  inline int Passenger::getBoardTime() const
  {
    return this->boardTime;
  }

  /*============================================================================
    getEndFloor
        return value of the endFloor data member

    Revision History
        7 July 2015 - Function created
  *///==========================================================================
  inline int Passenger::getEndFloor() const
  {
    return this->endFloor;
  }
  
  /*============================================================================
    getEndTime
        return value of the endTime data member

    Revision History
        7 July 2015 - Function created
  *///==========================================================================
  inline int Passenger::getEndTime() const
  {
    return this->endTime;
  }
  
  /*============================================================================
    getStartFloor
        return value of the startFloor data member

    Revision History
        7 July 2015 - Function created
  *///==========================================================================
  inline int Passenger::getStartFloor() const
  {
    return this->startFloor;
  }
  
  /*============================================================================
    getStartTime
        return value of the startTime data member

    Revision History
        7 July 2015 - Function created
  *///==========================================================================
  inline int Passenger::getStartTime() const
  {
    return this->startTime;
  }

  /*============================================================================
    setBoardTime
        set the value of the boardTime data member

    Revision History
        7 July 2015 - Function created
  *///==========================================================================
  inline Passenger& Passenger::setBoardTime(const int time) // finished world time
  {
    this->boardTime = time;
    return *this;
  }

  /*============================================================================
    setEndFloor
        set the value of the endFloor data member

    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline Passenger& Passenger::setEndFloor(const int floor) // where to go
  {
    this->endFloor = floor;
    return *this;
  }

  /*============================================================================
    setEndTime
        set the value of the endTime data member

    Revision History
        7 July 2015 - Function created
  *///==========================================================================
  inline Passenger& Passenger::setEndTime(const int time) // finished world time
  {
    this->endTime = time;
    return *this;
  }
  
  /*============================================================================
    setStartFloor
        set the value of the startFloor data member

    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline Passenger& Passenger::setStartFloor(const int floor) // where to start
  {
    this->startFloor = floor;
    return *this;
  }
  
  /*============================================================================
    setStartTime
        set the value of the startTime data member

    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline Passenger& Passenger::setStartTime(const int time) // when to start
  {
    this->startTime = time;
    return *this;
  }
  
} // namespace hw6

#endif // PASSENGER_HPP
