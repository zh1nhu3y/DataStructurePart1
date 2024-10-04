/** #include <iostream>
#include <fstream>
#include <sstream>
#include "tripadvisor_hotel_reviews.cpp" // No .h file; directly use the cpp file
#include "positive_and_negative_words.cpp"

// Function to count positive and negative words in a review and write results to a file
void analyzeSentiment(const Review &review, const WordArray &positiveWords, const WordArray &negativeWords, std::ofstream &outFile)
{
    int positiveCount = 0, negativeCount = 0;
    std::istringstream words(review.text);
    std::string word;

    while (words >> word)
    {
        // Normalize word to lower case for comparison
        std::string lowerWord = word;
        std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);

        if (positiveWords.contains(lowerWord))
        {
            positiveCount++;
        }
        if (negativeWords.contains(lowerWord))
        {
            negativeCount++;
        }
    }

    // Raw Sentiment Score
    int rawScore = positiveCount - negativeCount;
    int N = positiveCount + negativeCount; // Total positive and negative word count

    // Normalized Score calculation
    float normalizedScore = 0.0;
    if (N > 0)
    {
        float minRawScore = -N;
        float maxRawScore = N;
        normalizedScore = (rawScore - minRawScore) / (maxRawScore - minRawScore);
    }

    // Sentiment Score (1 – 5)
    float sentimentScore = 1 + (4 * normalizedScore);

    // Write the result to the file
    outFile << "Review: " << review.text << std::endl;
    outFile << "Positive Words = " << positiveCount << std::endl;
    outFile << "Negative Words = " << negativeCount << std::endl;
    outFile << "Sentiment Score (1-5) = " << sentimentScore << std::endl;
    outFile << "============================" << std::endl;
}

int main()
{
    // Initialize the review container
    ReviewContainer reviews;

    // Load reviews from the raw CSV file
    reviews.loadFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/tripadvisor_hotel_reviews.csv");

    // Save the cleaned reviews to a new CSV file
    reviews.saveToFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/organized_hotel_reviews.csv");

    std::cout << "Data cleaning complete. Cleaned data saved to " << CLEANED_FILE << std::endl;

    reviews.loadFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/organized_hotel_reviews.csv");

    WordArray positiveWords, negativeWords;
    positiveWords.loadWordsFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/positive-words.txt");
    negativeWords.loadWordsFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/negative-words.txt");

    // Open the file for writing the results
    std::ofstream outFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/sentiment_analysis_results.txt");

    if (!outFile.is_open())
    {
        std::cerr << "Error opening file for writing results." << std::endl;
        return 1;
    }

    // Analyze each review and write results to the file
    for (int i = 0; i < reviews.getReviewCount(); i++)
    {
        Review review = reviews.getReview(i);
        analyzeSentiment(review, positiveWords, negativeWords, outFile);
    }

    // Close the file when done
    outFile.close();

    std::cout << "Sentiment analysis completed. Results written to file." << std::endl;

    return 0;
}
*/