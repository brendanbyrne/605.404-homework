#include <sstream>
#include <algorithm> // for_each
///#include <cstdlib> // atoi

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
  }
  
  /*============================================================================
    digitizeInt
        Given an int, this method
        
    Revision History
        28 June 2015 - Function created
  *///==========================================================================
  Number HugeInt::digitizeInt(int value)
  {
    // make sure number is positive
    int toDigitize = value < 0 ? value*-1 : value;
    
    Number number;
    while (toDigitize)
    {
      int digit = toDigitize % HugeInt::BASE;
      
      toDigitize /= HugeInt::BASE;
      
      number.push_back(digit);
    }
    return number;
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
    // only test if values share same number of digits
    if (lhs.getValue().size() == rhs.getValue().size())
    {
      int result = HugeInt::compareSameLength(lhs.getValue(), rhs.getValue());
      return result == 0 && lhs.getSign() == rhs.getSign();
    }
    else
    {
      return false;
    }
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
    
    this->setValue(answer);

    return *this;
  }
  
  /*============================================================================
    operator-=
        unary subtract assignment operator overload.  Is a member of the 
        HugeInt class
        
    Revision History
        26 June 2015 - Function created
  *///==========================================================================
  HugeInt& HugeInt::operator-=(const HugeInt& rhs)//number to subtract from self
  {    
    Number answer;
    bool sign;
    
    if (this->positive != rhs.getSign())
    {
      answer = addSameSign(this->value, rhs.getValue());
      sign = this->positive;
    }
    else if (this->positive && rhs.getSign())
    {
      answer = subtractSameSign(this->value, rhs.getValue(), sign);
    }
    else
    {
      answer = subtractSameSign(rhs.getValue(), this->value, sign);
    }
    
    this->positive = sign;
    this->value = answer;
    
    return *this;
  }  
  
  HugeInt& HugeInt::operator*=(const HugeInt& rhs)
  {
    bool sign = this->positive == rhs.getSign();
    
    int shift = 0;
    
    
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
    
    // add negative sign
    if(!number.getSign())
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
        int result = HugeInt::compareSameLength(lhs.getValue(), rhs.getValue());
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
    subtractSameSign
        subtracts two numbers assuming they share the same sign.  Returns the 
        the sign of the answer by reference
        
    Revision History
        30 June 2015 - Function created
  *///==========================================================================
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
  }
  
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
