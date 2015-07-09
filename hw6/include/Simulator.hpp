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

#include <vector>
#include <queue>

#include "Elevator.hpp"
#include "Floor.hpp"
#include "Passenger.hpp"

namespace hw6
{
  // convenience aliases
  typedef std::vector<Elevator> Elevators;
  typedef std::vector<Floor> Building;
    
  class Simulator
  { 
  public:
    Simulator(); // default constructor
    Simulator(const Line& people,
               const Building& building,
               const Elevators& elevators); // full constructor
    
    // starts the simulation
    double start();
    
    // setters
    void setBuilding(const Building& building);
    void setElevators(const Elevators& elevators);
    void setPeople(const Line& people) ;
    
  private:
    // simulation variables
    Line people;
    Building building;
    Elevators elevators;
    
    // outcome of data checks
    bool hasPeople;
    bool hasBuilding;
    bool hasElevators;
    
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
    this->elevators = elevators;
  }
  
  /*============================================================================
    setElevator
        set the value of the elevators data member
        
    Revision History
        8 July 2015 - Function created
  *///==========================================================================
  //                                   desired value
  inline void Simulator::setElevators(const Elevators& elevators)
  {
    this->elevators = elevators;
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
  }
} // namespace hw6

#endif // SIMULATOR_HPP
