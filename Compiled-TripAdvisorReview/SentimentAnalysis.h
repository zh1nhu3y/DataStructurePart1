
/**
 *  SentimentAnalysis.cpp
 *  -> This class
 */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Struct to store words found in a linked list
struct WordNode
{
    string word;
    WordNode *next;

    WordNode(const string &w) : word(w), next(nullptr) {}
};

// Struct to store review data with sentiment analysis
struct SentimentNode
{
    string review;
    int rating;
    int positiveCount;
    int negativeCount;
    double sentimentScore;
    WordNode *positiveWordsList;
    WordNode *negativeWordsList;
    SentimentNode *next;

    SentimentNode(const string &r, int rt) : review(r), rating(rt), positiveCount(0), negativeCount(0), sentimentScore(0.0),
                                             positiveWordsList(nullptr), negativeWordsList(nullptr), next(nullptr) {}
};

class SentimentLinkedList
{
private:
    SentimentNode *head;
    WordArray &positiveWords; // Array of positive words
    WordArray &negativeWords; // Array of negative words
    int size;

public:
    // Constructor
    SentimentLinkedList(WordArray &posWords, WordArray &negWords)
        : head(nullptr), positiveWords(posWords), negativeWords(negWords), size(0) {}

    // Destructor
    ~SentimentLinkedList()
    {
        SentimentNode *current = head;
        while (current)
        {
            deleteList(current->positiveWordsList);
            deleteList(current->negativeWordsList);
            SentimentNode *temp = current;
            current = current->next;
            delete temp;
        }
    }

    SentimentNode* getNodeAt(int index) const; 

    // Function to delete word linked list (for destructor)
    void deleteList(WordNode *node)
    {
        while (node)
        {
            WordNode *temp = node;
            node = node->next;
            delete temp;
        }
    }

    //  Add a new review to linked list at the end
    void insertAtEnd(const string &review, int rating)
    {
        SentimentNode *newNode = new SentimentNode(review, rating);

        if (!head)
        {
            head = newNode;
        }
        else
        {
            SentimentNode *current = head;
            while (current->next)
            {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    // Return size of linked list
    int getSize()
    {
        return size;
    }


    //  Sentiment Analysis for one review
    void analyzeReview(SentimentNode *node)
    {
        string lowerReview = node->review;
        transform(lowerReview.begin(), lowerReview.end(), lowerReview.begin(), ::tolower);

        istringstream iss(lowerReview);
        string word;

        // Count positive and negative words and store them in lists
        while (iss >> word)
        {
            if (binarySearchSentiment(positiveWords, word))
            {
                node->positiveCount++;
                addToList(node->positiveWordsList, word); // Add positive word to list
            }
            if (binarySearchSentiment(negativeWords, word))
            {
                node->negativeCount++;
                addToList(node->negativeWordsList, word); // Add negative word to list
            }
        }

        // Calculate raw score
        int rawScore = node->positiveCount - node->negativeCount;
        int N = node->positiveCount + node->negativeCount;

        if (N > 0)
        {
            int minRawScore = -N;
            int maxRawScore = +N;
            double normalizedScore = static_cast<double>(rawScore - minRawScore) / (maxRawScore - minRawScore);
            node->sentimentScore = 1 + (4 * normalizedScore);
        }
        else
        {
            node->sentimentScore = 3;
        }
    }

    // Binary Search to search words in review
    bool binarySearchSentiment(const WordArray &words, const string &word) const
    {
        // auto start = high_resolution_clock::now();
        int low = 0;
        int high = words.getWordCount() - 1;

        while (low <= high)
        {
            int mid = (low + high) / 2;
            const string &midWord = words.getWordAt(mid);

            if (midWord == word)
            {
                // auto stop = high_resolution_clock::now();
                // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                // cout << "Linked List Binary Search Time: " << duration.count() << " milliseconds" << endl;
                return true; // Word found
            }
            else if (midWord < word)
            {
                low = mid + 1; // Search in the right half
            }
            else
            {
                high = mid - 1; // Search in the left half
            }
        }
        // auto stop = high_resolution_clock::now();
        // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start) / 1000;
        // cout << "Linked List Binary Search Time: " << duration.count() << " seconds" << endl;
        return false; // Word not found
    }

    //  Analyze all reviews in the linked list
    void analyzeSentiment()
    {
        SentimentNode *current = head;
        int count = 0;
        while (current)
        {
            analyzeReview(current);
            // cout << "Analyzed sentiment for review " << ++count << endl;
            current = current->next;
            ++count;
        }
        cout << "Total Review Analyzed: " << count << endl;
    }

    //  Add a word to a linked list
    void addToList(WordNode *&listHead, const string &word)
    {
        WordNode *newWord = new WordNode(word);
        if (!listHead)
        {
            listHead = newWord;
        }
        else
        {
            WordNode *current = listHead;
            while (current->next)
            {
                current = current->next;
            }
            current->next = newWord;
        }
    }

    // Save sentiment analysis results to a file
    void saveResultsToFile(const string &filename)
    {
        ofstream outFile(filename);
        if (!outFile)
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        SentimentNode *current = head;
        while (current)
        {
            outFile << "Review: " << current->review << "\n"
                    << endl;
            outFile << "Positive Words Count: " << current->positiveCount << endl;
            outFile << "Positive Words Found: ";
            writeWordsToFile(outFile, current->positiveWordsList);
            outFile << "Negative Words Count: " << current->negativeCount << endl;
            outFile << "Negative Words Found: ";
            writeWordsToFile(outFile, current->negativeWordsList);
            outFile << "Sentiment Score: " << current->sentimentScore << endl;
            outFile << "Given Rating: " << current->rating << endl;
            outFile << "----------------------------------------" << endl;
            current = current->next;
        }

        outFile.close();
        cout << "Sentiment Analysis Results saved to: " << filename << endl;
    }

    // Write list of words from a linked list to the file
    void writeWordsToFile(ofstream &outFile, WordNode *listHead)
    {
        WordNode *current = listHead;
        if (listHead == nullptr)
        {
            outFile << "-";
        }
        while (current)
        {
            outFile << current->word << " ";
            current = current->next;
        }
        outFile << endl;
    }

    // Bubble sort to sort the reviews by sentiment score in ascending order
    void bubbleSortSentiment()
    {
        if (head->next == nullptr)
            return;

        bool swapped;
        do
        {
            swapped = false;
            SentimentNode *current = head;
            SentimentNode *prev = nullptr;
            SentimentNode *nextNode = nullptr;

            while (current->next)
            {
                nextNode = current->next;
                if (current->sentimentScore > nextNode->sentimentScore)
                {
                    // Swap nodes
                    if (prev)
                    {
                        prev->next = nextNode;
                    }
                    else
                    {
                        head = nextNode;
                    }
                    current->next = nextNode->next;
                    nextNode->next = current;
                    swapped = true;
                }
                prev = current;
                current = nextNode;
            }
        } while (swapped);

        cout << "Reviews sorted by sentiment score." << endl;
    }

    // Insertion Sort function for the linked list
    void insertionSort() {
        if (!head || !head->next) return; // If list is empty or has only one element

        SentimentNode* sorted = nullptr; // This will hold the sorted portion of the list

        SentimentNode* current = head;
        while (current) {
            SentimentNode* next = current->next; // Store next node
            // Insert current node in sorted linked list
            if (!sorted || sorted->rating >= current->rating) {
                current->next = sorted;
                sorted = current;
            } else {
                SentimentNode* temp = sorted;
                while (temp->next && temp->next->rating < current->rating) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }

        head = sorted; // Update the head to point to the sorted list
    }

    // Quick sort function for linked list based on rating
    void quickSort(SentimentNode* head, SentimentNode* low, SentimentNode* high) {
        if (low != high && low != nullptr && high != nullptr && low != high->next) {
            // Partition the list and get the pivot node
            SentimentNode* pivot = partition(low, high);

            // QuickSort the left side (before the pivot)
            quickSort(head, low, getTailBefore(head, pivot));  // Get the node just before the pivot

            // QuickSort the right side (after the pivot)
            quickSort(head, pivot->next, high);
        }
    }




    // Partition function for quick sort
    SentimentNode* partition(SentimentNode* low, SentimentNode* high) {
        int pivotRating = high->rating;  // Use the rating of the high node as pivot
        SentimentNode* i = low;          // Start with the low node
        SentimentNode* j = low;          // Traverse the list with j

        // Traverse from low to high and swap elements that are smaller than the pivot
        while (j != high) {
            if (j->rating <= pivotRating) {
                // Swap ratings and reviews between i and j
                std::swap(i->rating, j->rating);
                std::swap(i->review, j->review);
                i = i->next;  // Move i to the next node
            }
            j = j->next;
        }

        // Finally, swap the pivot (high) with the current i position
        std::swap(i->rating, high->rating);
        std::swap(i->review, high->review);

        return i;  // i is now the pivot
    }



    // Helper function to swap two nodes in the linked list
    void swap(SentimentNode* a, SentimentNode* b) {
        int tempRating = a->rating;
        a->rating = b->rating;
        b->rating = tempRating;
    }

    SentimentNode* getTailBefore(SentimentNode* head, SentimentNode* pivot) {
    if (head == nullptr || head == pivot) return nullptr;

    SentimentNode* current = head;
    while (current->next != pivot && current->next != nullptr) {
        current = current->next;
    }
    return current;
}



    SentimentNode *getHead()
    {
        return head;
    }

    SentimentNode* getTail() {
    SentimentNode* current = head;
        if (!current) return nullptr;  // If head is nullptr, the list is empty
        while (current->next != nullptr) {
            current = current->next;  // Traverse to the last node
        }
        return current;  // Return the last node (tail)
    }   

    // Linear search function to find all reviews with a specific rating
    int* linearSearchAll(SentimentNode* head, int targetRating, int &resultCount)
    {
        resultCount = 0;
        // Dynamically allocate memory to store result indices
        int* indices = new int[getSize()];  
               // Traverse the entire linked list to find all matching ratings
        SentimentNode* current = head;
        int index = 0;
        while (current != nullptr)
        {
            if (current->rating == targetRating)
            {
                indices[resultCount] = index;
                resultCount++;
            }
            current = current->next;
            index++;
        }

        // If no matches were found, return nullptr
        if (resultCount == 0)
        {
            delete[] indices;  // No matches, so clean up and return nullptr
            return nullptr;
        }

        return indices;  // Return array of indices for matching reviews
    }

    int* binarySearchAllLinkedList(const SentimentLinkedList &reviews, int targetRating, int &resultCount) {
        int size = getSize();
        
        if (size == 0) {
            return nullptr;  // If the list is empty, return nullptr
        }

        int* indices = new int[size];
        resultCount = 0;

        int low = 0;
        int high = size - 1;

        // Perform binary search on the linked list
        while (low <= high) {
            // Find the middle index (this is a slow O(n) process in a linked list)
            int mid = low + (high - low) / 2;
            SentimentNode* midNode = reviews.getNodeAt(mid);  // Traverse to get the node at 'mid'

            if (midNode == nullptr) {
                break;
            }

            int midRating = midNode->rating;  // Get the rating of the node

            if (midRating == targetRating) {
                // If the targetRating is found at mid, store the index
                indices[resultCount] = mid;
                resultCount++;

                // Search to the left and right of the found element
                int left = mid - 1;
                while (left >= 0 && reviews.getNodeAt(left)->rating == targetRating) {
                    indices[resultCount] = left;
                    resultCount++;
                    left--;
                }

                int right = mid + 1;
                while (right < size && reviews.getNodeAt(right)->rating == targetRating) {
                    indices[resultCount] = right;
                    resultCount++;
                    right++;
                }

                break;  // Break after finding all the matches
            } 
            else if (midRating < targetRating) {
                low = mid + 1;
            } 
            else {
                high = mid - 1;
            }
        }

        if (resultCount == 0) {
            delete[] indices;  // If no results found, return nullptr
            return nullptr;
        }

        return indices;  // Return indices of found reviews
    }

    // Function to display all reviews matching the search rating in the linked list
    void displaySearchedReviews(int searchRating) {
        SentimentNode* current = head;
        bool found = false;

        // Traverse the list and print the reviews with the target rating
        while (current != nullptr) {
            if (current->rating == searchRating) {
                std::cout << "Review: " << current->review << ", Rating: " << current->rating << std::endl;
                found = true;
            }
            current = current->next;
        }

        // If no matching reviews are found
        if (!found) {
            std::cout << "No reviews found with rating " << searchRating << "." << std::endl;
        }
    }

    void clear() {
        SentimentNode* current = head;
        SentimentNode* nextNode;

        // Traverse through the linked list
        while (current != nullptr) {
            nextNode = current->next;  // Store the next node
            delete current;            // Delete the current node
            current = nextNode;        // Move to the next node
        }

        head = nullptr;  // Reset head to null, indicating the list is empty
    }

    void bubbleSortLinkedList() {
    if (head == nullptr) return;

    SentimentNode* current = head;
    SentimentNode* next = nullptr;
    bool swapped;

    do {
        swapped = false;
        current = head;

        while (current->next != nullptr) {
            next = current->next;
            if (current->rating > next->rating) {
                std::swap(current->rating, next->rating);
                swapped = true;
            }
            current = next;
        }
    } while (swapped);
}

void displaySentimentAnalysisResults()
{
    // Check if the list is empty
    if (head == nullptr)
    {
        cout << "No reviews available for sentiment analysis." << endl;
        return;
    }

    SentimentNode *current = head;  // Start from the head of the linked list

    while (current)
    {
        // Output the current review's details to the console
        cout << "Review: " << current->review << "\n" << endl;

        cout << "Positive Words Count: " << current->positiveCount << endl;
        cout << "Positive Words Found: ";
        // Custom function to display words in a list
        displayWords(current->positiveWordsList);

        cout << "Negative Words Count: " << current->negativeCount << endl;
        cout << "Negative Words Found: ";
        // Custom function to display words in a list
        displayWords(current->negativeWordsList);

        // Output sentiment score and rating
        cout << "Sentiment Score: " << current->sentimentScore << endl;
        cout << "Given Rating: " << current->rating << endl;

        cout << "----------------------------------------" << endl;

        // Move to the next node in the linked list
        current = current->next;
    }
}

// Helper function to display the list of words (without using built-in containers)
void displayWords(WordNode *wordList)
{
    WordNode *currentWord = wordList;

    if (currentWord == nullptr)
    {
        cout << "None" << endl; // Handle case if no words are found
        return;
    }

    // Iterate through the word list and print each word
    while (currentWord)
    {
        cout << currentWord->word;
        if (currentWord->next != nullptr)
        {
            cout << ", ";  // Add a comma between words
        }
        currentWord = currentWord->next;
    }
    cout << endl;  // End the line after printing all words
}


    
};

// Function to get the node at a specific index
    SentimentNode* SentimentLinkedList::getNodeAt(int index) const
    {
        SentimentNode* current = head;
        for (int i = 0; i < index && current != nullptr; ++i)
        {
            current = current->next;
        }
        return current;
    }

