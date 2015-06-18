/*==============================================================================
  main.cpp
  Author: Brendan Byrne
  Inputs: path to file containing google formatted financial history
          path to where output file should be saved
  
  Options: -h [--help] displays help information
           -i [--input] path to an input file
           -o [--output] f path to an output file           
           -s [--serialize] path to an output file where a MACD object will be
                            serialized to
  
  Outputs: a file containing the moving average convergence divergence data for
           the given input stock price history

   usage: macd -i /path/to/input/data.csv -o /path/to/desired/output.csv
          macd -i /path/to/input/data.csv -s /path/to/serialized/output.serial
*///============================================================================
#include <iostream>
#include <string>
#include <fstream>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "GoogleHistoryParser.hpp"

int main (int argc, char* argv[])
{  
  // switches to detect input
  bool inputGiven = false;
  bool outputGiven = false;
  bool serialGiven = false;
  
  po::variables_map vm;
  
  // attempt to parse command line arguments
  try
  {
    po::options_description help_menu("Allowed options");
    help_menu.add_options()
      ("help,h", "display this help dialog")
      ("input,i", po::value<std::string>(), "path to input file")
      ("output,o", po::value<std::string>(), "path to output file")
      ("serialize,c", po::value<std::string>(),
       "path to serialized object output file")
      ("fast,f", po::value<int>()->default_value(12),
       "set the number of days to look back for the fast EMA, defaults to 12")
      ("slow,s", po::value<int>()->default_value(26),
       "set the number of days to look back for the slow EMA, defaults to 26")
      ("signal,g", po::value<int>()->default_value(9),
       "set the number of days to look back for the signal, defaults to 9");

    
    po::store(po::parse_command_line(argc, argv, help_menu), vm);
    po::notify(vm);    
    
    if (vm.count("help"))
    {
      std::cout << help_menu;
      
      // do not attempt anything else, simply return
      return 0;
    }

    // given an input file
    if (vm.count("input"))
    {
      inputGiven = true;
    }

    // given an output file
    if (vm.count("output"))
    {
      outputGiven = true;
    }

    // given a file to serialize to
    if (vm.count("serialize"))
    {
      serialGiven = true;
    }
  }
  catch(std::exception& e) {
    std::cerr << "error: " << e.what() << "\n";
    return 1;
  }
  catch(...) {
    std::cerr << "Exception of unknown type!" << "\n";
  }

  // check if there was enough information given
  if (inputGiven && (outputGiven || serialGiven))
  {
    std::string inputFilePath  = vm["input"].as<std::string>();
    
    hw3::GoogleHistoryParser parser;

    hw3::PriceHistory ph = parser.parse(inputFilePath);
    
    // check if the parsing was successful
    if (parser.wasSuccessful())
    {
      for (auto i : ph)
      {
        std::cout << i << std::endl;
      }
      
      int fastEMA = vm["fast"].as<int>();
      int slowEMA = vm["slow"].as<int>();
      int signal  = vm["signal"].as<int>();

      hw3::MACD macd(fastEMA, slowEMA, signal);
  
      // generate MACD data
      if (outputGiven)
      {
        std::string outputFilePath = vm["output"].as<std::string>();
        // write out
      }
      
      if (serialGiven)
      {
        std::string serialFilePath = vm["serialize"].as<std::string>();
        // serial out
      }
    }
    else
    {
      std::cout << "Unable to parse pricing history!" << std::endl;
    }
  }
  else
  {
    if (!inputGiven)
    {
      std::cout << "No input file given" << std::endl;
    }
    if (!outputGiven && !serialGiven)
    {
      std::cout << "No output or serial path given" << std::endl;
    }
  }
  
  return 0;
} // main
