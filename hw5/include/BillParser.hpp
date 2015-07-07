/*==============================================================================
  
  Author: Brendan Byrne
  
  Date: 4 July, 2015
  
  Revision History
      4 July, 2015 - class created
  
  Class Name: BillParser
  
  Intent: Parse a bill of materials csv and extract the product information
  
  Description: This class handles all the parsing a bill of materials and
               returns the type of part, it's description, and the amount needed
               for all parts in the bill.

*///============================================================================

#ifndef BILLPARSER_HPP
#define BILLPARSER_HPP

#include <string>
#include <map>
#include <utility>
#include <vector>

namespace hw5
{
  //               part nubmer       quantity, description
  typedef std::map<std::string, std::pair<int, std::string> > MaterialMap;
  
  typedef std::vector<std::string> Tokens;
  typedef std::array<std::string, 3> ParseOutput;
  
  // struct to help capture to the multiple outputs of the parsing function
  struct BillOutput
  {
    std::string name; // name of the bill of materials
    MaterialMap materialList; // list of items in the kit
  };

  class BillParser
  {    
  public:
    // parse bill of material at filepath
    BillOutput parse(const std::string& filepath);
    bool getFlag();
    
  private:
    // locations of information in tokens vector
    static const int NAME_INDEX = 0;
    static const int QUANTITY_INDEX = 0;
    static const int PART_INDEX = 1;
    static const int DESCRIPTION_INDEX = 2;
    
    bool fileFlag; // flag for if error raised during parsing
    
    void cleanLine(std::string& line); // erase the carriage return from line
    
    // parse a line from a bill of materials
    bool parseLine(const std::string& line,
			  ParseOutput& output);
    
    // attempt to convert an string to an int, returns if it was successful
    bool validInt(const std::string& input, int& output);
    
  }; // class BillParser
  
  /*============================================================================
    getFlag
        returns the state of the error flag. false means that no flag was raised
        
    Revision History
        6 July 2015 - Function created
  *///==========================================================================
  inline bool BillParser::getFlag()
  {
    return this->fileFlag;
  }
  
} // namespace HW5

#endif // BILLPARSER_HPP
