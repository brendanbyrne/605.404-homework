/*==============================================================================
 
  Author: Brendan Byrne
  
  Date: 07 July, 2015
  
  main.cpp
  
  Author: Brendan Byrne
  
  Inputs: The paths to the bill of material csv files
    
  Outputs: For each of the desired part numbers it outputs the part number, it's
           description, all the kits that this part is used in, and quantity of 
           parts needed to full each bill of materials.  
*///============================================================================

#include <iostream>
#include <map>
#include <algorithm> // remove_if

#include "BillParser.hpp"
#include "Part.hpp"

// useful to contain the variable name bloat
//               part number, Part object
typedef std::map<std::string, hw5::Part> PartMap;

int main(int argc, char** argv)
{
  
  // if you don't have and files to check, simply exit
  if (argc < 2)
  {
    return 0;
  }
  
  // get list of file paths for the different bill of materials
  std::vector<std::string> filenames;  
  for (int index = 1; index < argc; ++index)
  {
    filenames.push_back(argv[index]);
  }
  
  // basic sanitizing of the inputs
  std::vector<std::string>::iterator filenamesEnd;
  filenamesEnd = std::remove_if(filenames.begin(), filenames.end(),
                                [](std::string name) -> bool
                                {
                                  bool shouldRemove = false;
                                  int location;
                                  
                                  // if file is temporary (emacs)
                                  location = name.find("~");
                                  if (!shouldRemove &&
                                      location != std::string::npos)
                                  {
                                    shouldRemove = true;
                                  }
                                  
                                  // if file is not a csv
                                  location = name.find(".csv");
                                  if (!shouldRemove &&
                                      location == std::string::npos)
                                  {
                                    shouldRemove = true;
                                  }
                                  
                                  return false;
                                });

  hw5::BillParser bp; // the parser
  hw5::BillOutput parserOutput; // container to hold output of parsing
  PartMap partMap; // contains all part information
  
  PartMap::iterator partIter;
  
  // for each bill
  for (std::vector<std::string>::iterator nameIter = filenames.begin();
       nameIter != filenamesEnd;
       ++nameIter)
  {
    // parse the csv
    parserOutput = bp.parse(*nameIter);
    
    // for each line of the bill of materials
    for (auto keyVal : parserOutput.materialList)
    {      
      partIter = partMap.find(keyVal.first);
      // if part# in map
      if (partIter != partMap.end())
      {  
        // add bill of materials/quantity pair
        partIter->second.addToKits({parserOutput.name, keyVal.second.first});
      }
      else
      {
        // create part
        hw5::Part part(keyVal.first, keyVal.second.second);
        
        // add pair
        part.addToKits({parserOutput.name, keyVal.second.first});
        
        // add part to map
        partMap.insert(partIter, {keyVal.first, part});
      }
    }
  }
  
  // print info for required parts
  std::vector<std::string> partsToCheck = {"Bolt-SKT",
                                           "FH-2",
                                           "CCW-5E3",
                                           "Nut-#8-32",
                                           "W025130 (EU)",
                                           "12A150A-50",
                                           "6N-4",
                                           "MFR220K-.5",
                                           "#8 sheet metal screw",
                                           "PJP-S"};
  
  // test each of the parts to see which bill of materials they appear in
  for (auto partNumber : partsToCheck)
  { 
    partIter = partMap.find(partNumber);
    
    if (partIter != partMap.end())
    {      
      std::cout << partIter->second << std::endl;
    }
    else
    {
      std::cout << "Part number: " << partNumber << " not found" << std::endl;
    }
  }
} // main function
