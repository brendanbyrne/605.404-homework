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

namespace hw4
{
  
  typedef std::vector<char> Number;
  
  class HugeInt
  {
    
  public:
    HugeInt(const Number& value = {0},
            bool positive = true); // constructor
    HugeInt(const int value); // convertion constructor
    
    bool getSign() const; // positive data member getter
    Number getValue() const; // value data member getter
    void setSign(const bool positive); // positive data member setter
    void setValue(const Number& value); // value data member setter
    
    HugeInt& operator+=(const HugeInt& rhs);
    
  private:
    Number value; // the vectored digits of the number
    bool positive; // sign of the number, positive is true
    
    static Number subtractSameSign(const Number& lhsNum, 
                                   const Number& rhsNum,
				   bool& sign);
    static Number addSameSign(const Number& lhsNum, 
                              const Number& rhsNum);
      
  }; // class HugeInt

  /*============================================================================
    getSign
        return the sign of the number, true is positive
	
    Revision History
        26 June 2015 - Function created
  *///==========================================================================                 
  inline bool HugeInt::getSign() const
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
  
  int isLarger(const Number& lhs, const Number& rhs);

  std::ostream& operator<<(std::ostream& out, const HugeInt& value);
  bool operator==(const HugeInt& lhs, const HugeInt& rhs);
  bool operator<(const HugeInt& lhs, const HugeInt& rhs);
  
  inline HugeInt operator+(HugeInt lhs, const HugeInt& rhs)
  {
    lhs += rhs;
    return lhs;
  }

} // namespace hw4

#endif // HUGEINT_HPP
