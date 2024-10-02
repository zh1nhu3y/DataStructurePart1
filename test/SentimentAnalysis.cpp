#include "SentimentAnalysis.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

SentimentLinkedList::SentimentLinkedList(WordArray &posWords, WordArray &negWords)
    : head(nullptr), positiveWords(posWords), negativeWords(negWords) {}

SentimentLinkedList::~SentimentLinkedList()
{
    SentimentNode *current = head;
    while (current)
    {
        SentimentNode *temp = current;
        current = current->next;
        delete temp;
    }
}

void SentimentLinkedList::addReview(const string &review, int rating)
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
}

void SentimentLinkedList::analyzeReview(SentimentNode *node)
{
    string lowerReview = node->review;
    std::transform(lowerReview.begin(), lowerReview.end(), lowerReview.begin(), ::tolower);

    istringstream iss(lowerReview); // Use the lowercased review for analysis
    string word;

    while (iss >> word)
    {
        if (positiveWords.contains(word))
        {
            node->positiveCount++;
        }
        if (negativeWords.contains(word))
        {
            node->negativeCount++;
        }
    }

    int rawScore = node->positiveCount - node->negativeCount;
    int N = node->positiveCount + node->negativeCount;

    if (N > 0)
    {
        double normalizedScore = static_cast<double>(rawScore + N) / (2 * N);
        node->sentimentScore = 1 + (4 * normalizedScore);
    }
    else
    {
        node->sentimentScore = 3;
    }
}

void SentimentLinkedList::displayResults()
{
    SentimentNode *current = head;
    while (current)
    {
        cout << "Review: " << current->review << endl;
        cout << "Positive words: " << current->positiveCount << endl;
        cout << "Negative words: " << current->negativeCount << endl;
        cout << "Sentiment Score: " << current->sentimentScore << endl;
        cout << "Given rating: " << current->rating << endl;
        cout << "----------------------------------------" << endl;
        current = current->next;
    }
}

void SentimentLinkedList::analyzeSentiment()
{
    SentimentNode *current = head;
    int count = 0;
    while (current)
    {
        analyzeReview(current);
        std::cout << "Analyzed sentiment for review " << ++count << std::endl;
        current = current->next;
    }
    std::cout << "Total Review Analyzed: " << count << std::endl;
}

void SentimentLinkedList::saveResultsToFile(const string &filename)
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
        outFile << "Review: " << current->review << endl;
        outFile << "Positive words: " << current->positiveCount << endl;
        outFile << "Negative words: " << current->negativeCount << endl;
        outFile << "Sentiment Score: " << current->sentimentScore << endl;
        outFile << "Given rating: " << current->rating << endl;
        outFile << "----------------------------------------" << endl;
        current = current->next;
    }

    outFile.close();
    cout << "Sentiment Analysis Results saved to: " << filename << endl;
}