// Passenger.cpp

#include "Passenger.hpp"

namespace hw6
{
  /*============================================================================
    Passenger
        constructor for the class

    Revision History
        7 July 2015 - Function created
  *///==========================================================================
  Passenger::Passenger(int arrivalTime, // time when passenger arrives at floor
                       int goalTime,  // usually zero, here for completion
                       int arrivalFloor, // starting floor for passenger
                       int goalFloor): // floor passenger wants to go to
    startTime(arrivalTime),
    endTime(goalTime),
    startFloor(arrivalFloor),
    endFloor(goalFloor)
  {
  }
  
  /*============================================================================
    operator<<
        insertion operator overload for a passenger

    Revision History
        7 July 2015 - Function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, // desired output stream
                           const Passenger& passenger) // passenger to print
  {
    out << passenger.getEndFloor();
    return out;
  }

  /*============================================================================
    operator<<
        insertion operator overload for a direction

    Revision History
        7 July 2015 - Function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, // desired output stream
                           const Direction& direction) // direction to print
  {
    switch (direction)
    {
    case Direction::UP:
      out << "Up";
      break;
      
    case Direction::DOWN:
      out << "Down";
      break;
      
    case Direction::NONE:
      out << "None";
      break;
      
    default:
      out << "error";
    }
    
    return out;
  }
} // namespace hw6
