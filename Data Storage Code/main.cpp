#include <iostream>
#include "SentimentAnalysis.h"

int main()
{
    // Step 1: Load positive and negative words into WordArray
    WordArray positiveWords, negativeWords;

    // Load positive and negative words from files
    positiveWords.loadWordsFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/positive-words.txt");
    negativeWords.loadWordsFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/negative-words.txt");

    std::cout << "Loaded " << positiveWords.getWordCount() << " positive words and "
              << negativeWords.getWordCount() << " negative words." << std::endl;

    // Step 2: Initialize the review container
    ReviewContainer reviews;

    // Load reviews from the CSV file
    reviews.loadFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/organized_hotel_reviews.csv");

    std::cout << "Loaded " << reviews.getReviewCount() << " reviews." << std::endl;

    // Step 3: Initialize SentimentLinkedList with positive and negative words
    SentimentLinkedList sentimentList(positiveWords, negativeWords);

    // Step 4: Add reviews to the sentiment list and analyze each one
    for (int i = 0; i < reviews.getReviewCount(); i++)
    {
        Review review = reviews.getReview(i);
        sentimentList.addReview(review.text, review.rating);
    }

    sentimentList.analyzeSentiment();

    sentimentList.displayResults();

    return 0;
}