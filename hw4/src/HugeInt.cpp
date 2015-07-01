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
  HugeInt::HugeInt (const std::string& numberStr) // string to turn into HugeInt
  { 
    this->positive = true;
    
    bool errorOccurred = false;
    
    std::string::const_reverse_iterator strIT = numberStr.rbegin();
    char digit;
    char rawInput;
    while (strIT != numberStr.rend())
    {
      // the value of the character in ascii
      rawInput = static_cast<char>(*strIT);
      
      // if negative sign detected
      if (rawInput == '-')
      {
        this->positive = false;
        break;
      }
      
      // if not a digit
      if (rawInput < '0' || rawInput > '9')
      {
        errorOccurred = true;
        break;
      }
      
      // shift rawInput from ascii domain to number domain
      digit = rawInput - '0';      
      this->value.push_back(digit);
      ++strIT;
    }
    
    trimZeros(this->value);

    
    // if there was an error in converting string to number, set to 0
    if (errorOccurred)
    {
      this->value = {0};
      this->positive = true;
    }
  }
  
  /*============================================================================
    HugeInt
        convertion constructor for an int
        
    Revision History
        25 June 2015 - Function created
  *///==========================================================================
  HugeInt::HugeInt (const int value) // number to turn into HugeInt
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
    
    this->value = HugeInt::digitizeInt(number);
  }
  
  /*============================================================================
    addSameSign
        adds two numbers assuming they share the same sign
        
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
      digit = number % HugeInt::BASE;
      carry = number / HugeInt::BASE;
      
      answer.push_back(digit);
    } // while
    
    // check if there is still a carry from the last operation
    if (carry != 0)
    {
      answer.push_back(carry);
    }
    
    return answer;
    
  } // addSameSign
  
  /*============================================================================
    compareSameLength
        Assumes the the input Numbers both have the same number of digits.
        Returns 0 if the numbers are equal in magnitude, -1 if the second input
        is larger, and 1 if the first input is larger.
        
    Revision History
        28 June 2015 - Function created
  *///==========================================================================
                                 // first value to use in comparison
  int HugeInt::compareSameLength(const Number& lhs,
                                 // second value to use in comparison
                                 const Number& rhs)
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
    } // while have digits
    
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
  } // compareSameLength
  
  /*============================================================================
    digitizeInt
        Given an int, this method reduces the absolute value of it to it's
	individual digits in ascending order of magnitude
        
    Revision History
        28 June 2015 - Function created
  *///==========================================================================
  Number HugeInt::digitizeInt(int value)
  {
    // make sure number is positive
    int toDigitize = value < 0 ? value*-1 : value;
        
    Number number;
    do
    {
      int digit = toDigitize % HugeInt::BASE;
      
      toDigitize /= HugeInt::BASE;
      
      number.push_back(digit);
    } while (toDigitize);
    
    return number;
  }

  /*============================================================================
    multiplyByInt
        finds the product of a typedef Number and an int, returns it as another
	typedef Number
        
    Revision History
        30 June 2015 - Function created
  *///==========================================================================
  Number HugeInt::multiplyByInt(const Number& number, // Number to multiply
				int single) // the single digit to multiply
  {
    // the output
    Number total = {0};
    
    // for all the components of the number (1's, 10's , 100's, etc.)
    // multiply them by the single value and then sum them
    Number::const_iterator numIT;
    int tensShift = 0;
    for(numIT = number.begin(); numIT != number.end(); ++numIT)
    {
      // pads the beggin
      Number withPadding(tensShift, 0);
      
      // multiply just the digit and single, return the digitized version
      Number endValue = HugeInt::digitizeInt(*numIT *  single);

      // append newly calculated digits to the padding
      for (auto digit : endValue)
      {
	withPadding.push_back(digit);
      }      
      
      total = HugeInt::addSameSign(total, withPadding);
      
      ++tensShift;
    }
    
    return total;
    
  }
  
   /*============================================================================
    operator+=
        unary addition assignment operator overload.
        
    Revision History
        26 June 2015 - Function created
  *///==========================================================================
  HugeInt& HugeInt::operator+=(const HugeInt& rhs) // number to add to self
  {    
    Number answer;
    
    // determine which method + or - to use based on the signs
    if (this->positive == rhs.isPositive())
    {                                                                   
      // equal signs mean magnitude increase
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
    
    this->value = answer;

    return *this;
  }
  
  /*============================================================================
    operator-=
        unary subtract assignment operator overload.
        
    Revision History
        26 June 2015 - Function created
  *///==========================================================================
  HugeInt& HugeInt::operator-=(const HugeInt& rhs)//number to subtract from self
  {    
    Number answer;
    bool sign;
    
    // determine which method + or - to use based on the signs
    if (this->positive != rhs.isPositive())
    {
      answer = HugeInt::addSameSign(this->value, rhs.getValue());
      sign = this->positive;
    }
    else if (this->positive && rhs.isPositive())
    {
      answer = HugeInt::subtractSameSign(this->value, rhs.getValue(), sign);
    }
    else
    {
      answer = HugeInt::subtractSameSign(rhs.getValue(), this->value, sign);
    }
    
    this->positive = sign;
    this->value = answer;
    
    return *this;
  }  
  
  /*============================================================================
    operator*=
        unary multication assignment operator overload.
        
    Revision History
        30 June 2015 - Function created
  *///==========================================================================
  HugeInt& HugeInt::operator*=(const HugeInt& rhs) // number to multiply by self
  {
    Number sum = {0};
    
    // tens place shift count
    int shift = 0;
    
    // for every digit the this number
    Number::const_iterator lhsIT;
    for (lhsIT = this->value.begin(); lhsIT != this->value.end(); ++lhsIT)
    {
      // shift the right hand number
      Number work(shift, 0);  
      for (auto digit : rhs.getValue())
      {
	work.push_back(digit);
      }
      
      // multiply the shifted value by the current digit of this
      // then add the result to the answer
      sum = HugeInt::addSameSign(sum, HugeInt::multiplyByInt(work, *lhsIT));
      
      // shift to the next "tens" place
      ++shift;
    }
    
    // trim extra zeros
    trimZeros(sum);
    
    bool sign;
    // check if the answer is 0 and make it positive if true
    if (sum.size() == 1 and sum[0] == 0)
    {
      sign = true;
    }
    else
    {
      // same signs yield positive results while differing signs yields negative
      sign = this->positive == rhs.isPositive();
    }
    
    // assign results
    this->positive = sign;
    this->value = sum;
    
    return *this;
  }
  
  /*============================================================================
    operator/=
        unary division operator overload
        
    Revision History
        25 June 2015 - Function created
  *///==========================================================================
  HugeInt& HugeInt::operator/=(const HugeInt& rhs) // number to divide self by
  {
    // if trying to divid by zero.....don't
    if (rhs.getValue().size() == 1 && rhs.getValue()[0] == 0)
    {
      return *this;
    }
    
    // makes positive copy of self
    HugeInt dividend = *this;
    dividend.setSign(true);
    
    // makes positive copy of rhs
    HugeInt divisor = rhs;
    divisor.setSign(true);
    
    // subtract divisor from dividend until remainder is less than zero
    Number subCount = {0};
    HugeInt remainder = dividend - divisor;
    
    while (remainder.isPositive())
    {
      subCount = addSameSign(subCount, {1});
      remainder -= divisor;

      
    }

    bool sign;
    // check if the answer is 0 and make it positive if true
    if (subCount.size() == 1 && subCount[0] == 0)
    {
      sign = true;
    }
    else
    {
      // same signs yield positive results while differing signs yields negative
      sign = this->positive == rhs.isPositive();
    }
    
    // assign results
    this->positive = sign;
    this->value = subCount;
    
    return *this;
  }
  
  /*============================================================================
    operator==
        logical equality test operator overload

    Revision History
        28 June 2015 - Function created
  *///==========================================================================
  bool operator==(const HugeInt& lhs, // left hand side of equality test
		  const HugeInt& rhs) // right hand side of equality test
  {
    bool isEqual;
    // only test if values share same number of digits
    if (lhs.getValue().size() == rhs.getValue().size())
    {
      int result = HugeInt::compareSameLength(lhs.getValue(), rhs.getValue());
      isEqual = result == 0 && lhs.isPositive() == rhs.isPositive();
    }
    else
    {
      isEqual = false;
    }
    return isEqual;
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
    
    // add negative sign
    if(!number.isPositive())
    {
      ss << "-";
    }
    
    Number value = number.getValue();
    std::for_each(value.rbegin(), value.rend(),
                  // upcasts char to int for printing purposes
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
    if (lhs.isPositive() == true && rhs.isPositive() == false)
    {
      isSmaller = false;
    }
    else if (lhs.isPositive() == false && rhs.isPositive() == true)
    {
      isSmaller = true;
    }
    // if they have the same sign
    else
    {      
      // if they have the same number of digits
      if (lhs.getValue().size() == rhs.getValue().size())
      {
        int result = HugeInt::compareSameLength(lhs.getValue(), rhs.getValue());
        // rhs is larger
        if (result == -1)
        {
          // lhs is positive
          if (lhs.isPositive())
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
          if (lhs.isPositive())
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
        if (lhs.isPositive())
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
        if (lhs.isPositive())
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
  } // operator<
    
  /*============================================================================
    subtractSameSign
        subtracts two numbers assuming they share the same sign.  Returns the 
        the sign of the answer by reference
        
    Revision History
        30 June 2015 - Function created
  *///==========================================================================
  Number HugeInt::subtractSameSign(const Number& lhsNumber, // left hand number
				   const Number& rhsNumber, // right hand number
				   bool& sign) // returns sign after operation
  {
    // figure out if the inputs should be reordered
    bool shouldSwitch = false;
    if (lhsNumber.size() == rhsNumber.size())
    { 
      if (compareSameLength(lhsNumber, rhsNumber) == -1)
      {
        shouldSwitch = true;
      }
    }
    else
    {
      if (lhsNumber.size() < rhsNumber.size())
      {
        shouldSwitch = true;
      }
    }
    
    // possibly reorder and assign sign
    Number topNumber;
    Number bottomNumber;
    if (shouldSwitch)
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
    
    // if numbers are equal make answer 0
    Number answer;
    if (lhsNumber == rhsNumber)
    {
      answer = {0};
    }
    // perform full subtraction method
    else
    {
      int difference;
      int borrow = 0;
      Number::iterator topIT = topNumber.begin();
      Number::iterator botIT = bottomNumber.begin();
      while (topIT != topNumber.end())
      {
        // get next digit for top number
        int topVal;
        if (topIT != topNumber.end())
        {
          topVal = *topIT;
          ++topIT;
        }
        else
        {
          // if no next digit, use zero
          topVal = 0;
        }
        
        // get next digit for bottom number
        int botVal;
        if (botIT != bottomNumber.end())
        {
          botVal = *botIT;
          ++botIT;
        }
        else
        {
          // if no next digit, use zero
          botVal = 0;
        }
        
        // where the actual subtraction of bottom digit from top digit happens
        difference = topVal - botVal - borrow;
        borrow = 0;
        
        // if you need to borrow from the next digit over
        if (difference < 0)
        {
          difference += HugeInt::BASE;
          borrow = 1;
        }
        
        answer.push_back(difference);
        
      } // while still digits to subtract
    } // if numbers equal
    
    trimZeros(answer);
    
    return answer;
  } // subtractSameSign
  
  /*============================================================================
    trimZeros
        takes a number and trims the leading 0s off of it
        
    Revision History
        25 June 2015 - Function created
  *///==========================================================================
  void trimZeros(Number& number) // the number to trim zeros from
  {
    // trim leading zeros, except if the number is just 0
    Number::iterator digitIT = number.end();
    --digitIT;
    while (*digitIT == 0 && digitIT != number.begin())
    {
      number.erase(digitIT);
      --digitIT;
    }
  }
  
} // namespace hw4
