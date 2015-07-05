// BillParser.cpp

#include <fstream>
#include <algorithm> // any_of

#include <boost/algorithm/string.hpp> // split, is_any_of

#include "BillParser.hpp"

// testing only
#include <iostream>


namespace hw5
{
  /*============================================================================
    cleanLine
        removes unwanted characters from the line

    Revision History
        4 July, 2015 - function created
  *///==========================================================================
  void BillParser::cleanLine(std::string& line) // the line to try to clean
  {    
    // delete carriage return
    if (std::any_of(line.begin(), line.end(),
		    [](char str)
		    {
		      return str == '\r';
		    }))
    {
      line.pop_back();
    }
  }
  
  /*============================================================================
    parseLine
        parse a line of text around comma delimiters and return a status of true
	if all fields are not empty

    Revision History
        4 July, 2015 - function created
  *///==========================================================================
  bool BillParser::parseLine(const std::string& line,  // the line to parse
			     Tokens& tokens) // container for parsed tokens
  {    
    // determine if the line has a product description
    bool hasDescription = std::any_of(line.begin(), line.end(),
				      [](char letter)
				      {
					return letter == '"';
				      });
    
    std::string delimiters;
    std::string description;
    
    // parse the description section if it ex
    if (hasDescription)
    {
      delimiters = "\"";
      Tokens descripTokens;
      boost::split(descripTokens, line, boost::is_any_of(delimiters));
      
      // extract the part description from the tokens
      description = descripTokens[1];
    }
    
    // parse the line around commas
    delimiters = ",";
    boost::split(tokens, line, boost::is_any_of(delimiters));
    
    if (hasDescription)
    {
      tokens[2] = description;
    
    
      // remove extra whitespace from product number
      std::string::iterator strIter;
      std::cout << "tokens[1]: >" << tokens[1] << "<" << std::endl;
      for (strIter = tokens[1].begin(); strIter != tokens[1].end(); ++strIter)
      {
	if (*strIter == ' ')
	{
	  tokens[1].erase(strIter);
	}
      }
    }
    
    return hasDescription;
  } // parseLine
  
  /*============================================================================
    parse
        parse a csv file containing the bill of materials for a particular kit.
	the output is a struct containing the name and data of the kit

    Revision History
        4 July, 2015 - function created
  *///==========================================================================
  BillOutput BillParser::parse(const std::string& filePath) // path to bill file
  {
    // Initialize the output container
    BillOutput output;
    
    // reset the error flags
    this->fileFlag = false;
    
    // attempt to open the input csv file
    std::ifstream file(filePath);
    
    if (file)
    {
      // variables used in parsing
      std::string line;
      Tokens parsedLine;
      bool goodLine;
      int quantity;
      
      // get the name of the bill
      getline(file, line);
      BillParser::cleanLine(line);
      parseLine(line, parsedLine);
      output.name = parsedLine[0];
      
      // continue parsing till EOF
      int j = 0;
      while (getline(file, line) && j++ < 5)
      {
	cleanLine(line);
	goodLine = BillParser::parseLine(line, parsedLine);
	
	for (auto i : parsedLine)
	{
	  std::cout << ">" << i << "<" << std::endl;
	}

	if (goodLine && BillParser::validInt(parsedLine[0].c_str(), quantity))
	{
	  std::cout << "size: " << parsedLine.size() << std::endl;
	  
	  // clean the product description
	  cleanLine(parsedLine[2]);
	  
	  //output.materialList
	}
      }
      
    }
    else
    {
      this->fileFlag = true;
    } // if file opened

    return output;
  } // parse

  /*============================================================================
    validInt
        attempt to convert a string to an int, returning whether or not it was
	success.  The number itself is returned by reference

    Revision History
        4 July, 2015 - function created
  *///==========================================================================
  bool BillParser::validInt(const char* input,
			    int& output)
  {
    bool successful;
    
    // attempt to convert a string to an int
    output = std::atoi(input);
    
    if (output != 0)
    {
      successful = true;
    }
    else
    {
      successful = false;
    }
        
    return successful;
  }

} // namespace hw5
