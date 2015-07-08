#include <iostream>

#include "TimelineParser.hpp"
#include "Floor.hpp"
#include "Elevator.hpp"

int main(int argc, char** argv)
{
  hw6::TimelineParser parser;
  hw6::Line movementHistory;
  
  movementHistory = parser.parse("../csv/HW6-Elevators.csv");
  
  return 0;
}
