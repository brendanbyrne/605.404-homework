// Controller.cpp

#include "Controller.hpp"

#include <iostream>

namespace hw6
{
  Controller::Controller()
  {
    floorsPtr = nullptr;
    elevatorsPtr = nullptr;
  }
  
  Controller::Controller(std::shared_ptr<Floors> floorsPtr,
			 std::shared_ptr<Elevators> elevatorsPtr):
    floorsPtr(floorsPtr), elevatorsPtr(elevatorsPtr)
  {
  }

  void Controller::ptrTest()
  {
    std::cout << "number of floors: " << floorsPtr->size() << std::endl;
  }

} // namespace hw6
