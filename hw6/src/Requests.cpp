//Requests.cpp

#include <algorithm> // find_if

#include "Requests.hpp"

#include <iostream>
namespace hw6
{
  /*============================================================================
    Requests
        creats empty collection of requests

    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  Requests::Requests()
  {
  }
  
  /*============================================================================
    add
        attempt to add an item to the requests list

    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  void Requests::add(const Request& request) // the item to add
  {
    // if a similar request doesn't exist already
    if (this->find(request) == this->list.end())
    {
      this->list.push_back(request);
      this->list.sort();
    }
  }
  
  /*============================================================================
    clear
        delete requests that are similar to the given one

    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  void Requests::clear(const Request& request)
  {
    auto location = this->find(request);
    while (location != this->list.end())
    {
      this->list.erase(location);
      location = this->find(request);
    }
  }

  /*============================================================================
    find
        search for an object in the requests list and return an iterator to its
        location

    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  std::list<Request>::iterator Requests::find(const Request& request)
  {
    std::list<Request>::iterator location;
    location = std::find_if(this->list.begin(), this->list.end(),
                            [&request](const Request& item) -> bool
                            {
                              bool areSame = std::get<1>(item) ==
                                std::get<1>(request)
                                &&
                                std::get<2>(item) ==
                                std::get<2>(request);
                              
                              return areSame;
                            });
    return location;
  }
  
  /*============================================================================
    operator<<
        insertion overload for displaying a list of requests

    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, const Requests& requests)
  {
    for (auto item : requests.getList())
    {
      out << item << "\n";
    }
    return out;
  }

  /*============================================================================
    operator<<
        insertion overload for displaying a single request

    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, const Request& request)
  {
    out << std::get<0>(request) << " "
        << std::get<1>(request) << " "
        << std::get<2>(request);
    
    return out;
  }
    
  /*============================================================================
    update
        if similar request exists then remove the old one and replace with new 
        one, else just add it

    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  void Requests::update(const Request& request)
  {
    auto location = this->find(request);
    
    // if a similar request already exists
    if (location != this->list.end())
    {
      this->list.erase(location);
    }
    this->list.push_back(request);
    this->list.sort();
  }
  
} // namespace hw6
