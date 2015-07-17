// main.cpp

#include <iostream>

#include "TimelineParser.hpp"
#include "Simulator.hpp"

int main(int argc, char** argv)
{  

  // parse csv file for testing configuration
  hw6::TimelineParser parser;
  hw6::Line movementHistory;  
  movementHistory = parser.parse("../csv/HW6-Elevators.csv");
  
  int numberOfElevators = 4;

  // create the building
  hw6::Floors slowFloors;
  for (int id = 0; id < 100; ++id)
  {
    slowFloors.push_back(hw6::Floor(id));
  }
  
  // Set up the elevators
  hw6::Elevators slowElevators;
  for (int id = 0; id < numberOfElevators; ++id)
  {
    slowElevators.push_back(hw6::Elevator(id, 10, 0, slowFloors.size()-1));
  }
  
  hw6::Building slowBuilding(slowFloors, slowElevators);
  
  // create and run simulation for the slower speed
  hw6::Simulator simSlowSpeed = hw6::Simulator(movementHistory,
                                               slowBuilding);
  
  simSlowSpeed.start();
  hw6::SimulationOutput slowResults = simSlowSpeed.calculateResults();
  
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
    fastElevators.push_back(hw6::Elevator(i,5, 0, fastFloors.size()-1));
  }
  
  hw6::Building fastBuilding(fastFloors, fastElevators);
  
  // create and run simulation for the slower speed
  hw6::Simulator simFastSpeed = hw6::Simulator(movementHistory,
                                               fastBuilding);
  
  simFastSpeed.start();
  hw6::SimulationOutput fastResults = simFastSpeed.calculateResults();

  
  // output the results
  std::cout << "For the slow run:" << std::endl;
  std::cout << "average wait time: " << slowResults.waitTime << std::endl;
  std::cout << "average travel time: " << slowResults.travelTime << std::endl;

  std::cout << "For the fast run:" << std::endl;
  std::cout << "average wait time: " << fastResults.waitTime << std::endl;
  std::cout << "average travel time: " << fastResults.travelTime << std::endl;
  
  double waitPercentage = (slowResults.waitTime - fastResults.waitTime) * 100
    / slowResults.waitTime;
  double travelPercentage = (slowResults.travelTime - fastResults.travelTime) * 100
    / slowResults.travelTime;
  
  std::cout << "Pecentage speedup in wait time: " << waitPercentage << "%" <<  std::endl;
  std::cout << "Percentage speedup in travel time: " << waitPercentage << "%" << std::endl;
  
  return 0;
}
