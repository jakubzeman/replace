#ifndef OPTIONS_H
#define OPTIONS_H
#include <string>

class Options {
    std::string inputFileName;
    std::string outputFileName;
    std::string programName;
public:
    Options(int argc, char *argv[]);
    const std::string & getInputFileName() const {return this->inputFileName;}
    const std::string & getOutputFileName() const {return this->outputFileName;}
    void printHelp();
};

#endif
