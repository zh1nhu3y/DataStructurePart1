/**
 *  SentimentAnalysis.cpp
 */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

// Struct to store words found in a linked list
struct WordNode
{
    string word;
    WordNode *next;

    WordNode(const string &w) : word(w), next(nullptr) {}
};

// Struct to store review data with sentiment analysis
struct SentimentNode
{
    string review;
    int rating;
    int positiveCount;
    int negativeCount;
    double sentimentScore;
    WordNode *positiveWordsList;
    WordNode *negativeWordsList;
    SentimentNode *next;

    SentimentNode(const string &r, int rt) : review(r), rating(rt), positiveCount(0), negativeCount(0), sentimentScore(0.0),
                                             positiveWordsList(nullptr), negativeWordsList(nullptr), next(nullptr) {}
};

class SentimentLinkedList
{
private:
    SentimentNode *head;
    WordArray &positiveWords; // Array of positive words
    WordArray &negativeWords; // Array of negative words
    int size;

public:
    // Constructor
    SentimentLinkedList(WordArray &posWords, WordArray &negWords)
        : head(nullptr), positiveWords(posWords), negativeWords(negWords), size(0) {}

    // Destructor
    ~SentimentLinkedList()
    {
        SentimentNode *current = head;
        while (current)
        {
            deleteList(current->positiveWordsList);
            deleteList(current->negativeWordsList);
            SentimentNode *temp = current;
            current = current->next;
            delete temp;
        }
    }

    // Function to delete word linked list (for destructor)
    void deleteList(WordNode *node)
    {
        while (node)
        {
            WordNode *temp = node;
            node = node->next;
            delete temp;
        }
    }

    //  Add a new review to linked list
    void addReview(const string &review, int rating)
    {
        SentimentNode *newNode = new SentimentNode(review, rating);

        if (!head)
        {
            head = newNode;
        }
        else
        {
            SentimentNode *current = head;
            while (current->next)
            {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    int getSize()
    {
        return size;
    }

    //  Sentiment Analysis for one review
    void analyzeReview(SentimentNode *node)
    {
        string lowerReview = node->review;
        transform(lowerReview.begin(), lowerReview.end(), lowerReview.begin(), ::tolower);

        istringstream iss(lowerReview);
        string word;

        // Count positive and negative words and store them in lists
        while (iss >> word)
        {
            if (positiveWords.contains(word))
            {
                node->positiveCount++;
                addToList(node->positiveWordsList, word); // Add positive word to list
            }
            if (negativeWords.contains(word))
            {
                node->negativeCount++;
                addToList(node->negativeWordsList, word); // Add negative word to list
            }
        }

        // Calculate raw score
        int rawScore = node->positiveCount - node->negativeCount;

        // N is the total number of positive and negative words
        int N = node->positiveCount + node->negativeCount;

        if (N > 0)
        {
            // Calculate the min and max raw scores
            int minRawScore = -N;
            int maxRawScore = +N;

            // Calculate the normalized score
            double normalizedScore = static_cast<double>(rawScore - minRawScore) / (maxRawScore - minRawScore);

            // Calculate the final sentiment score (1–5)
            node->sentimentScore = 1 + (4 * normalizedScore);
        }
        else
        {
            // If no sentiment words, set a neutral score
            node->sentimentScore = 3;
        }
    }

    //  Analyze all reviews in the linked list
    void analyzeSentiment()
    {
        SentimentNode *current = head;
        int count = 0;
        while (current)
        {
            analyzeReview(current);
            cout << "Analyzed sentiment for review " << ++count << endl;
            current = current->next;
        }
        cout << "Total Review Analyzed: " << count << endl;
    }

    //  Add a word to a linked list
    void addToList(WordNode *&listHead, const string &word)
    {
        WordNode *newWord = new WordNode(word);
        if (!listHead)
        {
            listHead = newWord;
        }
        else
        {
            WordNode *current = listHead;
            while (current->next)
            {
                current = current->next;
            }
            current->next = newWord;
        }
    }

    // Save sentiment analysis results to a file
    void saveResultsToFile(const string &filename)
    {
        ofstream outFile(filename);
        if (!outFile)
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        SentimentNode *current = head;
        while (current)
        {
            outFile << "Review: " << current->review << "\n"
                    << endl;
            outFile << "Positive Words Count: " << current->positiveCount << endl;
            outFile << "Positive Words Found: ";
            writeWordsToFile(outFile, current->positiveWordsList);
            outFile << "Negative Words Count: " << current->negativeCount << endl;
            outFile << "Negative Words Found: ";
            writeWordsToFile(outFile, current->negativeWordsList);
            outFile << "Sentiment Score: " << current->sentimentScore << endl;
            outFile << "Given Rating: " << current->rating << endl;
            outFile << "----------------------------------------" << endl;
            current = current->next;
        }

        outFile.close();
        cout << "Sentiment Analysis Results saved to: " << filename << endl;
    }

    // Write list of words from a linked list to the file
    void writeWordsToFile(ofstream &outFile, WordNode *listHead)
    {
        WordNode *current = listHead;
        if (listHead == nullptr)
        {
            outFile << "-";
        }
        while (current)
        {
            outFile << current->word << " ";
            current = current->next;
        }
        outFile << endl;
    }
};
