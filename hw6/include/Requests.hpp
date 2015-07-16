/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 16 July, 2015
  
  Revision History
      16 July, 2015 - class created
  
  Class Name: Requests
  
  Intent: Manage the requests for floors
  
  Description: A thin wrapper around a list that manages which elevator requests
               get saved for later commanding.  Equivalence is determined by
               only looking at the floor and direction, not the time.  Time is 
               included and is the first element so sort() can leverage the 
               lexigraphical built-in sort for the tuple

*///============================================================================

#ifndef REQUESTS_HPP
#define REQUESTS_HPP

#include <list>
#include <tuple>
#include <ostream>

#include "Passenger.hpp"

namespace hw6
{
  // format for a single request
  // entry time, goal floor number, goal direction
  typedef std::tuple<int, int, Direction> Request;
  
  class Requests
  {
  public:
    Requests(); // constructor

    void add(const Request& request);
    void update(const Request& request); 
    void clear(const Request& request);
    
    // list pass throughs
    int size() const;
    Request front() const;
    void pop();
    
    std::list<Request> getList() const;

  private:
    std::list<Request> list;

    std::list<Request>::iterator find(const Request& request);
    
  }; // Requests
  
  // operation overloads
  std::ostream& operator<<(std::ostream& out, const Requests& requests);
  std::ostream& operator<<(std::ostream& out, const Request& request);
  
  /*============================================================================
    front
        returns the item at the beginning of the list data member
        
    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  inline Request Requests::front() const
  {
    return this->list.front();
  }
  
  /*============================================================================
    getList
        returns value of the list data member
        
    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  inline std::list<Request> Requests::getList() const
  {
    return this->list;
  }
  
  /*============================================================================
    pop
        pop off the front item of the list data member
        
    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  inline void Requests::pop()
  {
    return this->list.pop_front();
  }
  
  /*============================================================================
    size
        returns the size of the list data member
        
    Revision History
        16 July 2015 - Function created
  *///==========================================================================
  inline int Requests::size() const
  {
    return this->list.size();
  }
  
  
} // namespace hw6

#endif // #REQUESTS_HPP
