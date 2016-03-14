#include "options.hpp"
#include <iostream>
#include <stdlib.h>

Options::Options(int argc, char *argv[])
{
    if (argc >= 1) {
        this->programName = argv[0];
    }
    switch (argc) {
    case 3:
        this->inputFileName = argv[1];
        this->outputFileName = argv[2];
        break;
    default:
        this->printHelp();
        exit(1);
        break;
    }
}

void Options::printHelp()
{
    std::cout << "Usage: " << std::endl;
    std::cout << this->programName << " <path to input text file> <path to output file name>" << std::endl;
    std::cout << "Search in the text file for all word or sentence duplicities, removes them and saves the text to output file" << std::endl; 
}

