#include "QuestionClass.hpp"

namespace hw2
{
  QuestionClass::QuestionClass(Foo bar_value):
    bar(bar_value), fooToStr1({ {Foo::VALUE, "value" } })
  {
  }
  
  std::string QuestionClass::str() const
  {
    return QuestionClass::fooToStr1.at(this->bar);
  }
  
  
  
}; // namespace hw2
