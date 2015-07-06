// BillParser.cpp

#include <fstream>
#include <algorithm> // any_of, copy, all_of

#include <boost/algorithm/string.hpp> // split, is_any_of
#include <boost/algorithm/string/join.hpp> // join

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
			     ParseOutput& output) // /container for parsed tokens
  {    
    // parse the line as if it's a csv
    Tokens tokens;
    boost::split(tokens, line, boost::is_any_of(","));
        
    // is this a full line
    bool allLinesFull = std::all_of(tokens.begin(), tokens.end(),
				    [](std::string str)
				    {
				      return str.size() != 0;
				    });
    
    // attempt to parse full line or just part of it
    if (allLinesFull)
    {
      output[BillParser::QUANTITY_INDEX] = tokens[BillParser::QUANTITY_INDEX];

      std::string partNumber = tokens[BillParser::PART_INDEX];
      
      // remove spaces from the beginning of the part number
      std::string::iterator partIter = partNumber.begin();
      while (partIter != partNumber.end() &&
	     *partIter == ' ')
      {
	partNumber.erase(partIter++);
      }

      // remove spaces from the beginning of the part number
      partIter = partNumber.end();
      --partIter;
      while (partIter != partNumber.begin() &&
	     *partIter == ' ')
      {
	partNumber.erase(partIter--);
      }
      
      output[BillParser::PART_INDEX] = partNumber;
      
      // determine if the line has a product description
      bool hasQuotes = std::any_of(line.begin(), line.end(),
				   [](char letter)
				   {
				     return letter == '"' ;
				   });
    
      // build description
      std::string description;
      if (hasQuotes)
      {
	// split text around quotations
	Tokens quoteTokens;
	boost::split(quoteTokens, line, boost::is_any_of("\""));
      
	// remove the empty strings
	Tokens::iterator newEnd;
	newEnd = std::remove_if(quoteTokens.begin(), quoteTokens.end(),
				[](std::string str)
				{
				  return str.size() == 0;
				});
      
	// copy the product description from the tokens
	Tokens descriptionParts(newEnd - (quoteTokens.begin() + 1));
	std::copy(quoteTokens.begin()+1, newEnd, descriptionParts.begin());
      
	// stitch the description back together
	description = boost::join(descriptionParts, "\"");
      
	output[BillParser::DESCRIPTION_INDEX] = description;
      }
      else
      {
	output[BillParser::DESCRIPTION_INDEX] = 
	  tokens[BillParser::DESCRIPTION_INDEX];
      }
    }
    else
    {
      output[BillParser::NAME_INDEX] = tokens[BillParser::NAME_INDEX];
    } // if a full line

    return allLinesFull;
    
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
      ParseOutput parsedLine;
      bool goodLine;
      bool isValid;
      int quantity;
      
      // get the name of the bill
      getline(file, line);
      BillParser::cleanLine(line);
      parseLine(line, parsedLine);
      output.name = parsedLine[BillParser::NAME_INDEX];
      std::cout << "Bill Name: " << output.name << std::endl;
      
      // continue parsing till EOF
      int i = 0;
      while (getline(file, line) && i++ < 10)
      {
	cleanLine(line);
	goodLine = parseLine(line, parsedLine);
	isValid = validInt(parsedLine[BillParser::QUANTITY_INDEX].c_str(), quantity);
	//std::cout << "goodLine: " << goodLine << " isValid: " << isValid << std::endl;
	
	// if the line was sucessfully parsed & first value correctly converted
	if (goodLine && isValid)
	{
	  std::cout << ">" << parsedLine[BillParser::QUANTITY_INDEX] << "< >"
	    	    << parsedLine[BillParser::PART_INDEX] << "< >"
	    	    << parsedLine[BillParser::DESCRIPTION_INDEX]
		    << "<" << std::endl;
	  
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
