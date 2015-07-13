// Controller.cpp

#include "Controller.hpp"

namespace hw6
{
  /*============================================================================
    Controller
        default constructor
        
    Revision History
        13 July 2015 - Function created
  *///==========================================================================
  Controller::Controller():
    floorsPtr(nullptr), elevatorsPtr(nullptr)
  {
  }
  
  /*============================================================================
    Controller
        full constructor
        
    Revision History
        13 July 2015 - Function created
  *///==========================================================================
  Controller::Controller(std::shared_ptr<Floors> floorsPtr,
			 std::shared_ptr<Elevators> elevatorsPtr):
    floorsPtr(floorsPtr), elevatorsPtr(elevatorsPtr)
  {
  }
  
  /*============================================================================
    issueCommands
        issue some commands directly to the elevators and returns thoses that
        can't be issued here back to be carried out else where
        
    Revision History
        13 July 2015 - Function created
  *///==========================================================================
  Commands Controller::issueCommands()
  {
    Commands commands;
    
    int id = 0;
    Elevators::iterator iter;
    for (iter = elevatorsPtr->begin();
         iter != elevatorsPtr->end();
         ++iter)
    {
      if (iter->getGoalFloor() == iter->getCurrentFloor() &&
          iter->getState() == Elevator::State::STOPPED)
      {
        commands.push_back(Command(id, Action::OPEN));
      }
                           
      ++id;
    }

    return commands;
  }
  
} // namespace hw6
