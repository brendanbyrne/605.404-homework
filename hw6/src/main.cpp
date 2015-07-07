#include <iostream>

#include "TimelineParser.hpp"

int main(int argc, char** argv)
{
  hw6::TimelineParser parser;
  hw6::Timeline timeline;
  
  timeline = parser.parse("../csv/HW6-Elevators.csv");
  
  for(auto passenger : timeline)
    std::cout << passenger << std::endl;

  return 0;
}
