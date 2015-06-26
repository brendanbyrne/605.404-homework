#include <sstream>

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
  HugeInt::HugeInt (const std::string& value)
  {
    std::string::const_iterator strIT;
    for (strIT = value.begin(); strIT < value.end(); ++strIT)
    {
      std::cout << *strIT << std::endl;
    }

    this->value = value;
  }
  
  /*============================================================================
    HugeInt
        convertion constructor for an int
	
    Revision History
        25 June 2015 - Function created
  *///==========================================================================
  HugeInt::HugeInt (const int value)
  {
    this->value = std::to_string(value);
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
    std::string valueStr = number.getValue();
    std::string::const_iterator strIT = valueStr.begin();
    
    std::stringstream ss;

    int leftOver = valueStr.length()%3;
    
    ss << valueStr;
    
    out << ss.str();
    
    return out;
  }

} // namespace hw4
