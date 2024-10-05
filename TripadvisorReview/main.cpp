/**
 *  main.cpp
 */

#include <iostream>
#include "ReviewContainer.h"
#include "WordArray.h"
#include "SentimentAnalysis.h"
#include "SummaryReportGenerator.h"

using namespace std;

int main()
{
    cout << "\n DATA STRUCTURE PART 1 - GROUP M";
    cout << "\n Pan Zhin Huey, Law Mei Jun, Jason Soo Zi Shen, Lee Cen Yu\n";
    cout << "\n================= DATA STORAGE ================\n\n";
    // Initialize the review container
    ReviewContainer reviews;

    // Load reviews from the raw CSV file
    reviews.loadFromFile("C:/Users/Zhin Huey/OneDrive - Asia Pacific University/Degree Year2-SEM2/Data Structure/Assignement 1/tripadvisor_hotel_reviews.csv");

    // Save the cleaned reviews to a new CSV file
    reviews.saveToFile("C:/Users/Zhin Huey/OneDrive - Asia Pacific University/Degree Year2-SEM2/Data Structure/organized_hotel_reviews.csv");

    WordArray positiveWords, negativeWords;
    positiveWords.loadWordsFromFile("C:/Users/Zhin Huey/OneDrive - Asia Pacific University/Degree Year2-SEM2/Data Structure/Assignement 1/positive-words.txt");
    negativeWords.loadWordsFromFile("C:/Users/Zhin Huey/OneDrive - Asia Pacific University/Degree Year2-SEM2/Data Structure/Assignement 1/negative-words.txt");

    cout << "\n================= SENTIMENT ANALYSIS ================\n\n";

    reviews.loadFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/organized_hotel_reviews_test.csv");

    // Create a SentimentLinkedList to analyze the reviews
    SentimentLinkedList sentimentList(positiveWords, negativeWords);

    // Add each reviews to the linked list
    (int i = 0; i < reviews.getReviewCount(); i++)
    {
        Review review = reviews.getReview(i);
        sentimentList.addReview(review.text, review.rating);

        for (int i = 0; i < reviews.getSize(); i++)
        {
            std::string reviewText = reviews.getReview(i);
            int reviewRating = reviews.getRating(i);
            sentimentList.insertAtEnd(reviewText, reviewRating);

            cout << "Added review " << i + 1 << " to the list." << endl;
        }
        cout << "Number of reviews loaded: " << sentimentList.getSize() << endl; // print number of reviews loaded
    }
    // Sentiment Analysis for all reviews
    sentimentList.analyzeSentiment();

    sentimentList.bubbleSortSentiment();

    // Save sentiment analysis results to a file
    sentimentList.saveResultsToFile("sentiment_analysis_results.txt");

    cout << "\n================= SUMMARY REPORT ================\n\n";

    // Create report generator using existing word arrays
    SummaryReportGenerator reportGenerator(positiveWords, negativeWords);

    // Convert array to linked list and analyze reviews
    reportGenerator.analyzeReviews(reviews); // uses the already cleaned reviews

    // Generate comprehensive report
    reportGenerator.generateEnhancedReport("C:/Users/Zhin Huey/OneDrive - Asia Pacific University/Degree Year2-SEM2/Data Structure/Assignement 1/summary_report.txt");

    cout << "\n================= END OF PROGRAM =================\n\n";
    return 0;
}
