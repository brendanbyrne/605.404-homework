// Simulator.cpp

#include <algorithm> // for_each
#include <iostream>

#include "Simulator.hpp"

// for testing only
#include <iostream>

namespace hw6
{
  /*============================================================================
    Simulator
        default constructor
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  Simulator::Simulator()
  {
    this->hasPeople   = false;
    this->hasBuilding = false;
  }

  /*============================================================================
    Simulator
        full constructor
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  Simulator::Simulator(const Line& people, // people riding the elevators
                       const Building& building): // building to simulate
    people(people), building(building)
  { 
    this->hasPeople   = true;
    this->hasBuilding = true;
  }
  
  /*============================================================================
    calculateResults
        calculates the average wait time of a passenger riding the elevator
        
    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  double Simulator::calculateResults()
  {
    // If no exit data return 0
    if (this->building.getExitResults().size() == 0)
    {
      return 0.0;
    }

    Group results = this->building.getExitResults();
    int sum = 0;
    std::for_each(results.begin(), results.end(),
                  [&sum](const Passenger& person) -> void
                  {
                    sum += person.getEndTime() - person.getStartTime();
                  });
    
    int size = this->building.getExitResults().size();
    double average = static_cast<double>(sum) / static_cast<double>(size);
    
    return average;
  }
  
  /*============================================================================
    start
        start the simulation
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  void Simulator::start()
  {

    // if simulation has enough data
    if (this->hasPeople &&
        this->hasBuilding)
    {
      // reset the simulation clock
      this->simTime = 0;

      // run simulation till its termination condition has been reached
      while (this->stillSimulating())
      {
        //std::cout << "Current time: " << this->simTime << std::endl;
        tick();
	++this->simTime;
      }
    }
    
//    std::cout << "Final elevator state" << std::endl;
    for (auto e : this->building.getElevators())
    {
      //std::cout << e << std::endl;
    }
    
  }
    
  /*============================================================================
    tick
        advances the simulition forward one unit of time
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  void Simulator::tick()
  { 
    
    // find people that need to enter the simulation now
    // and add them to their floor
    Group assignToFloor;
    while (people.front().getStartTime() == this->simTime &&
           people.size() > 0)
    { 
      this->building.addPerson(people.front());
      people.pop();
    }
    
    this->building.advance(this->simTime);

  }
  
} // namespace hw6
