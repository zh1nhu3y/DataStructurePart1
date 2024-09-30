#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

const int INITIAL_CAPACITY_WORDS = 1000;  // Initial capacity for dynamic array

class WordArray {
private:
    std::string* words;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        std::string* newWords = new std::string[capacity];
        for (int i = 0; i < size; i++) {
            newWords[i] = words[i];
        }
        delete[] words;
        words = newWords;
    }

public:
    WordArray() : size(0), capacity(INITIAL_CAPACITY_WORDS) {
        words = new std::string[capacity];
    }

    ~WordArray() {
        delete[] words;
    }

    void addWord(const std::string& word) {
        if (size >= capacity) {
            resize();
        }
        words[size++] = word;
    }

    bool contains(const std::string& word) const {
        std::string lowerWord = toLower(word); // Convert to lower case for comparison
        for (int i = 0; i < size; i++) {
            if (toLower(words[i]) == lowerWord) {
                return true;
            }
        }
        return false;
    }

    std::string toLower(const std::string& str) const {
        std::string lowerStr = str;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }

    void loadWordsFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string word;
        while (std::getline(file, word)) {
            addWord(word);
        }
        file.close();
    }

    int getWordCount() const {
        return size;  // Add this method to get the count of words loaded
    }
};