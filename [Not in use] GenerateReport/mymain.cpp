#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <iomanip>
#include "SummaryReportGenerator.h"

using namespace std;

// Output to File Code

// Generate Histogram for Report

void generateHistogram(const LinkedList<WordFrequency> &frequencies, ofstream &outputFile, int maxBars = 10)
{
    outputFile << "\n9. WORD FREQUENCY HISTOGRAM\n";

    // Find the max frequency for scaling
    Node<WordFrequency> *current = frequencies.getHead();
    int maxFreq = 0;
    while (current != nullptr)
    {
        if (current->data.frequency > maxFreq)
            maxFreq = current->data.frequency;
        current = current->next;
    }

    // Display top words as a histogram
    current = frequencies.getHead();
    int shown = 0;
    while (current != nullptr && shown < maxBars)
    {
        int barLength = (current->data.frequency * 50) / maxFreq;
        outputFile << setw(15) << left << current->data.word << " |";
        for (int i = 0; i < barLength; i++)
            outputFile << "█"; // Block character created with "alt + 219"
        outputFile << " " << current->data.frequency << "\n";
        current = current->next;
        shown++;
    }
}

void generateSentimentDistribution(int positiveCount, int negativeCount, ofstream &outputFile)
{
    outputFile << "\n10. SENTIMENT DISTRIBUTION GRAPH\n";
    int total = positiveCount + negativeCount;
    if (total == 0)
        return;

    int positiveBar = (positiveCount * 50) / total;
    int negativeBar = (negativeCount * 50) / total;

    outputFile << "Positive |";
    for (int i = 0; i < positiveBar; i++)
        outputFile << "█";
    outputFile << " " << positiveCount << " ("
               << fixed << setprecision(1)
               << (static_cast<double>(positiveCount) / total * 100) << "%)\n";

    outputFile << "Negative |";
    for (int i = 0; i < negativeBar; i++)
        outputFile << "█";
    outputFile << " " << negativeCount << " ("
               << fixed << setprecision(1)
               << (static_cast<double>(negativeCount) / total * 100) << "%)\n";
}

void generateEnhancedReport(const SummaryReportGenerator &analyzer, ofstream &outputFile)
{
    outputFile << "\n====== COMPREHENSIVE SENTIMENT ANALYSIS REPORT ======\n\n";

    // 1. Basic Statistics
    int totalReviews = analyzer.getTotalReviews();
    int totalPositive = analyzer.getTotalPositiveWords();
    int totalNegative = analyzer.getTotalNegativeWords();

    outputFile << "1. BASIC STATISTICS\n";
    outputFile << "Total Reviews Analyzed: " << totalReviews << "\n";
    outputFile << "Total Positive Words: " << totalPositive << "\n";
    outputFile << "Total Negative Words: " << totalNegative << "\n";

    // 2. Overall Sentiment Trend
    double sentimentRatio = totalReviews > 0 ? static_cast<double>(totalPositive) / (totalPositive + totalNegative) : 0;
    outputFile << "\n2. OVERALL SENTIMENT TREND\n";
    outputFile << "Sentiment Ratio (positive words / total sentiment words): "
               << fixed << setprecision(2) << sentimentRatio * 100 << "%\n";

    if (sentimentRatio > 0.6)
    {
        outputFile << "Trend: Predominantly Positive Sentiment\n";
    }
    else if (sentimentRatio < 0.4)
    {
        outputFile << "Trend: Predominantly Negative Sentiment\n";
    }
    else
    {
        outputFile << "Trend: Mixed Sentiment\n";
    }

    // 3. Word Usage Analysis
    LinkedList<WordFrequency> frequencies = analyzer.getWordFrequencies();
    Node<WordFrequency> *current = frequencies.getHead();

    string maxWord, minWord;
    int maxFreq = 0, minFreq = INT_MAX;
    int totalWords = 0;

    while (current != nullptr)
    {
        if (current->data.frequency > maxFreq)
        {
            maxFreq = current->data.frequency;
            maxWord = current->data.word;
        }
        if (current->data.frequency < minFreq)
        {
            minFreq = current->data.frequency;
            minWord = current->data.word;
        }
        totalWords += current->data.frequency;
        current = current->next;
    }

    outputFile << "\n3. WORD USAGE PATTERNS\n";
    outputFile << "Most impactful word: \"" << maxWord << "\" (used " << maxFreq << " times)\n";
    outputFile << "Least impactful word: \"" << minWord << "\" (used " << minFreq << " times)\n";

    // 4. Average Sentiment Words Per Review
    double avgWordsPerReview = totalReviews > 0 ? static_cast<double>(totalWords) / totalReviews : 0;
    outputFile << "\n4. SENTIMENT INTENSITY\n";
    outputFile << "Average sentiment words per review: "
               << fixed << setprecision(2) << avgWordsPerReview << "\n";

    if (avgWordsPerReview > 5)
    {
        outputFile << "Trend: Reviews show strong emotional content\n";
    }
    else if (avgWordsPerReview < 2)
    {
        outputFile << "Trend: Reviews are generally neutral or factual\n";
    }
    else
    {
        outputFile << "Trend: Reviews show moderate emotional content\n";
    }

    // 5. Word Frequency Distribution
    outputFile << "\n5. WORD FREQUENCY DISTRIBUTION\n";
    int highFreq = 0, medFreq = 0, lowFreq = 0;
    current = frequencies.getHead();

    while (current != nullptr)
    {
        if (current->data.frequency >= maxFreq * 0.7)
            highFreq++;
        else if (current->data.frequency >= maxFreq * 0.3)
            medFreq++;
        else
            lowFreq++;
        current = current->next;
    }

    outputFile << "High frequency words (>70% of max): " << highFreq << "\n";
    outputFile << "Medium frequency words (30-70% of max): " << medFreq << "\n";
    outputFile << "Low frequency words (<30% of max): " << lowFreq << "\n";

    // 6. Detailed Word List
    outputFile << "\n6. DETAILED WORD FREQUENCY LIST\n";

    current = frequencies.getHead();

    // testing
    cout << "Total words: " << totalWords << "\n"; // Print total words

    if (current != nullptr)
    {
        cout << "Current Frequency: " << current->data.frequency << "\n"; // Print current frequency if current is not nullptr
    }

    while (current != nullptr)
    {
        // Percentage of each word used
        double percentage = totalWords > 0 ? (static_cast<double>(current->data.frequency) / totalWords) * 100.0 : 0.0;
        outputFile << current->data.word << ": " << current->data.frequency
                   << " times (" << fixed << setprecision(3) << percentage << "%)\n";
        current = current->next;
    }

    // Add histogram
    generateHistogram(frequencies, outputFile);

    // Add sentiment distribution graph
    generateSentimentDistribution(analyzer.getTotalPositiveWords(),
                                  analyzer.getTotalNegativeWords(), outputFile);

    // ... (keep sorting and searching sections)
}

int main()
{
    SummaryReportGenerator reportGenerator;

    // Load word lists
    reportGenerator.loadWordLists("C:/Users/Zhin Huey/OneDrive - Asia Pacific University/Degree Year2-SEM2/Data Structure/Assignement 1/positive-words.txt", "C:/Users/Zhin Huey/OneDrive - Asia Pacific University/Degree Year2-SEM2/Data Structure/Assignement 1/negative-words.txt");

    // Process CSV file
    ifstream csvFile("C:/Users/Zhin Huey/OneDrive - Asia Pacific University/Degree Year2-SEM2/Data Structure/Assignement 1/tripadvisor_hotel_reviews.csv");
    string line;

    // Skip header line
    getline(csvFile, line);

    while (getline(csvFile, line))
    {
        istringstream iss(line);
        string review;

        // Assuming the review text is in the second column
        getline(iss, review, ','); // Skip first column
        getline(iss, review, ','); // Get review text

        reportGenerator.analyzeReview(review);
    }

    // Open the output file
    ofstream outputFile("C:/Users/Zhin Huey/OneDrive - Asia Pacific University/Degree Year2-SEM2/Data Structure/Assignement 1/sentiment_analysis_report.txt");
    if (!outputFile.is_open())
    {
        cerr << "Error: Could not open the file for writing." << endl;
        return 1; // Exit if the file cannot be opened
    }

    // Generate and save the report
    generateEnhancedReport(reportGenerator, outputFile);

    // Close the output file
    outputFile.close();

    // Print confirmation to the console
    cout << "Summary Report Generated\n";

    return 0;
}