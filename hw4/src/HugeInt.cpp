#include <sstream>
#include <algorithm> // for_each

#include "HugeInt.hpp"

//for testing
#include <iostream>

namespace hw4
{
  /*============================================================================
    HugeInt
        constructor that takes in the typedef Number and the sign of the number
        
    Revision History
        25 June 2015 - Function created
  *///==========================================================================
  HugeInt::HugeInt (const Number& value, bool positive)
  {
    this->positive = positive;
    
    this->value = value;
    
    // trim leading zeros
    Number::iterator valIT = this->value.end();
    --valIT;
    while (*valIT == 0 && valIT != this->value.begin())
    {
      this->value.erase(valIT);
      --valIT;
    }
    
    // check if all values of the vector are positive
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
    
    // if not a series of nonnegative digits revert to default value
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
    
    // digitize the magnituge of the input
    int number = this->positive ? value : -1 * value;
    while (number)
    {
      int digit = number%10;
      
      number /= 10;
      
      this->value.push_back(digit);
    }
  }
  
  
  /*============================================================================
    isLarger
        Assumes the the input Numbers both have the same number of digits.
        Returns 0 if the numbers are equal in magnitude, -1 if the second input
        is larger, and 1 if the first input is larger.
        
    Revision History
        28 June 2015 - Function created
  *///==========================================================================
  int isLarger(const Number& lhs, const Number& rhs)
  {    
    // does the lhs or rhs have the larger magnitude of value
    bool lhsLargerMag = false;
    bool rhsLargerMag = false;
    
    // start looking at the most significant digits
    Number::const_reverse_iterator lhsIT = lhs.rbegin();
    Number::const_reverse_iterator rhsIT = rhs.rbegin();
    while (lhsIT != lhs.rend() &&
           rhsIT != rhs.rend())
    {
      if (*lhsIT != *rhsIT)
      {
        if (*lhsIT > *rhsIT)
        {
          lhsLargerMag = true;
        }
        else
        {
          rhsLargerMag = true;
        }
        break;
      }
      else
      {
        lhsIT++;
        rhsIT++;
      }
    }
    
    int result;
    // if equal
    if (lhsLargerMag == rhsLargerMag)
    {
      result = 0;
    }
    else if (lhsLargerMag)
    {
      result = 1;
    }
    else
    {
      result = -1;
    }

    return result;
  }

  /*============================================================================
    operator==
        logical equality test operator overload

    Revision History
        28 June 2015 - Function created
  *///==========================================================================
  bool operator==(const HugeInt& lhs,
		  const HugeInt& rhs)
  {
    int result = isLarger(lhs.getValue(), rhs.getValue());
    return result == 0 && lhs.getSign() == rhs.getSign();
  }
  
  /*============================================================================
    operator+=
        unary addition assignment operator overload.  Is a member of the 
        HugeInt class
        
    Revision History
        26 June 2015 - Function created
  *///==========================================================================
  HugeInt& HugeInt::operator+=(const HugeInt& rhs) // number to add to self
  {    
    Number answer;
    if (this->positive == rhs.getSign())
    {
      answer = HugeInt::addSameSign(this->value, rhs.getValue());
    }
    else
    {
      Number subLHS;
      Number subRHS;
      if (this->positive == false)
      {
        // flip sides to exploit symmetry
        subLHS = rhs.getValue();
        subRHS = this->value;
      }
      else
      {
        subLHS = this->value;
        subRHS = rhs.getValue();
      }
      
      bool sign;
      answer = HugeInt::subtractSameSign(subLHS, subRHS, sign);

      this->positive = sign;
    }
    
    this->setValue(answer);

    return *this;
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
    
    std::stringstream ss;
    
    if(!number.getSign())
    {
      ss << "-";
    }
    
    Number value = number.getValue();
    std::for_each(value.rbegin(), value.rend(),
                  [&ss](const int digit)
                  {
                    ss << digit;
                  });
    
    out << ss.str();
    
    return out;
  }
  
  
  /*============================================================================
    operator<
        less than operator overload for the HugeInt class
        
    Revision History
        27 June 2015 - Function created
  *///==========================================================================
  bool operator<(const HugeInt& lhs, // left hand side value in comparison
                 const HugeInt& rhs) // right hand side value in comparison
  {
    bool isSmaller;
    // if their signs make this obvious
    if (lhs.getSign() == true && rhs.getSign() == false)
    {
      isSmaller = false;
    }
    else if (lhs.getSign() == false && rhs.getSign() == true)
    {
      isSmaller = true;
    }
    // if they have the same sign
    else
    {      
      // if they have the same number of digits
      if (lhs.getValue().size() == rhs.getValue().size())
      {
        int result = isLarger(lhs.getValue(), rhs.getValue());
        // rhs is larger
        if (result == -1)
        {
          // lhs is positive
          if (lhs.getSign())
          {
            isSmaller = true;
          }
          else
          {
            isSmaller = false;
          }
        }	
        //  lhs is larger
        else if (result == 1)
        {
          // lhs is positive
          if (lhs.getSign())
          {
            isSmaller = false;
          }
          else
          {
            isSmaller = true;
          }
        }
        // if they are equal
        else
        {
          isSmaller = false;
        }// if result
      }
      // if lhs has less digits
      else if (lhs.getValue().size() < rhs.getValue().size())
      {
        if (lhs.getSign())
        {
          isSmaller = true;
        }
        else
        {
          isSmaller = false;
        }
      }
      // if lhs has more digits
      else
      {
        if (lhs.getSign())
        {
          isSmaller = false;
        }
        else
        {
          isSmaller = true;
        }
      } // if same number of digits
    } // if their signs are the same
    return isSmaller;
  }

  /*============================================================================
    addSameSign
        adds two numbers if they share the same sign
        
    Revision History
        25 June 2015 - Function created
  *///==========================================================================
                              // left hand side digits
  Number HugeInt::addSameSign(const Number& lhsNum,
			      // right hand side digits
			      const Number& rhsNum)
  {
    // Container for the outcome
    Number answer;
    
    // values for the cur digit from each number
    int rhsValue;
    int lhsValue;
    
    // walkthrough both numbers adding the digits together
    int carry = 0;
    int number;
    int digit;
    Number::const_iterator lhsIT = lhsNum.begin();
    Number::const_iterator rhsIT = rhsNum.begin();
    while (lhsIT != lhsNum.end() ||
           rhsIT != rhsNum.end())
    {
      // get next rhs digit value
      if (rhsIT != rhsNum.end())
      {
        rhsValue = *rhsIT;
        ++rhsIT;
      }
      else
      {
        rhsValue = 0;
      }
      
      // get next lhs digit value
      if (lhsIT != lhsNum.end())
      {
        lhsValue = *lhsIT;
        ++lhsIT;
      }
      else
      {
        lhsValue = 0;
      }
      
      // perform the addition operation
      number = lhsValue + rhsValue + carry;
      digit = number%10;
      carry = number/10;
      
      answer.push_back(digit);
    } // while
    
    // check if there is still a carry from the last operation
    if (carry != 0)
    {
      answer.push_back(carry);
    }
    
    return answer;
    
  } // addSameSign
  
  Number HugeInt::subtractSameSign(const Number& lhsNumber,
				   const Number& rhsNumber,
				   bool& sign)
  {
    Number topNumber;
    Number bottomNumber;
    
    // figure out the sign
    if (lhsNumber < rhsNumber)
    {
      topNumber = rhsNumber;
      bottomNumber = lhsNumber;
      
      sign = false;
    }
    else
    {
      topNumber = lhsNumber;
      bottomNumber = rhsNumber;
      
      sign = true;
    }

    Number answer;
    if (lhsNumber == rhsNumber)
    {
      answer = {0};
    }
    else
    {
      Number::iterator topIT = topNumber.begin();
      Number::iterator botIT = bottomNumber.begin();
      while (topIT != topNumber.end())
      {
        int topVal;
        if (topIT != topNumber.end())
        {
          topVal = *topIT;
          ++topIT;
        }
        else
        {
          topVal = 0;
        }

        int botVal;
        if (botIT != bottomNumber.end())
        {
          botVal = *botIT;
          ++botIT;
        }
        else
        {
          botVal = 0;
        }
        
        // attempt the subtraction
        if (topVal > botVal)
        {
          answer.push_back(topVal-botVal);
        }
        else
        {
          
        }
      }
    }
    
    return answer;
  }
  
} // namespace hw4
