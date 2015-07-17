// Simulator.cpp

#include <algorithm> // for_each
#include <iostream>

#include "Simulator.hpp"

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
  SimulationOutput Simulator::calculateResults()
  {
    // If no exit data return 0
    if (this->building.getExitResults().size() == 0)
    {
      SimulationOutput nullOutput;
      return nullOutput;
    }

    Group results = this->building.getExitResults();
    int sumWaitingTime = 0;
    int sumTravelTime = 0;
    std::for_each(results.begin(), results.end(),
                  [&sumWaitingTime, &sumTravelTime](const Passenger& person) -> void
                  {
                    sumWaitingTime += person.getBoardTime() - person.getStartTime();
                    sumTravelTime += person.getEndTime() - person.getBoardTime();
                  });
    
    int size = this->building.getExitResults().size();
    double averageWaitTime = static_cast<double>(sumWaitingTime) / static_cast<double>(size);
    double averageTravelTime = static_cast<double>(sumTravelTime) / static_cast<double>(size);
    
    SimulationOutput simOutput;
    simOutput.waitTime = averageWaitTime;
    simOutput.travelTime = averageTravelTime;
    
    return simOutput;
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
      int watchdog = 0;
      while (this->stillSimulating())// && watchdog++ < 3)
      {
        tick();
        ++this->simTime;
      }
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
