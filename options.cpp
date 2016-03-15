#include "options.hpp"
#include <iostream>
#include <stdlib.h>
#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"

Options::Options(int argc, char *argv[])
{
    std::string appName = boost::filesystem::basename(argv[0]);
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "Print usage")
        ("print-duplicities,p", po::value<bool>(), "Enables print of duplicities to stdout")
        ("separators,s", po::value<std::string>(), "Set separators. Default values are \" \\n\"")
        ("input-file", po::value<std::string>(&this->inputFileName)->required(), "Path to input file - mandatory option")
        ("output-file", po::value<std::string>(&this->outputFileName)->required(), "Path to output file - mandatory option")
    ;
    po::positional_options_description positionalOptions;
    positionalOptions.add("input-file", 1);
    positionalOptions.add("output-file", 1);
    po::variables_map vm;

    try {
        po::store(po::command_line_parser(argc, argv).options(desc).positional(positionalOptions).run(), vm);
        if (vm.count("help")) {
            this->printHelp();
            std::cout << desc << std::endl;
            exit(0);
        }
    }
    catch (boost::program_options::required_option& e) {
        std::cerr << "Option ERROR: " << e.what() << std::endl << std::endl;
        this->printHelp();
        std::cout << desc << std::endl;
        exit(1);
    }
    catch (boost::program_options::error& e) {
        std::cerr << "Option ERROR: " << e.what() << std::endl << std::endl;
        this->printHelp();
        std::cout << desc << std::endl;
        exit(1);
    }

    if (this->inputFileName.empty() || this->outputFileName.empty()) {
        std::cerr << "Required args are missing" << std::endl << std::endl;
        this->printHelp();
        std::cout << desc << std::endl;
        exit(1);
    }

    if (vm.count("separators")) {
        this->separators = vm["separators"].as<std::string>();
    }
    else {
        this->separators = " \n";
    }
    if (vm.count("print-duplicities")) {
        this->printDuplicities = vm["print-duplicities"].as<bool>();
    }
    else {
        this->printDuplicities = false;
    }
}

void Options::printHelp()
{
    std::cout << "Search in the text file for all word or sentence duplicities, removes them and saves the text to output file" << std::endl; 
}

