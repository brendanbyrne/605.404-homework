// main.cpp

#include <iostream>

#include "TimelineParser.hpp"
#include "Simulator.hpp"


#include "Requests.hpp"

int main(int argc, char** argv)
{  
  // parse csv file for testing configuration
  hw6::TimelineParser parser;
  hw6::Line movementHistory;  
  movementHistory = parser.parse("../csv/HW6-Elevators.csv");
    
  int numberOfElevators = 4;

  // create the building
  hw6::Floors slowFloors;
  for (int i = 0; i < 100; ++i)
  {
    slowFloors.push_back(hw6::Floor(i));
  }
  
  // Set up the elevators
  hw6::Elevators slowElevators;
  for (int i = 0; i < numberOfElevators; ++i)
  {
    slowElevators.push_back(hw6::Elevator(i));
  }
  
  hw6::Building slowBuilding(slowFloors, slowElevators);
  
  // create and run simulation for the slower speed
  hw6::Simulator simSlowSpeed = hw6::Simulator(movementHistory,
					       slowBuilding);
  
  simSlowSpeed.start();
  std::cout << "average wait time: " << simSlowSpeed.calculateResults() << std::endl;


  /*

  // create the building
  hw6::Floors fastFloors;
  for (int i = 0; i < 100; ++i)
  {
    fastFloors.push_back(hw6::Floor(i));
  }
  
  // Set up the elevators
  hw6::Elevators fastElevators;
  for (int i = 0; i < numberOfElevators; ++i)
  {
    fastElevators.push_back(hw6::Elevator(i,5));
  }
  
  hw6::Building fastBuilding(fastFloors, fastElevators);
  
  // create and run simulation for the slower speed
  hw6::Simulator simFastSpeed = hw6::Simulator(movementHistory,
					       fastBuilding);
  
  simFastSpeed.start();
  std::cout << "average wait time: " << simFastSpeed.calculateResults() << std::endl;
  
  */

  return 0;
}
