#include <sstream>
#include <algorithm> // for_each

#include "HugeInt.hpp"

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
    
    std::string::const_reverse_iterator strIter = numberStr.rbegin();
    char digit;
    char rawInput;
    while (strIter != numberStr.rend())
    {
      // the value of the character in ascii
      rawInput = static_cast<char>(*strIter);
      
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
      ++strIter;
    }
    
    HugeInt::trimZeros(this->value);

    
    // if there was an error in converting string to number, set to 0
    if (errorOccurred)
    {
      this->value = {0};
      this->positive = true;
    }
  } // HugeInt (string)
  
  /*============================================================================
    HugeInt
        convertion constructor for an int
        
    Revision History
        25 June 2015 - Function created
  *///==========================================================================
  HugeInt::HugeInt (const int value) // number to turn into HugeInt
  {
    // set the sign
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
    Number::const_iterator lhsIter = lhsNum.begin();
    Number::const_iterator rhsIter = rhsNum.begin();
    while (lhsIter != lhsNum.end() ||
           rhsIter != rhsNum.end())
    {
      // get next rhs digit value
      if (rhsIter != rhsNum.end())
      {
        rhsValue = *rhsIter;
        ++rhsIter;
      }
      else
      {
        rhsValue = 0;
      }
      
      // get next lhs digit value
      if (lhsIter != lhsNum.end())
      {
        lhsValue = *lhsIter;
        ++lhsIter;
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
    compareNumbers
        Assumes the the input Numbers both have the same number of digits.
        Returns 0 if the numbers are equal in magnitude, -1 if the second input
        is larger, and 1 if the first input is larger.
        
    Revision History
        28 June 2015 - Function created
  *///==========================================================================
                              // first value to use in comparison
  int HugeInt::compareNumbers(const Number& lhs,
                              // second value to use in comparison
                              const Number& rhs)
  { 
    int result;
    if (lhs.size() == rhs.size())
    {
      // does the lhs or rhs have the larger magnitude of value
      bool lhsLargerMag = false;
      bool rhsLargerMag = false;
      
      // start looking at the most significant digits
      Number::const_reverse_iterator lhsIter = lhs.rbegin();
      Number::const_reverse_iterator rhsIter = rhs.rbegin();
      while (lhsIter != lhs.rend() &&
             rhsIter != rhs.rend())
      {
        if (*lhsIter != *rhsIter)
        {
          if (*lhsIter > *rhsIter)
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
          lhsIter++;
          rhsIter++;
        }
      } // while have digits
      
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
    } // if same length
    else if (lhs.size() > rhs.size())
    {
      result = 1;
    }
    else
    {
      result = -1;
    }
    
    return result;
  } // compareNumbers
  
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
    divideSameSign
        divides two Number typedefs using a naive subtraction only based
        approach. Returns another Number typedef, no sign math is done here.
        While this can technically solve all HugeInt division problems, it is 
        much slower than the long division technique.    
        
    Revision History
    1 July 2015 - Function created
  *///==========================================================================
  Number HugeInt::divideSameSign(const Number& dividend, // number to divide
                                 const Number& divisor) // number to divide by
  {
    // subtract divisor from dividend until remainder is less than zero
    bool isPositive;
    Number count = {0};
    Number remainder = HugeInt::subtractSameSign(dividend, divisor, isPositive);
    
    while (isPositive)
    {
      count = addSameSign(count, {1});
      remainder = HugeInt::subtractSameSign(remainder, divisor, isPositive);
    }
    
    return count;
  }
  
  /*============================================================================
    longDivision
        Solve the division of two Number typedefs by the process of long
        division.  This does not do any sign math and returns another
        Number typedef
        
    Revision History
        2 July 2015 - Function created
  *///==========================================================================
  Number HugeInt::longDivision (Number dividend, // left hand side of division
                                const Number& divisor) // the right hand side
  {
    Number answer = {0};

    // don't do division if the answer will floor to zero
    if (HugeInt::compareNumbers(dividend, divisor) == -1)
    {
      return answer;
    }
    
    Number shiftedCount; // answer to division sub problem
    Number change; // the total amount to change the dividend after a sub problem
    Number section; // the dividend of the shifted division sub problem
    bool sign; // the used sign container needed for the subtraction
    
    do
    {
      // guess correct ten's shift by subtracting number of digits
      int shift = dividend.size() - divisor.size();
      section = Number(dividend.begin()+shift, dividend.end());
      
      // while section < divisor
      while (HugeInt::compareNumbers(section, divisor) == -1)
      {
        --shift;
        section = Number(dividend.begin()+shift, dividend.end());        
      }
      
      // solve the shifted sub division problem
      shiftedCount = HugeInt::divideSameSign(section,
                                             divisor);
      
      // unshift the count back out of the sub problem domain
      Number count(shift, 0);
      for (auto digit : shiftedCount)
      {
        count.push_back(digit);
      }
      
      // add the, now unshifted, count to the answer
      answer = HugeInt::addSameSign(answer, count);
      
      // find the amount to change dividend by
      change = HugeInt::multiplySameSign(count, divisor);
      
      // apply the calculated delta
      dividend = HugeInt::subtractSameSign(dividend, change, sign);
                                               
      // while dividend > divisor
    } while (HugeInt::compareNumbers(dividend, divisor) == 1);
    
    return answer;
  } // long division

  /*============================================================================
    multiplyByInt
        finds the product of a typedef Number and an int, returns it as another
        typedef Number
        
    Revision History
        30 June 2015 - Function created
  *///==========================================================================
  Number HugeInt::multiplyByInt(const Number& number, // Number to multiply
				int single) // single digit to multiply by
  {
    // the output
    Number sum = {0};
    
    // for all the components of the number (1's, 10's , 100's, etc.)
    // multiply them by the single value and then sum them
    Number::const_iterator numIter;
    int tensShift = 0;
    for(numIter = number.begin(); numIter != number.end(); ++numIter)
    {
      // pads the beggin
      Number withPadding(tensShift, 0);
      
      // multiply just the digit and single, return the digitized version
      Number endValue = HugeInt::digitizeInt(*numIter *  single);

      // append newly calculated digits to the padding
      for (auto digit : endValue)
      {
	withPadding.push_back(digit);
      }      
      
      sum = HugeInt::addSameSign(sum, withPadding);
      
      ++tensShift;
    }
    
    return sum;
    
  }
  
  /*============================================================================
    multiplySameSign
        Multiplies two Number typedefs using the long multiplication method.
        Returns another Number typedef, no sign math done here.
        
    Revision History
        30 June 2015 - Function created
  *///==========================================================================
  Number HugeInt::multiplySameSign(const Number& lhs, // left hand side number
                                   const Number& rhs) // right hand side number
  {
    Number sum = {0};
    
    // tens place shift count
    int shift = 0;
    
    // for every digit the this number
    Number::const_iterator lhsIter;
    for (lhsIter = lhs.begin(); lhsIter != lhs.end(); ++lhsIter)
    {
      // shift the right hand number
      Number work(shift, 0);  
      for (auto digit : rhs)
      {
	work.push_back(digit);
      }
      
      // multiply the shifted value by the current digit of this
      // then add the result to the answer
      sum = HugeInt::addSameSign(sum, HugeInt::multiplyByInt(work, *lhsIter));
      
      // shift to the next "tens" place
      ++shift;
    }
    
    // trim extra zeros
    HugeInt::trimZeros(sum);
    
    return sum;
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
    
    Number product = multiplySameSign(this->value, rhs.getValue());
    
    bool sign;
    // check if the answer is 0 and make it positive if true
    if (product.size() == 1 and product[0] == 0)
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
    this->value = product;
    
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
    
    // due to potentially big number, use long division method
    Number quotient = HugeInt::longDivision(this->getValue(), rhs.getValue());
    
    bool sign;
    // check if the answer is 0 and make it positive if true
    if (quotient.size() == 1 && quotient[0] == 0)
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
    this->value = quotient;
    
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
    int result = HugeInt::compareNumbers(lhs.getValue(), rhs.getValue());
    return result == 0 && lhs.isPositive() == rhs.isPositive();
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
      int result = HugeInt::compareNumbers(lhs.getValue(), rhs.getValue());
      
      // if rhs has larger magnitude
      if (result == -1)
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
      // if they have equal magnitudes
      else if (result == 0)
      {
        // since signs must be equal, they must be equal
        isSmaller = false;
      }
      // if lhs has larger magnitude
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
      }
    } // if signs don't match
    
    return isSmaller;
  } // operator<
    
  /*============================================================================
    subtractSameSign
        subtracts two numbers assuming they share the same sign.  Returns the 
        the sign of the answer by reference
        
    Revision History
        30 June 2015 - Function created
  *///==========================================================================
  Number HugeInt::subtractSameSign(const Number& lhs, // left hand number
				   const Number& rhs, // right hand number
				   bool& sign) // returns sign after operation
  {
    // figure out if the inputs should be reordered
    // switch ordering of numbers if rhs > lhs
    bool shouldSwitch = HugeInt::compareNumbers(lhs, rhs) == -1;
    int result = HugeInt::compareNumbers(lhs, rhs);

    // possibly reorder and assign sign
    Number topNumber;
    Number bottomNumber;
    if (shouldSwitch)
    {
      topNumber = rhs;
      bottomNumber = lhs;
      
      sign = false;
    }
    else
    {
      topNumber = lhs;
      bottomNumber = rhs;
      
      sign = true;
    }
    
    // if numbers are equal make answer 0
    // this exploits the std::vector == overload
    Number answer;
    if (lhs == rhs)
    {
      answer = {0};
    }
    // perform full subtraction method
    else
    {
      int difference;
      int borrow = 0;
      Number::iterator topIter = topNumber.begin();
      Number::iterator bottomIter = bottomNumber.begin();
      while (topIter != topNumber.end())
      {
        // get next digit for top number
        int topVal;
        if (topIter != topNumber.end())
        {
          topVal = *topIter;
          ++topIter;
        }
        else
        {
          // if no next digit, use zero
          topVal = 0;
        }
        
        // get next digit for bottom number
        int botVal;
        if (bottomIter != bottomNumber.end())
        {
          botVal = *bottomIter;
          ++bottomIter;
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
    
    HugeInt::trimZeros(answer);
    
    return answer;
  } // subtractSameSign
  
  /*============================================================================
    trimZeros
        takes a number and trims the leading 0s off of it
        
    Revision History
        25 June 2015 - Function created
  *///==========================================================================
  void HugeInt::trimZeros(Number& number) // the number to trim zeros from
  {
    // trim leading zeros, except if the number is just 0
    Number::iterator digitIter = number.end();
    --digitIter;
    while (*digitIter == 0 && digitIter != number.begin())
    {
      number.erase(digitIter);
      --digitIter;
    }
  }
  
} // namespace hw4
