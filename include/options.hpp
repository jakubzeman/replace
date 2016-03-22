#ifndef OPTIONS_H
#define OPTIONS_H
#include <string>

class Options {
    std::string inputFileName;
    std::string outputFileName;
    std::string separators;
    bool printDuplicities;
public:
    Options(int argc, char *argv[]);
    const std::string & getInputFileName() const { return this->inputFileName; }
    const std::string & getOutputFileName() const { return this->outputFileName; }
    const std::string & getSeparators() const { return this->separators; }
    bool printDuplicitiesEnabled() const { return this->printDuplicities; }
    void printHelp(const std::string & appName);
};

#endif
