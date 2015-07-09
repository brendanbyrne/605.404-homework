#include <iostream>

#include "TimelineParser.hpp"
#include "Simulator.hpp"

int main(int argc, char** argv)
{
  // parse csv file for testing configuration
  hw6::TimelineParser parser;
  hw6::Line movementHistory;  
  movementHistory = parser.parse("../csv/HW6-Elevators.csv");
  
  // create the building
  hw6::Building building;
  for (int i = 0; i < 100; ++i)
  {
    building.push_back(hw6::Floor(i));
  }
  
  // Set up the elevators
  hw6::Elevators elevators;
  for (int i = 0; i < 4; ++i)
  {
    elevators.push_back(hw6::Elevator(0, 10));
  }
  
  // create and run simulation for the slower speed
  hw6::Simulator simSlowSpeed = hw6::Simulator(movementHistory,
                                               building,
                                               elevators);
  double slowTime = simSlowSpeed.start();
  
  elevators.clear();
  for (int i = 0; i < 4; ++i)
  {
    elevators.push_back(hw6::Elevator(0, 5));
  }
  
  // create and run simulation for the faster speed
  hw6::Simulator simFastSpeed = hw6::Simulator(movementHistory,
                                               building,
                                               elevators);
  double fastTime = simFastSpeed.start();
  
  return 0;
}
