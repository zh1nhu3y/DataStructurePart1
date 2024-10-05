/** #ifndef SENTIMENT_ANALYSIS_H
#define SENTIMENT_ANALYSIS_H

#include <string>
#include "positive_and_negative_words.cpp"
#include "tripadvisor_hotel_reviews.cpp"

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
};

#endif
*/