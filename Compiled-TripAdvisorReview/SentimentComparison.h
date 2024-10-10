#ifndef SENTIMENTCOMPARISON_H
#define SENTIMENTCOMPARISON_H

#include <iostream>
#include <cmath> // For std::floor
#include "linkedlist.h" // This should contain LinkedList<SentimentNode>
#include "SentimentAnalysis.h" // Assuming this contains SentimentNode definition

using namespace std;

class SentimentComparison
{
public:
    // Function to compare sentiment score with the rating and display results
    void compareSentimentAndRating(SentimentLinkedList &sentimentList)
    {
        SentimentNode* current = sentimentList.getHead(); // Get the head node

        while (current)
        {

            // Floor the sentiment score to the nearest integer
            int flooredSentimentScore = static_cast<int>(std::floor(current->sentimentScore));

            cout << "Review: " << current->review << endl;
            cout << "Given Rating: " << current->rating << endl;
            cout << "Sentiment Score (floored): " << flooredSentimentScore << endl;

            // Compare the floored sentiment score with the given rating
            if (flooredSentimentScore == current->rating)
            {
                cout << "User's subjective evaluation matches the sentiment score provided by the analysis." << endl;
                cout << "This suggests that the user's rating is consistent with the sentiment analysis." << endl;
            }
            else
            {
                cout << "User's subjective evaluation does not match the sentiment score provided by the analysis." << endl;
                cout << "This implies a difference in the user's perception compared to the sentiment analysis." << endl;
            }
            cout << "----------------------------------------" << endl;

            // Move to the next review in the list
            current = current->next;
        }
    }
};

#endif // SENTIMENTCOMPARISON_H
