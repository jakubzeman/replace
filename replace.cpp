#include "replace.hpp"
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

std::string Replace::WORD_SEPARATORS = " \n";

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
    WORD_SEPARATORS = options.getSeparators();
    this->printDuplicities = options.printDuplicitiesEnabled();
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
    return 1 == word.length() && std::string::npos != WORD_SEPARATORS.find(word);
}

void Replace::processSeparator(const std::string & word)
{
    if (this->compareBuffer.noSep.empty()) {
        if (this->readBuffer.output.empty())
            this->readBuffer.output += word;
        // For more readability skip duplicities of separators ("lazy fox     jumps" is reduced to "lazy fox jumps")
        else if (1 < word.length() || (1 == word.length() && *word.begin() != *this->readBuffer.output.rbegin()))
            this->readBuffer.output += word;
    }
    else {
        this->compareBuffer.output += word;
        this->rollBackBuffer.push_back(word);
    }
}

void Replace::processStartup(const std::string & word)
{
    size_t pos = this->readBuffer.noSep.find(word);
    if (pos == std::string::npos) {
        // If the word is not present in already read buffer just continue
        this->readBuffer.noSep += word;
        this->readBuffer.output += word;
    }
    else if (pos + word.length() == this->readBuffer.noSep.length()) {
        // In case it reached the end of already read buffer then it's a duplicity and we can skip it.
        if (this->printDuplicities) std::cout << "Duplicity found: <" << word << ">" << std::endl;
        this->cleanUpWhenDuplicityFound();
    }
    else {
        // Otherwise start comparing new sequence
        this->compareBuffer.noSep = word;
        this->compareBuffer.output = word;
        this->rollBackBufferFirst = word;
    }
}

void Replace::cleanUpWhenNoDuplicity() {
    this->readBuffer.noSep += this->rollBackBufferFirst;
    this->readBuffer.output += this->rollBackBufferFirst;
    this->compareBuffer.noSep = "";
    this->compareBuffer.output = "";
    this->rollBackBufferFirst = "";
}

void Replace::cleanUpWhenDuplicityFound() 
{
    if (!this->compareBuffer.output.empty() && this->printDuplicities) {
        std::cout << "Duplicity found: <" << this->compareBuffer.output << ">" << std::endl;
    }
    this->compareBuffer.noSep = "";
    this->compareBuffer.output = "";
    this->rollBackBufferFirst = "";
    this->rollBackBuffer.clear();
}

void Replace::processOneWord(const std::string & word)
{
    bool sep = isSeparator(word);
    if (sep) {
        // Ignore separators (I need to save them to output buffers only)
        this->processSeparator(word);
    }
    else {
        if (this->compareBuffer.noSep.empty()) {
            // Process words in case no duplicity was found
            this->processStartup(word);
        }
        else {
            // Add word to comparation buffer
            this->compareBuffer.noSep += word;
            this->compareBuffer.output += word;
            this->rollBackBuffer.push_back(word);
            // Try to find duplicity from the beginning of already read file
            size_t pos = this->readBuffer.noSep.find(this->compareBuffer.noSep);
            if (pos == std::string::npos) {
                this->cleanUpWhenNoDuplicity();
                
                // Process next words in the buffer again
                const std::vector <std::string> rollBackBufferCopy(this->rollBackBuffer);
                this->rollBackBuffer.clear();
                BOOST_FOREACH(const std::string & retryWord, rollBackBufferCopy) {
                    processOneWord(retryWord);
                }
            }
            else if (pos + this->compareBuffer.noSep.length() == this->readBuffer.noSep.length()) {
                // In case it reached the end of already read buffer then it's a duplicity and we can skip it.
                this->cleanUpWhenDuplicityFound();
            }
        }
    }
}

void Replace::processFile(const std::string & file)
{
    const boost::char_separator<char> sep("", WORD_SEPARATORS.c_str());
    const boost::tokenizer<boost::char_separator<char> > words(file, sep);

    BOOST_FOREACH(const std::string & word, words) {
        this->processOneWord(word);
    }
}

void Replace::replace()
{
    if (!this->inputFile.is_open() || !this->outputFile.is_open()) {
        return;
    }

    std::string textFile((std::istreambuf_iterator<char>(this->inputFile)), std::istreambuf_iterator<char>());
    this->processFile(textFile);
    this->outputFile << this->readBuffer.output;
    if (!this->compareBuffer.output.empty()) {
        this->outputFile << this->compareBuffer.output;
    }
}

