/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 4 July, 2015
  
  Revision History
      4 July, 2015 - class created
  
  Class Name: BillParser
  
  Intent: Parse a bill of materials csv and extract the product information
  
  Description: This class handles all the 

*///============================================================================

#ifndef BILLPARSER_HPP
#define BILLPARSER_HPP

#include <string>
#include <map>
#include <utility>
#include <vector>

namespace hw5
{
  
  typedef std::map<std::string, std::pair<int, std::string> > MaterialMap;
  typedef std::vector<std::string> Tokens;
  typedef std::array<std::string, 3> ParseOutput;
  
  // struct to help capture to the multiple outputs of the parsing function
  struct BillOutput
  {
    std::string name;
    MaterialMap materialList;
  };

  class BillParser
  {

    
  public:
    // parse bill of material at filepath
    BillOutput parse(const std::string& filepath);
    
  private:
    bool fileFlag; // flag for if error raised during parsing
    
    void cleanLine(std::string& line); // erase the carriage return from line
    
    // parse a line from a bill of materials
    bool parseLine(const std::string& line,
			  ParseOutput& output);
    
    bool validInt(const char* input, int& output);

    // locations of information in tokens vector
    static const int NAME_INDEX = 0;
    static const int QUANTITY_INDEX = 0;
    static const int PART_INDEX = 1;
    static const int DESCRIPTION_INDEX = 2;
    
  }; // class BillParser

} // namespace HW5

#endif // BILLPARSER_HPP
