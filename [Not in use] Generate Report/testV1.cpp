// WordNode.hpp
#ifndef WORDNODE_HPP
#define WORDNODE_HPP

#include <string>

struct WordNode {
    std::string word;
    int frequency;
    WordNode* next;
    
    WordNode(const std::string& w) : word(w), frequency(1), next(nullptr) {}
};

#endif

// SentimentReporter.hpp
#ifndef SENTIMENTREPORTER_HPP
#define SENTIMENTREPORTER_HPP

#include <string>
#include <vector>
#include "WordNode.hpp"

class SentimentReporter {
private:
    WordNode* positiveHead;
    WordNode* negativeHead;
    int totalPositiveWords;
    int totalNegativeWords;
    int totalReviews;

    // Helper methods
    void insertWord(WordNode*& head, const std::string& word);
    void bubbleSort(WordNode*& head);
    void insertionSort(WordNode*& head);
    WordNode* linearSearch(WordNode* head, const std::string& word);
    WordNode* binarySearch(WordNode* head, const std::string& word);
    int getListLength(WordNode* head);
    
public:
    SentimentReporter();
    ~SentimentReporter();
    
    void addReview(const std::vector<std::string>& positiveWords, 
                   const std::vector<std::string>& negativeWords);
    void generateReport();
    void sortWordsByFrequency(bool useBubbleSort = true);
    
    // Getter methods for testing
    int getTotalPositiveWords() const { return totalPositiveWords; }
    int getTotalNegativeWords() const { return totalNegativeWords; }
    int getTotalReviews() const { return totalReviews; }
};

#endif

// SentimentReporter.cpp
#include "SentimentReporter.hpp"
#include <iostream>
#include <iomanip>

SentimentReporter::SentimentReporter() 
    : positiveHead(nullptr), negativeHead(nullptr), 
      totalPositiveWords(0), totalNegativeWords(0), totalReviews(0) {}

SentimentReporter::~SentimentReporter() {
    // Cleanup code for linked lists
    WordNode *current, *next;
    
    current = positiveHead;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    
    current = negativeHead;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
}

void SentimentReporter::insertWord(WordNode*& head, const std::string& word) {
    WordNode* found = linearSearch(head, word);
    if (found) {
        found->frequency++;
    } else {
        WordNode* newNode = new WordNode(word);
        newNode->next = head;
        head = newNode;
    }
}

void SentimentReporter::addReview(const std::vector<std::string>& positiveWords,
                                 const std::vector<std::string>& negativeWords) {
    totalReviews++;
    
    for (const auto& word : positiveWords) {
        insertWord(positiveHead, word);
        totalPositiveWords++;
    }
    
    for (const auto& word : negativeWords) {
        insertWord(negativeHead, word);
        totalNegativeWords++;
    }
}

void SentimentReporter::bubbleSort(WordNode*& head) {
    if (!head || !head->next) return;
    
    bool swapped;
    WordNode* current;
    WordNode* tail = nullptr;
    
    do {
        swapped = false;
        current = head;
        
        while (current->next != tail) {
            if (current->frequency < current->next->frequency) {
                // Swap nodes
                std::swap(current->word, current->next->word);
                std::swap(current->frequency, current->next->frequency);
                swapped = true;
            }
            current = current->next;
        }
        tail = current;
    } while (swapped);
}

void SentimentReporter::insertionSort(WordNode*& head) {
    if (!head || !head->next) return;
    
    WordNode* sorted = nullptr;
    WordNode* current = head;
    
    while (current != nullptr) {
        WordNode* next = current->next;
        
        if (!sorted || sorted->frequency <= current->frequency) {
            current->next = sorted;
            sorted = current;
        } else {
            WordNode* search = sorted;
            while (search->next != nullptr && 
                   search->next->frequency > current->frequency) {
                search = search->next;
            }
            current->next = search->next;
            search->next = current;
        }
        
        current = next;
    }
    
    head = sorted;
}

WordNode* SentimentReporter::linearSearch(WordNode* head, const std::string& word) {
    WordNode* current = head;
    while (current != nullptr) {
        if (current->word == word) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void SentimentReporter::sortWordsByFrequency(bool useBubbleSort) {
    if (useBubbleSort) {
        bubbleSort(positiveHead);
        bubbleSort(negativeHead);
    } else {
        insertionSort(positiveHead);
        insertionSort(negativeHead);
    }
}

void SentimentReporter::generateReport() {
    std::cout << "\nSENTIMENT ANALYSIS REPORT\n";
    std::cout << "========================\n\n";
    
    std::cout << "Overall Statistics:\n";
    std::cout << "-----------------\n";
    std::cout << "Total Reviews: " << totalReviews << "\n";
    std::cout << "Total Positive Words: " << totalPositiveWords << "\n";
    std::cout << "Total Negative Words: " << totalNegativeWords << "\n";
    
    double sentimentRatio = totalPositiveWords > 0 ? 
        static_cast<double>(totalPositiveWords) / (totalPositiveWords + totalNegativeWords) : 0;
    std::cout << "Overall Sentiment Ratio: " << std::fixed << std::setprecision(2) 
              << sentimentRatio * 100 << "%\n\n";
    
    // Sort words by frequency
    sortWordsByFrequency();
    
    std::cout << "Word Frequency Analysis:\n";
    std::cout << "----------------------\n";
    
    std::cout << "Top Positive Words:\n";
    WordNode* current = positiveHead;
    int count = 0;
    while (current != nullptr && count < 5) {
        std::cout << std::setw(15) << current->word << ": " 
                  << current->frequency << " times\n";
        current = current->next;
        count++;
    }
    
    std::cout << "\nTop Negative Words:\n";
    current = negativeHead;
    count = 0;
    while (current != nullptr && count < 5) {
        std::cout << std::setw(15) << current->word << ": " 
                  << current->frequency << " times\n";
        current = current->next;
        count++;
    }
    
    std::cout << "\nMost used words: ";
    if (positiveHead && negativeHead) {
        if (positiveHead->frequency > negativeHead->frequency) {
            std::cout << positiveHead->word << " (positive, " 
                      << positiveHead->frequency << " times)\n";
        } else {
            std::cout << negativeHead->word << " (negative, " 
                      << negativeHead->frequency << " times)\n";
        }
    }
    
    std::cout << "\nTrend Analysis:\n";
    std::cout << "--------------\n";
    if (sentimentRatio > 0.6) {
        std::cout << "Overall Positive Trend: Reviews are predominantly positive.\n";
    } else if (sentimentRatio < 0.4) {
        std::cout << "Overall Negative Trend: Reviews are predominantly negative.\n";
    } else {
        std::cout << "Neutral Trend: Reviews show a balance of positive and negative sentiment.\n";
    }
}