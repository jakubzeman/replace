#include "replace.hpp"
#include <iostream>
#include <stdlib.h>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

const std::string Replace::WORD_SEPARATORS = " \n";

Replace::Replace(const Options & options)
{
    this->inputFile.open(options.getInputFileName().c_str());
    if (!this->inputFile.is_open()) {
        std::cerr << "Cannot open " << options.getInputFileName() << std::endl;
        return;
    }
    this->outputFile.open(options.getOutputFileName().c_str());
    if (!this->outputFile.is_open()) {
        std::cerr << "Cannot open " << options.getOutputFileName() << std::endl;
    }
}

Replace::~Replace()
{
    if (this->inputFile.is_open())
        this->inputFile.close();
    if (this->outputFile.is_open())
        this->outputFile.close();
}

bool Replace::isSeparator(const std::string & word)
{
    //if (1 == word.length() && 0 == word.compare("\n"))
    if (1 == word.length() && std::string::npos != WORD_SEPARATORS.find(word))
        return true;
    else
        return false;
}

void Replace::processOneWord(const std::string & word)
{
    bool sep = isSeparator(word);
    if (sep) {
        if (this->dupbuf.empty()) {
            if (this->outbuf.empty())
                this->outbuf += word;
            else if (1 < word.length() || (1 == word.length() && *word.begin() != *this->outbuf.rbegin()))
                this->outbuf += word;
        }
        else {
            this->dupbufwithsep += word;
            this->unroll.push_back(word);
        }
    }
    else {
        if (this->dupbuf.empty()) {
            std::cout << "<" << word << ">" << std::endl;
            size_t pos = this->readbuf.find(word);
            if (pos == std::string::npos) {
                this->readbuf += word;
                this->outbuf += word;
            }
            else if (pos + word.length() == this->readbuf.length()) {
                this->dupbuf = "";
                this->dupbufwithsep = "";
                this->unrollFirst = "";
            }
            else {
                this->dupbuf = word;
                this->dupbufwithsep = word;
                this->unrollFirst = word;
            }
        }
        else {
            this->dupbuf += word;
            this->dupbufwithsep += word;
            this->unroll.push_back(word);
            size_t pos = this->readbuf.find(this->dupbuf);
            if (pos == std::string::npos) {
                std::cout << "FCK <" << this->dupbufwithsep << ">" << std::endl;
                this->readbuf += this->unrollFirst;
                this->outbuf += this->unrollFirst;
                this->dupbuf = "";
                this->dupbufwithsep = "";
                this->unrollFirst = "";

                std::vector <std::string> unroll_copy(this->unroll);
                this->unroll.clear();
                BOOST_FOREACH(std::string retry_word, unroll_copy) {
                    processOneWord(retry_word);
                }
            }
            else if (pos + this->dupbuf.length() == this->readbuf.length()) {
                std::cout << "Clean up <" << this->dupbufwithsep << ">" << std::endl;
                this->dupbuf = "";
                this->dupbufwithsep = "";
                this->unrollFirst = "";
                this->unroll.clear();
            }
        }
    }
}

void Replace::processOneLine(const std::string & line)
{
    boost::char_separator<char> sep("", WORD_SEPARATORS.c_str());
    boost::tokenizer<boost::char_separator<char> > words(line, sep);

    BOOST_FOREACH(std::string word, words) {
        this->processOneWord(word);
    }
}

void Replace::replace()
{
    if (!this->inputFile.is_open() || !this->outputFile.is_open()) {
        return;
    }

    std::string line;
    while (0 == (this->inputFile.rdstate() & std::ifstream::eofbit)) {
        std::getline(this->inputFile, line);
        if (0 == (this->inputFile.rdstate() & std::ifstream::eofbit))
            line += "\n";
        this->processOneLine(line);
    }
    this->outputFile << this->outbuf;
    if (!this->dupbufwithsep.empty()) {
        std::cout << "Hola <" << this->dupbuf << ">" << std::endl;
        std::cout << "Hola <" << this->readbuf << ">" << std::endl;
        this->outputFile << this->dupbufwithsep;
    }
}

