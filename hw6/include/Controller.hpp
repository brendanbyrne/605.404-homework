/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 8 July, 2015
  
  Revision History
      8 July, 2015 - class created
  
  Class Name: Controller
  
  Intent: Controls the elevator system
  
  Description: This controller determines where its elevators should go.  This 
               control is possible because the controller has access to view
	       the state of two building resources. First is the building's 
	       floors and the second is the building's elevators.

*///============================================================================

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <memory>

#include "Floor.hpp"
#include "Elevator.hpp"

namespace hw6
{

  class Controller
  {
  public:
    Controller();
    Controller(std::shared_ptr<Floors> floorsPtr,
	       std::shared_ptr<Elevators> elevatorsPtr);
    
    void ptrTest();
    
  private:
    std::shared_ptr<Floors> floorsPtr;
    std::shared_ptr<Elevators> elevatorsPtr;
    
  }; // class Controller

} // namespace hw6

#endif // CONTROLLER_HPP
