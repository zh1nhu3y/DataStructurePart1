#include "WordArray.h"

// Constructor
WordArray::WordArray() : size(0), capacity(INITIAL_CAPACITY_WORDS)
{
    words = new std::string[capacity];
}

// Destructor
WordArray::~WordArray()
{
    delete[] words;
}

// Resize the dynamic array
void WordArray::resize()
{
    capacity *= 2;
    std::string *newWords = new std::string[capacity];
    for (int i = 0; i < size; i++)
    {
        newWords[i] = words[i];
    }
    delete[] words;
    words = newWords;
}

// Add a word to the array
void WordArray::addWord(const std::string &word)
{
    if (size >= capacity)
    {
        resize();
    }
    words[size++] = word;
}

// Check if the array contains a word
bool WordArray::contains(const std::string &word) const
{
    std::string lowerWord = toLower(word); // Convert to lower case for comparison
    for (int i = 0; i < size; i++)
    {
        if (toLower(words[i]) == lowerWord)
        {
            return true;
        }
    }
    return false;
}

// Convert string to lower case
std::string WordArray::toLower(const std::string &str) const
{
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Load words from a file
void WordArray::loadWordsFromFile(const std::string &filename)
{
    std::cout << "Loading file from: " << filename << std::endl;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string word;
    while (std::getline(file, word))
    {
        addWord(word);
    }
    file.close();
    std::cout << "Words file loaded" << std::endl;
}

// Get the number of words loaded
int WordArray::getWordCount() const
{
    return size; // Add this method to get the count of words loaded
}
