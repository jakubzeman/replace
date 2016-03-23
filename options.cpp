#include "options.hpp"
#include <iostream>
#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"


Options::Options(int argc, char *argv[])
{
    std::string appName = boost::filesystem::basename(argv[0]);
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "Print usage")
        ("print-duplicities,p", boost::program_options::bool_switch()->default_value(false), "Enables print of duplicities to stdout")
        ("separators,s", boost::program_options::value<std::string>(), "Set separators. Default value are $' \\n'")
        ("input-file", boost::program_options::value< std::vector<std::string> >(), "Path to input file - mandatory argument")
        ("output-file", boost::program_options::value< std::vector<std::string> >(), "Path to output file - mandatory argument")
    ;
    boost::program_options::variables_map vm;
    boost::program_options::positional_options_description positionalOptions;
    positionalOptions.add("input-file", 1);
    positionalOptions.add("output-file", 1);

    try {
        boost::program_options::store(
                boost::program_options::command_line_parser(argc, (const char *const *) argv).
                        options(desc).
                        positional(positionalOptions).
                        run(),
                vm
        );
        if (vm.count("help")) {
            this->printHelp(appName);
            std::cout << desc << std::endl;
            exit(0);
        }
        if (vm.count("input-file")) {
            this->inputFileName = vm["input-file"].as< std::vector<std::string> >()[0];
        }
        if (vm.count("output-file")) {
            this->outputFileName = vm["output-file"].as< std::vector<std::string> >()[0];
        }
    }
    catch (boost::program_options::required_option& e) {
        std::cerr << "Option ERROR: " << e.what() << std::endl << std::endl;
        this->printHelp(appName);
        std::cout << desc << std::endl;
        exit(1);
    }
    catch (boost::program_options::error& e) {
        std::cerr << "Option ERROR: " << e.what() << std::endl << std::endl;
        this->printHelp(appName);
        std::cout << desc << std::endl;
        exit(1);
    }

    if (this->inputFileName.empty()) {
        std::cerr << "Input file is missing" << std::endl << std::endl;
        this->printHelp(appName);
        std::cout << desc << std::endl;
        exit(1);
    }
    if (this->outputFileName.empty()) {
        std::cerr << "Output file is missing" << std::endl << std::endl;
        this->printHelp(appName);
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

void Options::printHelp(const std::string & appName)
{
    std::cout <<
            "Search in the text file for all word or sentence" << std::endl <<
            "duplicities, removes them and saves the text to" << std::endl <<
            "output file" << std::endl << std::endl;

    std::cout << "Usage: " << appName << " [options] <input file> <output file>" << std::endl;
}
