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
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <string>
#include <fstream>

int main (int argc, char* argv[])
{
  // switches to detect input
  bool inputGiven = false;
  bool outputGiven = false;
  bool serialGiven = false;
  std::string inputFilePath;
  std::string outputFilePath;
  std::string serialFilePath;

  // attempt to parse command line arguments
  try
  {
    po::options_description desc("Allowed options");
    desc.add_options()
      ("help,h", "display this help dialog")
      ("input,i", po::value<std::string>(), "path to input file")
      ("output,o", po::value<std::string>(), "path to output file")
      ("serialize,s", po::value<std::string>(),
       "path to serialized object output file");

    po::variables_map vm;        
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);    
    
    if (vm.count("help"))
    {
      std::cout << desc << std::endl;
    }
    
    if (vm.count("input"))
    {
      inputGiven = true;
      inputFilePath = vm["input"].as<std::string>();
      
      std::ifstream inputFile(inputFilePath);
      std::string line;
      while (std::getline(inputFile, line))
      {
        std::cout << ">" << line << "<" << std::endl;
      }
      
      inputFile.close();
    }

    if (vm.count("output"))
    {
      outputGiven = true;
      outputFilePath = vm["output"].as<std::string>();
      std::cout << "Output" << std::endl;
    }

    if (vm.count("serialize"))
    {
      serialGiven = true;
      serialFilePath = vm["serialize"].as<std::string>();
      std::cout << "Serialize" << std::endl;
    }
  }
  catch(std::exception& e) {
    std::cerr << "error: " << e.what() << "\n";
    return 1;
  }
  catch(...) {
    std::cerr << "Exception of unknown type!\n";
  }


  if (inputGiven && (outputGiven || serialGiven))
  {
    
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
