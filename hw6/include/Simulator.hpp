/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 8 July, 2015
  
  Revision History
      8 July, 2015 - class created
  
  Class Name: Simulator
  
  Intent: Manage the different components of the elevator simulation
  
  Description: The job of this class is to control the flow of time and manage
                the flow of people into the system

*///============================================================================

#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "Building.hpp"

namespace hw6
{
  class Simulator
  {
  public:
    Simulator(); // default constructor
    Simulator(const Line& people,
	      const Building& building); // full constructor
    
    double calculateResults(); // finds the average weight time per person

    // setters
    void setBuilding(const Building& building);
    void setPeople(const Line& people) ;
    
    void start(); // starts the simulation
    
  private:
    // simulation variables
    Line people;
    Building building;
    int simTime;
    
    // outcome of data checks
    bool hasPeople;
    bool hasBuilding;    
    
    bool stillSimulating(); // tests the system for a termination state
    void tick(); // advances the simulation one time unit
    
  }; // class Simulator

  /*============================================================================
    setBuilding
        set the value of the building data member
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline void Simulator::setBuilding(const Building& building) // desired value
  {
    this->building = building;
    hasBuilding = true;
  }
    
  /*============================================================================
    setPeople
        set the value of the people data member
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline void Simulator::setPeople(const Line& people) // desired value
  {
    this->people = people;
    this->hasPeople = true;
  }
  
  /*============================================================================
    stillSimulating
        checks simulation for a termination condition
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  inline bool Simulator::stillSimulating()
  {
    // continue while there are still passengers waiting to ride an elevator
    return !this->people.empty() || !this->building.isEmpty();
  }
  
} // namespace hw6

#endif // SIMULATOR_HPP
