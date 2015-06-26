/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 25 June, 2015
  
  Revision History
      25 June, 2015 - class created
  
  Class Name: HugeInt
  
  Intent: Allow integer operations for an number of unlimited size
  
  Description: 

*///============================================================================

#ifndef HUGEINT_HPP
#define HUGEINT_HPP

#include <string>
#include <ostream>

namespace hw4
{

  class HugeInt
  {
    
  public:
    
    HugeInt(const std::string& value = "0"); // constructor
    HugeInt(const int value); // convertion constructor
    
    std::string getValue() const; // value data member getter
    void setValue(const std::string& value); // value data member setter
    
  private:
    std::string value; // the string version of the number
    
  }; // class HugeInt
  
  /*============================================================================
    getValue
        return the value of the value data member
	
    Revision History
        25 June 2015 - Function created
  *///==========================================================================                                         
  inline std::string HugeInt::getValue() const
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
  inline void HugeInt::setValue(const std::string& value)
  {
    this->value = value;
  }
  
  std::ostream& operator<<(std::ostream& out, const HugeInt& value);
  
} // namespace hw4


#endif // HUGEINT_HPP
