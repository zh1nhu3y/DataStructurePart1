#ifndef WORD_ARRAY_H
#define WORD_ARRAY_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

static const int INITIAL_CAPACITY_WORDS = 1000;

class WordArray
{
private:
    std::string *words;
    int size;
    int capacity;

    void resize();

public:
    WordArray();
    ~WordArray();
    void addWord(const std::string &word);
    bool contains(const std::string &word) const;
    std::string toLower(const std::string &str) const;
    void loadWordsFromFile(const std::string &filename);
    int getWordCount() const;
};

#endif // WORD_ARRAY_H
