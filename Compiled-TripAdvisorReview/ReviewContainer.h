
/**
 *  ReviewContainer.h
 */
#ifndef REVIEW_CONTAINER_H
#define REVIEW_CONTAINER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <algorithm> // For std::transform
#include <cctype>    // For std::tolower

// Define a struct to hold review and rating together
struct ReviewRating
{
    std::string review;
    int rating;

    // Default constructor
    ReviewRating() : review(""), rating(0) {}

    // Constructor with parameters
    ReviewRating(const std::string &r, int ra) : review(r), rating(ra) {}
};

// Define a custom array class to handle dynamic storage
class CustomArray
{
    private:
        ReviewRating *data; // Pointer to dynamic array for reviews and ratings
        int capacity;       // Total capacity of the array
        int size;           // Current number of elements

        // Function to resize the array when it gets full
        void resize()
        {
            int newCapacity = capacity * 2;
            ReviewRating *newData = new ReviewRating[newCapacity]; // Array of ReviewRating

            // Copy the old data into the new array
            for (int i = 0; i < size; ++i)
            {
                newData[i] = data[i]; // Use copy constructor
            }

            // Free the old memory
            delete[] data;

            // Assign new array to the pointer
            data = newData;
            capacity = newCapacity;
        }

    public:
        // Constructor to initialize the array
        CustomArray(int initialCapacity = 10) : capacity(initialCapacity), size(0)
        {
            data = new ReviewRating[capacity]; // Array of ReviewRating
        }

        // Destructor to free memory
        ~CustomArray()
        {
            delete[] data;
        }

        // Add a new review and rating to the array
        void add(const std::string &review, int rating)
        {
            if (size == capacity)
            {
                resize(); // Resize if necessary
            }
            data[size] = ReviewRating(review, rating); // Create a new ReviewRating instance
            ++size;
        }

        // Function to get the review at a specific index
        std::string getReview(int index) const
        {
            if (index >= 0 && index < size)
            {
                return data[index].review;
            }
            return "";
        }

        // Function to get the rating at a specific index
        int getRating(int index) const
        {
            if (index >= 0 && index < size)
            {
                return data[index].rating;
            }
            return -1;
        }

        // Get the total number of elements
        int getSize() const
        {
            return size;
        }

        // Write cleaned reviews and ratings to a CSV file
        void writeToFile(const std::string &outputFile) const
        {
            std::ofstream outFile(outputFile);
            if (!outFile.is_open())
            {
                std::cerr << "Error opening output file!" << std::endl;
                return;
            }

            // Write header
            outFile << "Review,Rating\n";

            // Write cleaned data
            for (int i = 0; i < size; ++i)
            {
                outFile << "\"" << data[i].review << "\"," << data[i].rating << "\n"; // Use quotes to avoid commas in the review text causing issues
            }

            outFile.close();
            std::cout << "Cleaned data written to " << outputFile << std::endl;
        }

        // Function to remove an element at a specific index
        void removeAt(int index)
        {
            if (index < 0 || index >= size)
            {
                std::cerr << "Index out of bounds!" << std::endl;
                return;
            }

            // Shift elements to the left to fill the gap
            for (int i = index; i < size - 1; ++i)
            {
                data[i] = data[i + 1];
            }
            --size; // Decrease the size
        }

        // Set the size of the array
        void setSize(int newSize) {
            if (newSize >= 0 && newSize <= capacity) {
                size = newSize; // Update the size variable
            }
        }

    // Set a review at a specific index
    void setReview(int index, const std::string& review) {
        if (index >= 0 && index < size) {
            data[index].review = review; // Update the review in the ReviewRating struct
        } else {
            std::cerr << "Index out of range for setting review." << std::endl;
        }
    }

    // Set a rating at a specific index
    void setRating(int index, int rating) {
        if (index >= 0 && index < size) {
            if (rating >= 1 && rating <= 5) { // Ensure rating is between 1 and 5
                data[index].rating = rating; // Update the rating in the ReviewRating struct
            } else {
                std::cerr << "Rating must be between 1 and 5." << std::endl;
            }
        } else {
            std::cerr << "Index out of range for setting rating." << std::endl;
        }
    }

    int getValue(int index) const {
        return getRating(index);  
    }

    // Clear the array
    void clear() {
        size = 0;
    }
        
    };

    // Function to trim leading/trailing whitespaces
    std::string trim(const std::string &str)
    {
        size_t start = str.find_first_not_of(' ');
        size_t end = str.find_last_not_of(' ');
        if (start == std::string::npos || end == std::string::npos)
        {
            return ""; // If there are no non-whitespace characters
        }
        return str.substr(start, end - start + 1);
    }

    // Function to clean a review by applying all cleaning functions
    std::string advancedCleanReview(const std::string &review)
    {
        std::string result = review;

        // Step 1: Convert the entire string to lowercase
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);

        // Step 2: Replace multiple spaces with a single space
        result = std::regex_replace(result, std::regex("\\s{2,}"), " ");

        // Step 3: Remove special characters (like _Ç_, etc.) except for contractions
        // Keep apostrophes intact for contractions
        result = std::regex_replace(result, std::regex("[^a-zA-Z0-9\\s,.!?'-]"), " ");

        // Step 4: Remove extra commas or misplaced punctuation
        result = std::regex_replace(result, std::regex("[.,!?;:\"(){}\\[\\]<>/\\\\-]"),"");

        // Step 5: Trim leading and trailing spaces
        result = trim(result);

        return result;
    }

    // Function to read, clean, and store the CSV data
    void cleanCSV(const std::string &inputFile, CustomArray &reviews)
    {
        std::cout << "Loading reviews from " << inputFile << std::endl;
        std::ifstream inFile(inputFile);

        if (!inFile.is_open())
        {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }

        std::string line, review;
        int rating;

        // Skip the header
        std::getline(inFile, line);

        // Process each line (review and rating)
        while (std::getline(inFile, line))
        {
            std::stringstream ss(line);

            // Extract the review, which may be enclosed in quotes if it contains commas
            if (line[0] == '"')
            {
                size_t pos = line.find("\",");
                if (pos != std::string::npos)
                {
                    review = line.substr(1, pos - 1); // Extract the review text inside quotes
                    ss.seekg(pos + 2);                // Move past the end of the review
                    ss >> rating;                     // Read the rating (should be after the comma)
                }
            }
            else
            {
                std::getline(ss, review, ',');
                ss >> rating; // Assuming the rating follows the review
            }

            // Clean the review text with advanced cleaning
            review = advancedCleanReview(review);

            // Add the cleaned review and rating to the custom array
            reviews.add(review, rating);
        }
        std::cout << "Total Reviews Loaded: " << reviews.getSize() << std::endl;

        inFile.close();
}



#endif // REVIEW_CONTAINER_H