/**
 * SummaryReportGenerator.h
 */

#ifndef SUMMARYREPORTGENERATOR_H
#define SUMMARYREPORTGENERATOR_H

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <climits>
#include <iomanip>
#include <chrono>
#include "LinkedList.h"
#include "ReviewContainer.h"
#include "WordArray.h"

using namespace std;

struct WordFrequency
{
    string word;
    int frequency;

    WordFrequency(string w, int f) : word(w), frequency(f) {}

    bool operator==(const WordFrequency &other) const
    {
        return word == other.word; // Compare based on the word
    }
};

class SummaryReportGenerator
{
private:
    LinkedList<string> reviewLinkedList;
    const WordArray &positiveWords;
    const WordArray &negativeWords;
    LinkedList<string> allWords;
    Node<WordFrequency> *head;
    int totalReviews;
    int totalPositiveWords;
    int totalNegativeWords;

public:
    // Constructor
    SummaryReportGenerator(const WordArray &posWords, const WordArray &negWords)
        : positiveWords(posWords), negativeWords(negWords),
          totalPositiveWords(0), totalNegativeWords(0), head(nullptr) {}

    // Destructor
    // ~SummaryReportGenerator();

    void analyzeReviews(const ReviewContainer &reviews)
    {
        convertArrayToLinkedList(reviews);
        analyzeReviewsInLinkedList();
    }

    LinkedList<WordFrequency> getWordFrequencies() const
    {
        LinkedList<WordFrequency> frequencies;
        Node<string> *current = allWords.getHead();

        while (current != nullptr)
        {
            int freq = allWords.getWordFrequency(current->data);
            frequencies.insert(WordFrequency(current->data, freq));
            current = current->next;
        }

        return frequencies;
    }

    void generateEnhancedReport(const std::string &outputFilename)
    {
        cout << "Generating enhanced report..." << endl;
        std::ofstream outputFile(outputFilename);
        if (!outputFile.is_open())
        {
            cerr << "Error: Could not open the file for writing." << endl;
            return;
        }
        outputFile << "\n====== COMPREHENSIVE SENTIMENT ANALYSIS REPORT ======\n\n";

        // 1. Basic Statistics
        outputFile << "1. BASIC STATISTICS\n";
        outputFile << "Total Reviews Analyzed: " << reviewLinkedList.getSize() << "\n";
        outputFile << "Total Positive Words: " << totalPositiveWords << "\n";
        outputFile << "Total Negative Words: " << totalNegativeWords << "\n";

        // 2. Overall Sentiment Trend - overall direction of sentiment (positive or negative)
        double sentimentRatio = totalReviews > 0 ? static_cast<double>(totalPositiveWords) / (totalPositiveWords + totalNegativeWords) : 0;
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
        LinkedList<WordFrequency> frequencies = getWordFrequencies();
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

        // Testing
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
        generateHistogram(outputFile);

        // Add sentiment distribution graph
        generateSentimentDistribution(outputFile);

        outputFile.close();
        cout << "Summary Report Generated to: " << outputFilename << endl;

        // ... (keep sorting and searching sections)

        string wordToSearch = "great";

        cout << "\n=======SEARCH PERFORMANCE COMPARISON========\n";

        cout << "Word searched: \"" << wordToSearch << "\"\n";

        // Linear Search
        int linearFreq = allWords.linearSearch(wordToSearch);

        // Two-Pointer Search
        int twoPointerFreq = allWords.twoPointerSearch(wordToSearch);

        cout << "Linear Search result: Frequency = " << linearFreq << "\n";
        cout << "Two-Pointer Search result: Frequency = " << twoPointerFreq << "\n";
    }

    int getTotalReviews() const { return totalReviews; }
    int getTotalPositiveWords() const { return totalPositiveWords; }
    int getTotalNegativeWords() const { return totalNegativeWords; }

private:
    // Method to convert cleaned reviews to linked list
    void convertArrayToLinkedList(const ReviewContainer &reviews)
    {
        // Convert the array-based reviews to our linked list structure
        for (int i = 0; i < reviews.getReviewCount(); ++i)
        {
            Review review = reviews.getReview(i); // This gets a cleaned review
            reviewLinkedList.insert(review.text);
        }
        cout << "Converted " << reviews.getReviewCount() << " reviews to linked list.\n";
    }

    void analyzeReviewsInLinkedList()
    {
        Node<std::string> *current = reviewLinkedList.getHead();
        while (current != nullptr)
        {
            analyzeReview(current->data);
            current = current->next;
        }
    }

    void analyzeReview(const string &review)
    {
        cout << "Analyzing review: " << review << endl;
        istringstream iss(review);
        string word;
        while (iss >> word)
        {
            // Normalize word: convert to lowercase
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            // Remove any trailing punctuation (for simplicity, just common cases)
            word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());

            // Check if it's a positive or negative word
            if (positiveWords.contains(word))
            {
                totalPositiveWords++;
                allWords.insert(word);
            }
            if (negativeWords.contains(word))
            {
                totalNegativeWords++;
                allWords.insert(word);
            }
        }
        cout << "Finished analyzing review." << endl;
    }

    // void generateHistogram(ofstream &outputFile, int maxBars = 20)
    // {
    //     outputFile << "\n9. WORD FREQUENCY HISTOGRAM\n";

    //     LinkedList<WordFrequency> frequencies = getWordFrequencies();

    //     // Find maximum frequency for Histogram scalling
    //     Node<WordFrequency> *current = frequencies.getHead();
    //     int maxFreq = 0;
    //     while (current != nullptr)
    //     {
    //         if (current->data.frequency > maxFreq)
    //             maxFreq = current->data.frequency;
    //         current = current->next;
    //     }

    //     // Get Histogram for the first maxBars words
    //     current = frequencies.getHead();
    //     int shown = 0;
    //     while (current != nullptr && shown < maxBars)
    //     {
    //         int barLength = (current->data.frequency * 50) / maxFreq;
    //         outputFile << std::setw(15) << std::left << current->data.word << " |";
    //         for (int i = 0; i < barLength; i++)
    //             outputFile << "█";
    //         outputFile << " " << current->data.frequency << "\n";
    //         current = current->next;
    //         shown++;
    //     }
    // }

    // TestingGgggggggggggggggg

    void generateHistogram(ofstream &outputFile, int maxBars = 20)
    {
        outputFile << "\n9. WORD FREQUENCY HISTOGRAM\n";

        // Create two copies of the frequency list for comparison
        // LinkedList<WordFrequency> bubbleSortList = getWordFrequencies();
        LinkedList<WordFrequency> insertionSortList = getWordFrequencies();

        // Time bubble sort
        // auto startBubble = std::chrono::high_resolution_clock::now();
        // bubbleSortList.bubbleSort();
        // auto endBubble = std::chrono::high_resolution_clock::now();
        // auto bubbleDuration = std::chrono::duration_cast<std::chrono::microseconds>(endBubble - startBubble);

        // Time insertion sort
        auto startInsertion = std::chrono::high_resolution_clock::now();
        insertionSortList.insertionSort();
        auto endInsertion = std::chrono::high_resolution_clock::now();
        auto insertionDuration = std::chrono::duration_cast<std::chrono::microseconds>(endInsertion - startInsertion);

        // Output sorting times
        // cout << "Bubble Sort Time: " << insertionDuration.count() << " microseconds\n";
        cout << "\nInsertion Sort Time: " << insertionDuration.count() << " ns\n\n";

        // Use any sort list for histogram (you could use either one)
        Node<WordFrequency> *current = insertionSortList.getHead();

        // Node<WordFrequency> *current = insertionSortList.getHead();

        // Find maximum frequency for scaling
        int maxFreq = 0;
        while (current != nullptr)
        {
            if (current->data.frequency > maxFreq)
                maxFreq = current->data.frequency;
            current = current->next;
        }

        // Generate histogram
        current = insertionSortList.getHead();

        int shown = 0;
        while (current != nullptr && shown < maxBars)
        {
            int barLength = (current->data.frequency * 50) / maxFreq;
            outputFile << std::setw(15) << std::left << current->data.word << " |";
            for (int i = 0; i < barLength; i++)
                outputFile << "█";
            outputFile << " " << current->data.frequency << "\n";
            current = current->next;
            shown++;
        }
    }

    void generateSentimentDistribution(ofstream &outputFile) const
    {
        outputFile << "\n10. SENTIMENT DISTRIBUTION GRAPH\n";
        int total = totalPositiveWords + totalNegativeWords;
        if (total == 0)
            return;

        int positiveBar = (totalPositiveWords * 50) / total;
        int negativeBar = (totalNegativeWords * 50) / total;

        outputFile << "Positive |";
        for (int i = 0; i < positiveBar; i++)
            outputFile << "█";
        outputFile << " " << totalPositiveWords << " ("
                   << std::fixed << std::setprecision(1)
                   << (static_cast<double>(totalPositiveWords) / total * 100) << "%)\n";

        outputFile << "Negative |";
        for (int i = 0; i < negativeBar; i++)
            outputFile << "█";
        outputFile << " " << totalNegativeWords << " ("
                   << std::fixed << std::setprecision(1)
                   << (static_cast<double>(totalNegativeWords) / total * 100) << "%)\n";
    }
};

#endif // SUMMARYREPORTGENERATOR_H
