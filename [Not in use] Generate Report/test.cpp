// WordNode.hpp
#ifndef WORDNODE_HPP
#define WORDNODE_HPP

#include <string>

using namespace std;

struct WordNode {
    string word;
    int frequency;
    WordNode* next;
    
    WordNode(const string& w) : word(w), frequency(1), next(nullptr) {}
};



// SentimentAnalyzer.hpp
class SentimentAnalyzer    {
private:
    WordNode* positiveHead;
    WordNode* negativeHead;
    int totalReviews;
    int totalPositiveWords;
    int totalNegativeWords;
    
    void insertWord(WordNode*& head, const std::string& word) {
        WordNode* found = LinkedListAlgorithms::linearSearch(head, word);
        if (found) {
            found->frequency++;
        } else {
            WordNode* newNode = new WordNode(word);
            newNode->next = head;
            head = newNode;
        }
    }
    
public:
    SentimentAnalyzer() : positiveHead(nullptr), negativeHead(nullptr),
                          totalReviews(0), totalPositiveWords(0), totalNegativeWords(0) {}
    
    ~SentimentAnalyzer() {
        // Cleanup
        while (positiveHead) {
            WordNode* temp = positiveHead;
            positiveHead = positiveHead->next;
            delete temp;
        }
        while (negativeHead) {
            WordNode* temp = negativeHead;
            negativeHead = negativeHead->next;
            delete temp;
        }
    }
    
    void analyzeReview(const string& review, const WordArray& positiveWords, const WordArray& negativeWords) {
        std::istringstream words(review);
        std::string word;
        totalReviews++;
        
        while (words > word) {
            std::string lowerWord = word;
            std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);
            
            if (positiveWords.contains(lowerWord)) {
                insertWord(positiveHead, lowerWord);
                totalPositiveWords++;
            }
            if (negativeWords.contains(lowerWord)) {
                insertWord(negativeHead, lowerWord);
                totalNegativeWords++;
            }
        }
    }
    
    void generateReport(ofstream& outFile) {
        outFile << "\nSENTIMENT ANALYSIS REPORT\n";
        outFile << "========================\n\n";
        
        outFile << "Overall Statistics:\n";
        outFile << "-----------------\n";
        outFile << "Total Reviews: " << totalReviews << "\n";
        outFile << "Total Positive Words: " << totalPositiveWords << "\n";
        outFile << "Total Negative Words: " << totalNegativeWords << "\n\n";
        
        // Sort words by frequency using bubble sort
        LinkedListAlgorithms::bubbleSort(positiveHead);
        LinkedListAlgorithms::bubbleSort(negativeHead);
        
        outFile << "Frequency of each word (ascending order):\n";
        outFile << "---------------------------------------\n";
        
        // Print positive words
        WordNode* current = positiveHead;
        while (current != nullptr) {
            outFile << std::setw(15) << current->word << " = " 
                    << current->frequency << " times\n";
            current = current->next;
        }
        
        // Print negative words
        current = negativeHead;
        while (current != nullptr) {
            outFile << std::setw(15) << current->word << " = " 
                    << current->frequency << " times\n";
            current = current->next;
        }
        
        // Find maximum and minimum used words
        outFile << "\nMaximum used words in reviews: ";
        if (positiveHead && negativeHead) {
            if (positiveHead->frequency > negativeHead->frequency) {
                outFile << positiveHead->word;
            } else {
                outFile << negativeHead->word;
            }
        }
        
        // Find minimum (we need to traverse to the end of the lists)
        WordNode* minPositive = positiveHead;
        WordNode* minNegative = negativeHead;
        
        while (minPositive && minPositive->next) minPositive = minPositive->next;
        while (minNegative && minNegative->next) minNegative = minNegative->next;
        
        outFile << "\nMinimum used word in reviews: ";
        if (minPositive && minNegative) {
            if (minPositive->frequency < minNegative->frequency) {
                outFile << minPositive->word;
            } else {
                outFile << minNegative->word;
            }
        }
    }
};