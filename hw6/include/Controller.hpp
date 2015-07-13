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

#include <vector>
#include <memory>

#include "Floor.hpp"
#include "Elevator.hpp"

namespace hw6
{
  // GOAL - Update goalFLoor with new value
  // OPEN - open the doors and let passengers on or off
  enum class Action {GOAL, OPEN};

  struct Command
  {
    // convenience constructor
    Command(int id, Action action, int data = 0):
      id(id), action(action), data(data){};
    
    int id;        // who the action is for, index in Elevators container
    Action action; // what to do
    int data;      // extra if action requires it, currently just goal floor
  };
  
  // convenience aliases
  typedef std::vector<Command> Commands;
  
  class Controller
  {
  public:
    Controller(); // default constructor
    Controller(std::shared_ptr<Floors> floorsPtr,
	       std::shared_ptr<Elevators> elevatorsPtr); // full constructor
    
    // issue commands to elevators, return commands for  building to execute
    Commands issueCommands();
    
    void makeRequest(const Request& request);
    void updateQueue(int floorRequest);
    
  private:
    std::shared_ptr<Floors> floorsPtr;
    std::shared_ptr<Elevators> elevatorsPtr;
    Requests requests;
    
  }; // class Controller
  
  /*============================================================================
    issueCommands
        default constructor
        
    Revision History
        13 July 2015 - Function created
  *///==========================================================================
  inline void Controller::makeRequest(const Request& request)
  {
    requests.push(request);
  }
  
} // namespace hw6

#endif // CONTROLLER_HPP
