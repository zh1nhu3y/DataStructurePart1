/** #include "SentimentAnalysis.h"
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
    istringstream iss(node->review);
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
    while (current)
    {
        analyzeReview(current);
        current = current->next;
    }
} */