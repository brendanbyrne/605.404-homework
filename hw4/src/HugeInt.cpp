#include <sstream>
#include <algorithm> // for_each

#include "HugeInt.hpp"

//for testing
#include <iostream>

namespace hw4
{
  /*============================================================================
    HugeInt
        constructor that takes in an string
	
    Revision History
        25 June 2015 - Function created
  *///==========================================================================
  HugeInt::HugeInt (const std::deque<int>& value, bool positive)
  {
    this->positive = positive;
    
    this->value = value;
    
    // trim leading zeros
    std::deque<int>::iterator valIT = this->value.begin();
    // +1 for case when value is {0}
    while (*valIT == 0 && valIT + 1 != this->value.end())
    {
      this->value.erase(valIT);
      ++valIT;
    }
    
    // check if all values of the deque are positive
    bool isPositive = true;
    valIT = this->value.begin();
    while (isPositive && valIT != this->value.end())
    {
      isPositive = *valIT > 0;
      ++valIT;
    }
    
    // check if all values of the deque are single digits
    bool isDigit = true;
    valIT = this->value.begin();
    while (isDigit && valIT != this->value.end())
    {
      isDigit = *valIT < 10;
      ++valIT;
    }
    
    // if not a series of digits revert to default value
    if (!isDigit || !isPositive)
    {
      this->value = {0};
    }
  }
    
  /*============================================================================
    HugeInt
        convertion constructor for an int
	
    Revision History
        25 June 2015 - Function created
  *///==========================================================================
  HugeInt::HugeInt (const int value)
  {
    
    if (value < 0)
    {
      this->positive = false;
    }
    else
    {
      this->positive = true;
    }
    
    // digit
    int number = this->positive ? value : -1 * value;
    while (number)
    {
      int digit = number%10;
            
      number /= 10;
      
      this->value.push_front(digit);
    }
  }
  
  /*============================================================================
    operator+=
        unary addition assignment operator overload.  Is a member of the 
        HugeInt class
	
    Revision History
        26 June 2015 - Function created
  *///==========================================================================
  HugeInt& operator+=(const HugeInt& rhs)
  {
    bool isPositive;
    std::deque<int> answer;
    
    int carry = 0;
    std::deque<int>::const_reverse_iterator lhsIT = this->value.rbegin();
    std::deque<int>::const_reverse_iterator rhsIT = rhs.getValue().rbegin();
  }
  
  /*============================================================================
    operator<<
        insertion operator overload for the HugeInt class
	
    Revision History
        25 June 2015 - Function created
  *///==========================================================================
  std::ostream& operator<<(std::ostream& out, // desired output stream
			   const HugeInt& number) // number to display
  
  {
    std::deque<int> value = number.getValue();
    
    std::stringstream ss;
    
    std::for_each(value.begin(), value.end(),
                  [&ss](const int digit)
                  {
                    ss << digit;
                  });
    
    out << ss.str();
    
    return out;
  }

} // namespace hw4
