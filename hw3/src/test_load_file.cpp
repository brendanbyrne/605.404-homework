#include <iostream>
#include <fstream>
#include <string>

#include <boost/algorithm/string.hpp>

int main()
{
  std::string filePath = "histories/asps.csv";

  std::ifstream inputFile(filePath);
    
  std::string line;
  
  while (std::getline(inputFile, line))
  {
    std::cout << ">" << line << "<" << std::endl;
  }
  
  inputFile.close();
  return 0;
}
