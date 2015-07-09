// Simulator.cpp

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
  }
  
  /*============================================================================
    start
        start the simulation
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  double Simulator::start()
  {
    double averageTime = 0.0;
    
    if (this->hasPeople &&
        this->hasBuilding &&
        this->hasElevators)
    {
      while (stillSimulating())
      {
        tick();
      }
    }
    
    return averageTime;
  }
  
  /*============================================================================
    stillSimulating
        returns true if the simulation still needs to be run
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  bool Simulator::stillSimulating()
  {
    // are there any people still waiting to ride an elevator
    bool shouldContinue = people.size() > 0;
    
    // check all floors for people still waiting
    Building::iterator floorIter = this->building.begin();
    while (!shouldContinue &&
           floorIter != this->building.end())
    {
      if (floorIter->getGoingUp().size() > 0 ||
          floorIter->getGoingDown().size() > 0)
      {
        shouldContinue = true;
      }
      else
      {
        // check next floor
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
  }
  
} // namespace hw6
