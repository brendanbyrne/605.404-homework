/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 25 June, 2015
  
  Revision History
      25 June, 2015 - class created
  
  Class Name: HugeInt
  
  Intent: Allow integer operations for an number of unlimited size
  
  Description: The value of the number that a HugeInt holds is represented as a
               series of digits in a std::deque.  Lower index numbers are higher
               in order of magnitude.  A conversion constructor for the int type
               is provide to add in working with

*///============================================================================

#ifndef HUGEINT_HPP
#define HUGEINT_HPP

#include <vector>
#include <ostream>
#include <string>

namespace hw4
{
  
  typedef std::vector<char> Number;
  
  class HugeInt
  {
    // The base of the number system, demical -> 10
    static const int BASE = 10;

  public:
    explicit HugeInt(const std::string& numberStr = "0"); // string
    HugeInt(const int value); // convertion constructor
    
    // comparison between two numbers of the SAME number of digits
    // returns -1 if lhs  < rhs
    //          0 if lhs == rhs
    //          1 if lhs  > rhs
    static int compareSameLength(const Number& lhs, const Number& rhs);

    bool isPositive() const; // positive data member getter
    Number getValue() const; // value data member getter
    void setSign(const bool positive); // positive data member setter
    void setValue(const Number& value); // value data member setter
    
    // unary operator overloads
    HugeInt& operator+=(const HugeInt& rhs);
    HugeInt& operator-=(const HugeInt& rhs);
    HugeInt& operator*=(const HugeInt& rhs);
    HugeInt& operator/=(const HugeInt& rhs);
    
  private:
    Number value; // the vectored digits of the number, {lower -> higher}
    bool positive; // sign of the number, positive is true
    
    // addition backend
    static Number addSameSign(const Number& lhsNum, 
                              const Number& rhsNum);

    // turns int into aliased Number type
    static Number digitizeInt(int toBeDigitize);

    static Number subtractSameSign(const Number& lhsNum, 
                                   const Number& rhsNum,
				   bool& sign); // subtraction backend
    
    // newNumber = number * single
    static Number multiplyByInt(const Number& number, int single);
    
  }; // class HugeInt
  
  /*============================================================================
    getSign
        return the sign of the number, true is positive
	
    Revision History
        26 June 2015 - Function created
  *///==========================================================================                 
  inline bool HugeInt::isPositive() const
  {
    return this->positive;
  }
  
  /*============================================================================
    getValue
        return the value of the value data member
	
    Revision History
        25 June 2015 - Function created
  *///==========================================================================                 
  inline Number HugeInt::getValue() const
  {
    return this->value;
  }
  
  // binary operator overloads
  std::ostream& operator<<(std::ostream& out, const HugeInt& value);
  bool operator==(const HugeInt& lhs, const HugeInt& rhs);
  bool operator<(const HugeInt& lhs, const HugeInt& rhs);
  
  /*============================================================================
    operator>
        binary greater than operator overload
        
    Revision History
        1 July 2015 - Function created
  *///==========================================================================
  inline bool operator>(const HugeInt& lhs, // left hand number
                        const HugeInt& rhs) // right hand number
  {
    return operator<(rhs, lhs);
  }

  /*============================================================================
    operator+
        binary addition operator overload
        
    Revision History
        26 June 2015 - Function created
  *///==========================================================================
  inline HugeInt operator+(HugeInt lhs, // left hand number
                           const HugeInt& rhs) // right hand number
  {
    lhs += rhs;
    return lhs;
  }
  
  /*============================================================================
    operator-
        binary subtraction operator overload
        
    Revision History
        30 June 2015 - Function created
  *///==========================================================================
  inline HugeInt operator-(HugeInt lhs, // left hand number
                           const HugeInt& rhs) // right number
  {
    lhs -= rhs;
    return lhs;
  }

  /*============================================================================
    operator*
        binary multiplication operator overload for 2 HugeInts
        
    Revision History
        30 June 2015 - Function created
  *///==========================================================================
  inline HugeInt operator*(HugeInt lhs, // left hand number
                           const HugeInt& rhs) // right number
  {
    lhs *= rhs;
    return lhs;
  }
  
  /*============================================================================
    operator/
        binary division operator overload for 2 HugeInts
        
    Revision History
        30 June 2015 - Function created
  *///==========================================================================
  inline HugeInt operator/(HugeInt lhs, // left hand number
                           const HugeInt& rhs) // right number
  {
    lhs /= rhs;
    return lhs;
  }
  
  /*============================================================================
    setSign
        set the sign of the number, true is positive
	
    Revision History
        26 June 2015 - Function created
  *///==========================================================================
                               // desired sign for the huge int
  inline void HugeInt::setSign(const bool sign)
  {
    this->positive = sign;
  }
  
  /*============================================================================
    setValue
        set the value of the value data member
	
    Revision History
        25 June 2015 - Function created
  *///==========================================================================
                                // desired value for the huge int
  inline void HugeInt::setValue(const Number& value)
  {
    this->value = value;
  }

  // remove leading zeros from a number
  void trimZeros(Number& number);

} // namespace hw4

#endif // HUGEINT_HPP
