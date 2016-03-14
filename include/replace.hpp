#ifndef REPLACE_H
#define REPLACE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "options.hpp"

class Replace {
    static const std::string WORD_SEPARATORS;
    std::ifstream inputFile;
    std::ofstream outputFile;

    std::string readbuf;
    std::string outbuf;
    std::string dupbuf;
    std::string dupbufwithsep;

    std::string unrollFirst;
    std::vector <std::string> unroll;

    void processOneLine(const std::string & line);
    void processOneWord(const std::string & word);
    bool isSeparator(const std::string & word);
public:

    Replace(const Options & options);
    virtual ~Replace();
    void replace();
};

#endif

