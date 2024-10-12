#ifndef SENTIMENTCOMPARISON_H
#define SENTIMENTCOMPARISON_H

#include <iostream>
#include <cmath> // For std::floor

using namespace std;

class SentimentComparison
{
public:
    // Function to compare sentiment score with the rating and display results
    void compareSentimentAndRating(SentimentLinkedList &sentimentList)
    {
        SentimentNode *current = sentimentList.getHead(); // Get the head node

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

    void saveComparisonToFile(SentimentLinkedList &sentimentList, const string &filename)
    {
        ofstream outFile(filename); // Open the file for writing

        if (!outFile) // Check if file opened successfully
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        SentimentNode* current = sentimentList.getHead(); // Get the head node

        while (current)
        {
            // Floor the sentiment score to the nearest integer
            int flooredSentimentScore = static_cast<int>(std::floor(current->sentimentScore));

            outFile << "Review: " << current->review << endl;
            outFile << "Given Rating: " << current->rating << endl;
            outFile << "Sentiment Score (floored): " << flooredSentimentScore << endl;

            // Compare the floored sentiment score with the given rating
            if (flooredSentimentScore == current->rating)
            {
                outFile << "User's subjective evaluation matches the sentiment score provided by the analysis." << endl;
                outFile << "This suggests that the user's rating is consistent with the sentiment analysis." << endl;
            }
            else
            {
                outFile << "User's subjective evaluation does not match the sentiment score provided by the analysis." << endl;
                outFile << "This implies a difference in the user's perception compared to the sentiment analysis." << endl;
            }

            outFile << "----------------------------------------" << endl;

            // Move to the next review in the list
            current = current->next;
        }

        outFile.close(); // Close the file after writing
        cout << "Sentiment Comparison Results saved to: " << filename << endl;
    }
};

#endif // SENTIMENTCOMPARISON_H
