#include <iostream>

#include "QuestionClass.hpp"
int main()
{
  hw2::QuestionClass foo(hw2::QuestionClass::Foo::VALUE);
  std::cout << foo.str() << std::endl; // should output "value"
  
  return 0;
}
