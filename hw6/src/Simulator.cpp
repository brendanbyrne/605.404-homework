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

    this->waitTimes.reserve(people.size());
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
    while (people.front().getStartTime() == this->simTime)
    {
      this->building.addPerson(people.front());
      people.pop();
    }

    this->building.advance();

  }
  
} // namespace hw6
