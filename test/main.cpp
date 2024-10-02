#include <iostream>
#include "ReviewContainer.h"
#include "WordArray.h"
#include "SentimentAnalysis.h"

int main()
{
    std::cout << "\n DATA STRUCTURE PART 1 - GROUP M";
    std::cout << "\n Pan Zhin Huey, Law Mei Jun, Jason Soo Zi Shen, Lee Cen Yu\n";
    std::cout << "\n================= DATA STORAGE ================\n\n";
    // Initialize the review container
    ReviewContainer reviews;

    // Load reviews from the raw CSV file
    reviews.loadFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/tripadvisor_test.csv");

    // Save the cleaned reviews to a new CSV file
    reviews.saveToFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/organized_hotel_reviews_test.csv");

    WordArray positiveWords, negativeWords;
    positiveWords.loadWordsFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/positive-words.txt");
    negativeWords.loadWordsFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/negative-words.txt");

    std::cout << "\n================= SENTIMENT ANALYSIS ================\n\n";

    reviews.loadFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/organized_hotel_reviews_test.csv");
    // Create a SentimentLinkedList to analyze the reviews
    SentimentLinkedList sentimentList(positiveWords, negativeWords);

    for (int i = 0; i < reviews.getReviewCount(); i++)
    {
        Review review = reviews.getReview(i);
        sentimentList.addReview(review.text, review.rating);
        std::cout << "Added review " << i + 1 << " to the list." << std::endl;
    }
    std::cout << "Number of reviews loaded: " << reviews.getReviewCount() << std::endl;

    // Analyze sentiment
    sentimentList.analyzeSentiment();

    // Save results to a file
    sentimentList.saveResultsToFile("sentiment_analysis_results.txt");

    std::cout << "\n================= END OF PROGRAM =================\n\n";
    return 0;
}
