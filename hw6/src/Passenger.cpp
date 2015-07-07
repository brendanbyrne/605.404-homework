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
                       int goalTime,
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
        insertion operator overload

    Revision History
        7 July 2015 - Function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, Passenger passenger)
  {
    out << passenger.getStartTime();
    return out;
  }
} // namespace hw6
