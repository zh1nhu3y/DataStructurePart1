#ifndef SENTIMENT_ANALYSIS_H
#define SENTIMENT_ANALYSIS_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include "ReviewContainer.h"
#include "WordArray.h"

struct SentimentNode
{
    std::string review;
    int rating;
    int positiveCount;
    int negativeCount;
    double sentimentScore;
    SentimentNode *next;

    SentimentNode(const std::string &r, int rt) : review(r), rating(rt), positiveCount(0), negativeCount(0), sentimentScore(0.0), next(nullptr) {}
};

class SentimentLinkedList
{
private:
    SentimentNode *head;
    WordArray &positiveWords;
    WordArray &negativeWords;

public:
    SentimentLinkedList(WordArray &posWords, WordArray &negWords);
    ~SentimentLinkedList();

    // Funtion declaration
    void addReview(const std::string &review, int rating);
    void analyzeSentiment();
    void analyzeReview(SentimentNode *node);
    void displayResults();
    void saveResultsToFile(const std::string &filename);
};

#endif
