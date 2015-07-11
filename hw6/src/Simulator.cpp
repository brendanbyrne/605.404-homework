// Simulator.cpp

#include <algorithm>
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
    this->hasPeople    = false;
    this->hasBuilding  = false;
    this->hasElevators = false;
  }

  /*============================================================================
    Simulator
        full constructor
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  Simulator::Simulator(const Line& people, // people riding the elevators
                       const Building& building, // layout of building floors
                       const Elevators& elevators): // elevators to use
    people(people), elevators(elevators), building(building)
  { 
    this->hasPeople    = people.size()    != 0 ? true : false;
    this->hasBuilding  = building.size()  != 0 ? true : false;
    this->hasElevators = elevators.size() != 0 ? true : false;

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
    if (this->hasPeople &&
        this->hasBuilding &&
        this->hasElevators)
    {
      // reset the simulation clock
      this->simTime = 0;

      // run simulation till its termination condition has been reached
      while (stillSimulating())
      {
        tick();
	
	++this->simTime;
      }
    }
  }
  
  /*============================================================================
    stillSimulating
        checks simulation for a termination condition
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  bool Simulator::stillSimulating()
  {
    // are there any people still waiting to ride an elevator
    bool shouldContinue = !people.empty();
    
    // check all floors for people still waiting
    Building::iterator floorIter = this->building.begin();
    while (!shouldContinue &&
           floorIter != this->building.end())
    {
      if (floorIter->getGoingUp().empty() ||
          floorIter->getGoingDown().empty())
      {
        shouldContinue = true;
      }
      else
      {
        ++floorIter;
      }
    }
    
    // check all elevators for people still riding
    Elevators::iterator elevatorIter = this->elevators.begin();
    while (!shouldContinue &&
           elevatorIter != this->elevators.end())
    {
      if (elevatorIter->getOnBoard().size() > 0)
      {
        shouldContinue = true;
      }
      else
      {
        ++elevatorIter;
      }
    }
    
    return shouldContinue;
  }
  
  /*============================================================================
    tick
        advances the simulition forward one unit of time
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  void Simulator::tick()
  {
    std::cout << "Tick tock " << this->simTime << std::endl;

    // find people that need to enter the simulation now
    // and add them to their floor
    Group assignToFloor;
    while (people.front().getStartTime() == this->simTime)
    {
      building[people.front().getStartFloor()].waitInLine(people.front());
      people.pop();
    }
    
    //controller.advance()

  }
  
} // namespace hw6
