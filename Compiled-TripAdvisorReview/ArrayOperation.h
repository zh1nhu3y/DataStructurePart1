/**
 * ArrayOperation.h
 */

#ifndef ARRAY_OPERATION_H
#define ARRAY_OPERATION_H

#include "ReviewContainer.h"
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

class ArrayOperation
{
public:
    // ============================ SORTING =====================================

    // Function to sort reviews by rating using insertion sort
    void insertionSortArray(CustomArray &reviews)
    {
        std::cout << "Start Sorting..." << std::endl;
        // Start measuring time
        auto start = std::chrono::high_resolution_clock::now();

        int n = reviews.getSize();
        for (int i = 1; i < n; i++)
        {
            // Get the current review and rating
            std::string keyReview = reviews.getReview(i);
            int keyRating = reviews.getRating(i);

            int j = i - 1;

            // Shift elements that are greater than keyRating to the right
            while (j >= 0 && reviews.getRating(j) > keyRating)
            {
                // Move the elements to the right
                reviews.setReview(j + 1, reviews.getReview(j));
                reviews.setRating(j + 1, reviews.getRating(j));
                j--;
            }

            // Place the current key element in the correct position
            reviews.setReview(j + 1, keyReview);
            reviews.setRating(j + 1, keyRating);
        }

        // Update the size of the array (if necessary)
        reviews.setSize(n); // Optional, to ensure the size reflects the number of sorted elements

        // Stop measuring time
        auto stop = std::chrono::high_resolution_clock::now();
        duration<double> duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << "End Sorting..." << std::endl;
        std::cout << "\nTime taken for insertion sorting: " << duration.count() << " milliseconds" << std::endl;
    }



    // Function to sort reviews by rating using bubble sort
    void bubbleSortArray(CustomArray &reviews) {
    // Start measuring time
    auto start = high_resolution_clock::now();

    int n = reviews.getSize();
    bool swapped;
    
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (reviews.getRating(j) > reviews.getRating(j + 1)) {
                // Swap review and rating
                std::string tempReview = reviews.getReview(j);
                int tempRating = reviews.getRating(j);

                // Directly swap elements
                reviews.setReview(j, reviews.getReview(j + 1));
                reviews.setRating(j, reviews.getRating(j + 1));

                reviews.setReview(j + 1, tempReview);
                reviews.setRating(j + 1, tempRating);

                swapped = true;
            }
        }
        // If no two elements were swapped, break
        if (!swapped)
            break;
    }

    // Stop measuring time
    auto stop = high_resolution_clock::now();
    duration<double> duration = duration_cast<milliseconds>(stop - start);
    
    cout << "\nTime taken for bubble sorting: " << duration.count() << " milliseconds" << endl;
}
    // Function to display reviews
    void displayReviews(const CustomArray &reviews)
    {
        for (int i = 0; i < reviews.getSize(); i++)
        {
            std::cout << "Review: \"" << reviews.getReview(i) 
                      << "\", Rating: " << reviews.getRating(i)
                      << "\n -----------------------------------------" << std::endl;
        }
    }

    // Function to display reviews in a table format
    void displayReviewsTable(const CustomArray &reviews)
    {
        const int maxReviewLength = 150; // Maximum length for the review display
        const int reviewColumnWidth = 100; // Width of the review column
        const int ratingColumnWidth = 20; // Width of the columns for ratings
        const std::string separator = " -----------------------------------------";

        // Print the header
        std::cout << separator << std::endl;
        std::cout << std::left << std::setw(10) << "No."
              << std::setw(reviewColumnWidth) << "Review"
              << std::setw(ratingColumnWidth) << "Rating" << std::endl;
        std::cout << separator << std::endl;

        for (int i = 0; i < reviews.getSize(); i++)
        {
            std::string review = reviews.getReview(i);
            // Truncate the review if it exceeds the max length
            if (review.length() > maxReviewLength)
            {
                review = review.substr(0, maxReviewLength) + "..."; // Indicate truncation
            }

            // Display the review number, review text, and rating
        std::cout << std::left << std::setw(10) << i + 1 // Review number
                  << std::setw(reviewColumnWidth) << review  // Review text
                  << std::setw(ratingColumnWidth) << reviews.getRating(i) << std::endl; // Rating
        }

        std::cout << separator << std::endl;
    }

        // Function to swap two elements in the array
    void swapReviews(CustomArray &reviews, int i, int j)
    {
        std::string tempReview = reviews.getReview(i);
        int tempRating = reviews.getRating(i);

        reviews.setReview(i, reviews.getReview(j));
        reviews.setRating(i, reviews.getRating(j));

        reviews.setReview(j, tempReview);
        reviews.setRating(j, tempRating);
    }

    // Partition function for quicksort
    int partition(CustomArray &reviews, int low, int high)
    {
        int pivot = reviews.getRating(high);  // Last element as pivot
        int i = (low - 1);  // Index of smaller element

        for (int j = low; j < high; j++)
        {
            // If current rating is less than or equal to pivot
            if (reviews.getRating(j) <= pivot)
            {
                i++;
                swapReviews(reviews, i, j);
            }
        }

        // Swap the pivot with the element at i + 1
        swapReviews(reviews, i + 1, high);
        return (i + 1);  // Return the partition index
    }

    // Quicksort function
    void quickSort(CustomArray &reviews, int low, int high)
    {
        if (low < high)
        {
            // Partitioning index
            int pi = partition(reviews, low, high);

            // Recursively apply quicksort to the sublists
            quickSort(reviews, low, pi - 1);   // Left sublist
            quickSort(reviews, pi + 1, high);  // Right sublist
        }
    }

    // =============================== SEARCH =======================================
    
    // Linear search algorithm for all reviews
    int* linearSearchAll(const CustomArray &reviews, int targetRating, int &resultCount)
    {
        // Assume maximum possible matches could be equal to the total number of reviews
        int* indices = new int[reviews.getSize()];
        resultCount = 0;

        // Traverse through all reviews and collect matching ratings
        for (int i = 0; i < reviews.getSize(); i++)
        {
            if (reviews.getRating(i) == targetRating)
            {
                indices[resultCount] = i;  // Store index
                resultCount++;              // Increment match count
            }
        }

        if (resultCount == 0)
        {
            delete[] indices;  // Clean up memory if no matches
            return nullptr;    // Return null pointer if no matches found
        }

        return indices;  // Return the dynamically allocated array of matching indices
    }

    // Binary search algorithm
    int binarySearch(const CustomArray &reviews, int targetRating, int low, int high)
    {
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            int midRating = reviews.getRating(mid);

            if (midRating == targetRating)
                return mid;  // Return the index if found

            if (midRating < targetRating)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return -1;  // Return -1 if the rating is not found
    }

    // Binary search algorithm for all reviews
    int* binarySearchAll(const CustomArray &reviews, int targetRating, int &resultCount)
    {
        int low = 0;
        int high = reviews.getSize() - 1;

        // First, find any occurrence of the target rating
        int index = binarySearch(reviews, targetRating, low, high);
        if (index == -1)
        {
            return nullptr;  // No matching rating found
        }

        // Assume maximum possible matches could be equal to the total number of reviews
        int* indices = new int[reviews.getSize()];
        resultCount = 0;

        // Collect indices in both left and right directions
        // Add the index found
        indices[resultCount] = index;
        resultCount++;

        // Search to the left for more matches
        int left = index - 1;
        while (left >= 0 && reviews.getRating(left) == targetRating)
        {
            indices[resultCount] = left;
            resultCount++;
            left--;
        }

        // Search to the right for more matches
        int right = index + 1;
        while (right < reviews.getSize() && reviews.getRating(right) == targetRating)
        {
            indices[resultCount] = right;
            resultCount++;
            right++;
        }

        return indices;  // Return array of indices for matching reviews
    }

    // Binary search algorithm for searching words
    int binarySearchWord(const WordArray &words, const std::string &targetWord, int low, int high)
    {
        auto start = high_resolution_clock::now();
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            std::string midWord = words.getWordAt(mid);

            if (midWord == targetWord)
            {
                auto stop = high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start) / 1000;
                cout << "Array Binary Search Time: " << duration.count() << " seconds" << endl;
                return mid;  // Word found
            }
            if (midWord < targetWord)
                low = mid + 1;
            else
                high = mid - 1;
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start) / 1000;
        cout << "Array Binary Search Time: " << duration.count() << " seconds" << endl;
        return -1;  // Word not found
    }

    // Binary search algorithm for all occurrences of a word
    int* binarySearchAllWords(const WordArray &words, const std::string &targetWord, int &resultCount)
    {
        auto start = high_resolution_clock::now();
        int low = 0;
        int high = words.getWordCount() - 1;

        int index = binarySearchWord(words, targetWord, low, high);
        if (index == -1)
            return nullptr;

        int* indices = new int[words.getWordCount()];
        resultCount = 0;

        indices[resultCount++] = index;

        int left = index - 1;
        while (left >= 0 && words.getWordAt(left) == targetWord)
        {
            indices[resultCount++] = left;
            left--;
        }

        int right = index + 1;
        while (right < words.getWordCount() && words.getWordAt(right) == targetWord)
        {
            indices[resultCount++] = right;
            right++;
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start) / 1000;
        cout << "Array Binary Search Time: " << duration.count() << " seconds" << endl;
        return indices;
    }

    // Function to display reviews based on the indices returned by binarySearchAll
    void displaySearchedReviews(const CustomArray &reviews, int* indices, int resultCount)
    {
        if (resultCount == 0 || indices == nullptr)
        {
            std::cout << "No reviews found with the specified rating." << std::endl;
            return;
        }

        const int maxReviewLength = 200;  // Maximum length for the review display
        const int reviewColumnWidth = 200;  // Width of the review column
        const int ratingColumnWidth = 20;  // Width of the columns for ratings
        const std::string separator = "-----------------------------------------";

        // Print the header
        std::cout << separator << std::endl;
        std::cout << std::left << std::setw(10) << "No."
                << std::setw(reviewColumnWidth) << "Review"
                << std::setw(ratingColumnWidth) << "Rating" << std::endl;
        std::cout << separator << std::endl;

        // Loop through the indices and display corresponding reviews
        for (int i = 0; i < resultCount; i++)
        {
            int index = indices[i];
            std::string review = reviews.getReview(index);

            // Truncate the review if it exceeds the max length
            if (review.length() > maxReviewLength)
            {
                review = review.substr(0, maxReviewLength) + "...";  // Indicate truncation
            }

            // Display the review number, review text, and rating
            std::cout << std::left << std::setw(10) << i + 1
                    << std::setw(reviewColumnWidth) << review
                    << std::setw(ratingColumnWidth) << reviews.getRating(index) << std::endl;
        }

        std::cout << separator << std::endl;
    }

};


#endif // ARRAY_OPERATIONS_H