#ifndef QUESTION_CLASS_HPP
#define QUESTION_CLASS_HPP

#include <string>
#include <map>
#include <boost/assign/list_of.hpp> // for 'map_list_of'

namespace hw2
{
  class QuestionClass
  {
  public:
    enum class Foo {VALUE};
    
    typedef std::map<Foo, std::string> FooMap;
    
    QuestionClass(Foo);
    std::string str() const;
    
  private:
    
    static const FooMap fooToStr1;// = boost::assign::map_list_of(Foo::VALUE, "value");
    
    //static const FooMap fooToStr2; = { {Foo::VALUE,  "value"} };
    
    //static const FooMap fooToStr3;// { {Foo::VALUE, "value"} };
  
    
    Foo bar;
    
    
  }; //QuestionClass

} // namespace hw2

#endif // QUESTION_CLASS_HPP
