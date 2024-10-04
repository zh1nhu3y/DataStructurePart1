/**
 *  main.cpp
 */

#include <iostream>
#include "ReviewContainer.h"
#include "WordArray.h"
#include "SentimentAnalysis.h"

using namespace std;

int main()
{
    cout << "\n DATA STRUCTURE PART 1 - GROUP M";
    cout << "\n Pan Zhin Huey, Law Mei Jun, Jason Soo Zi Shen, Lee Cen Yu\n";
    cout << "\n================= DATA STORAGE ================\n\n";

    // Initialize custom array with a starting capacity
    CustomArray reviews(25000);

    // Input file path
    std::string inputFile = "C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/tripadvisor_test.csv";
    std::string outputFile = "C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/cleaned_tripadvisor_hotel_reviews.csv";

    // Clean the CSV file and store the data
    cleanCSV(inputFile, reviews);

    // Sort reviews based on rating
    reviews.sort();

    // Output cleaned reviews and ratings to a new CSV file
    reviews.writeToFile(outputFile);

    WordArray positiveWords, negativeWords;
    positiveWords.loadWordsFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/positive-words.txt");
    negativeWords.loadWordsFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/negative-words.txt");

    cout << "\n================= SENTIMENT ANALYSIS ================\n\n";

    // Create a SentimentLinkedList to analyze the reviews
    SentimentLinkedList sentimentList(positiveWords, negativeWords);

    // Add each reviews to the linked list
    for (int i = 0; i < reviews.getSize(); i++)
    {
        std::string reviewText = reviews.getReview(i);
        int reviewRating = reviews.getRating(i);
        sentimentList.insertAtEnd(reviewText, reviewRating);
        cout << "Added review " << i + 1 << " to the list." << endl;
    }
    cout << "Number of reviews loaded: " << sentimentList.getSize() << endl; // print number of reviews loaded

    // Sentiment Analysis for all reviews
    sentimentList.analyzeSentiment();

    sentimentList.bubbleSortSentiment();

    // Save sentiment analysis results to a file
    sentimentList.saveResultsToFile("sentiment_analysis_results.txt");

    cout << "\n================= END OF PROGRAM =================\n\n";
    return 0;
}
