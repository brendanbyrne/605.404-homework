/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 25 June, 2015
  
  Revision History
      25 June, 2015 - class created
  
  Class Name: HugeInt
  
  Intent: Allow integer operations for an number of unlimited size
  
  Description: the value data member

*///============================================================================

#ifndef HUGEINT_HPP
#define HUGEINT_HPP

#include <deque>
#include <ostream>

namespace hw4
{

  class HugeInt
  {
    
  public:
    
    HugeInt(const std::deque<int>& value = {0},
            bool positive = true); // constructor
    HugeInt(const int value); // convertion constructor
    
    std::deque<int> getValue() const; // value data member getter
    void setValue(const std::deque<int>& value); // value data member setter
   
    HugeInt& operator+=(const HugeInt& rhs); // 
 
  private:
    std::deque<int> value; // the vectored digits of the number
    bool positive;
    
  }; // class HugeInt
  
  /*============================================================================
    getValue
        return the value of the value data member
	
    Revision History
        25 June 2015 - Function created
  *///==========================================================================                                         
  inline std::deque<int> HugeInt::getValue() const
  {
    return this->value;
  }
  
  /*============================================================================
    setValue
        set the value of the value data member
	
    Revision History
        25 June 2015 - Function created
  *///==========================================================================
                                // desired value for the huge int
  inline void HugeInt::setValue(const std::deque<int>& value)
  {
    this->value = value;
  }
  
  std::ostream& operator<<(std::ostream& out, const HugeInt& value);
  
} // namespace hw4

#endif // HUGEINT_HPP
