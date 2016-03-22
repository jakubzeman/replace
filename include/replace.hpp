#ifndef REPLACE_H
#define REPLACE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "options.hpp"

struct ReadBuffer {
    std::string noSep; // buffer without separators
    std::string output; // buffer with separators

};

class Replace {
    static std::string WORD_SEPARATORS;
    bool printDuplicities;
    std::ifstream inputFile;
    std::ofstream outputFile;

    struct ReadBuffer readBuffer;
    struct ReadBuffer compareBuffer;

    std::string rollBackBufferFirst;
    std::vector <std::string> rollBackBuffer;

    void processFile(const std::string & file);
    void processOneWord(const std::string & word);
    bool isSeparator(const std::string & word);
    void processStartup(const std::string & word);
    void processSeparator(const std::string & word);
    void cleanUpWhenNoDuplicity();
    void cleanUpWhenDuplicityFound();
public:

    Replace(const Options & options);
    virtual ~Replace();
    void replace();
};

#endif

