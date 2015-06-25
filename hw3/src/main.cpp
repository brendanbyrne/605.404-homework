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
#include <algorithm>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <boost/date_time/gregorian/gregorian.hpp>
namespace greg = boost::gregorian;

#include "GoogleHistoryParser.hpp"
#include "MACD.hpp"

int main (int argc, char* argv[])
{  
  // switches to detect input
  bool inputGiven = false;
  
  // attempt to parse command line arguments
  po::variables_map vm;
  try
  {
    // initialize the input options
    po::options_description help_menu("Allowed options");
    help_menu.add_options()
      ("help,h", "display this help dialog")
      ("input,i", po::value<std::string>(), "path to input file")
      ("fast,f", po::value<int>()->default_value(12),
       "set the number of days to look back for the fast EMA, defaults to 12")
      ("slow,s", po::value<int>()->default_value(26),
       "set the number of days to look back for the slow EMA, defaults to 26")
      ("signal,g", po::value<int>()->default_value(9),
       "set the number of days to look back for the signal, defaults to 9");
    
    // parse the input options
    po::store(po::parse_command_line(argc, argv, help_menu), vm);
    po::notify(vm);    
    
    // if help is requested
    if (vm.count("help"))
    {
      std::cout << help_menu;
      return 0; // do not attempt anything else, simply return
    }

    // given an input file
    if (vm.count("input"))
    {
      inputGiven = true;
    }

  }
  catch(std::exception& e) {
    std::cerr << "error: " << e.what() << "\n";
    return 1;
  }
  catch(...) {
    std::cerr << "Exception of unknown type!" << "\n";
  } // try to read the input options

  // check if there was enough information given
  if (inputGiven)
  {
    std::string inputFilePath  = vm["input"].as<std::string>();
    
    hw3::GoogleHistoryParser parser;
    hw3::PriceHistory priceHistory = parser.parse(inputFilePath);
    
    // check if the parsing was successful
    if (parser.wasSuccessful())
    {
      // settings for the MACD analysis
      int fastEMA = vm["fast"].as<int>();
      int slowEMA = vm["slow"].as<int>();
      int signal  = vm["signal"].as<int>();
      
      // perform the MACD analysis
      hw3::MACD macd(fastEMA, slowEMA, signal);
      hw3::FullAnalysis analysis = macd.analyze(priceHistory);
      
      std::cout << "Analysis size: " << analysis.size() << std::endl;

      hw3::FullAnalysis::const_iterator entry;
      
      // search the analysis for entry pertaining june 1st 2015
      greg::date june1st(2015,06,01);
      entry = std::find_if(analysis.begin(), analysis.end(),
			   [&june1st](const hw3::AnalysisEntry& entry) -> bool
			   {
			     return entry.getDate() == june1st;
			   });
      
      // std::string outputFilePath = inputFilePath + ".out";
      // try
      // {
      //   std::ofstream ofile(outputFilePath);
      //   for (auto i : analysis)
      //   {
      //     ofile << i << "\n";
      //   }
      //   ofile.close();
      // }
      // catch (...)
      // {
      //   std::cout << "Cannot write to output file" << std::endl;
      // }

      // attempt to output the macd of the stock on 1 June, 2015
      if (entry != analysis.end())
      {
	std::cout << entry->getMACD() << std::endl;
      }
      else
      {
	std::cout << "No data for June 1st, 2015 found." << std::endl;
      }

    }
    else
    {
      std::cout << "Unable to parse pricing history!" << std::endl;
    } // if success parsing
  }
  else
  {
    std::cout << "No input file given" << std::endl;
  } // if input given
  
  return 0;
} // main