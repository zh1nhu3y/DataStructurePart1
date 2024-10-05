#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>

// Constants for initial capacity and file paths
static const int INITIAL_CAPACITY_REVIEWS = 10;
const std::string CLEANED_FILE = "C:\\Users\\lawme\\OneDrive - Asia Pacific University\\Degree\\Sem 2\\Data Structure\\Assignment\\DSTR_P1_Data\\Organized_hotel_reviews.csv"; // Output file

// Define structure to hold hotel reviews and ratings
struct Review
{
    std::string text;
    int rating;
};

// Custom container to store reviews and ratings using a dynamic array
class ReviewContainer
{
private:
    Review *reviews;
    int size;
    int capacity;

    // Function to resize the dynamic array when needed
    void resize()
    {
        capacity *= 2;
        Review *newReviews = new Review[capacity];
        for (int i = 0; i < size; i++)
        {
            newReviews[i] = reviews[i];
        }
        delete[] reviews;
        reviews = newReviews;
    }

    // Helper function to clean a review text by removing unwanted characters
    std::string cleanReviewText(const std::string &text)
    {
        std::string cleaned = text;
        // Remove unwanted characters like punctuation
        cleaned.erase(std::remove_if(cleaned.begin(), cleaned.end(), [](unsigned char c)
                                     {
                                         return std::ispunct(c); // Removes punctuation
                                     }),
                      cleaned.end());
        // Convert to lowercase
        std::transform(cleaned.begin(), cleaned.end(), cleaned.begin(), ::tolower);
        return cleaned;
    }

public:
    ReviewContainer() : size(0), capacity(INITIAL_CAPACITY_REVIEWS)
    {
        reviews = new Review[capacity];
    }

    ~ReviewContainer()
    {
        delete[] reviews;
    }

    // Function to add a review to the container
    void addReview(const std::string &reviewText, int rating)
    {
        if (size >= capacity)
        {
            resize();
        }
        reviews[size].text = cleanReviewText(reviewText);
        reviews[size].rating = rating;
        size++;
    }

    int getReviewCount() const
    {
        return size;
    }

    Review getReview(int index) const
    {
        if (index < size)
        {
            return reviews[index];
        }
        return {};
    }

    // Load and clean reviews from a CSV file
    void loadFromFile(const std::string &filename)
    {
        std::ifstream file(filename);
        std::string line;
        bool skipHeader = true;

        if (!file.is_open())
        {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }

        while (getline(file, line))
        {
            if (skipHeader)
            {
                skipHeader = false;
                continue; // Skip the first line (header)
            }

            std::stringstream ss(line);
            std::string review, ratingStr;
            int rating;

            // Handle reviews with quotes
            if (line.find('"') != std::string::npos)
            {
                size_t firstQuote = line.find('"');
                size_t lastQuote = line.rfind('"');
                review = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);
                ratingStr = line.substr(lastQuote + 2);
            }
            else
            {
                getline(ss, review, ',');
                getline(ss, ratingStr, ',');
            }

            try
            {
                if (!ratingStr.empty())
                {
                    rating = std::stoi(ratingStr);
                    if (rating >= 1 && rating <= 5)
                    {
                        addReview(review, rating);
                    }
                    else
                    {
                        std::cerr << "Skipped Review: Invalid rating: " << rating << std::endl;
                    }
                }
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Error: Invalid rating value for review. Skipping review." << std::endl;
            }
        }
        file.close();
    }

    // Save cleaned reviews to a new CSV file
    void saveToFile(const std::string &filename)
    {
        std::ofstream outFile(filename);
        if (!outFile.is_open())
        {
            std::cerr << "Error opening file for saving cleaned data!" << std::endl;
            return;
        }

        outFile << "Review,Rating" << std::endl; // Write the header

        for (int i = 0; i < size; i++)
        {
            outFile << "\"" << reviews[i].text << "\"," << reviews[i].rating << std::endl;
        }

        outFile.close();
        std::cout << "Cleaned data saved to: " << filename << std::endl;
    }
};

int main()
{
    // Initialize the review container
    ReviewContainer reviews;

    // Load reviews from the raw CSV file
    reviews.loadFromFile("C:\\Users\\lawme\\OneDrive - Asia Pacific University\\Degree\\Sem 2\\Data Structure\\Assignment\\DSTR_P1_Data\\tripadvisor_hotel_reviews.csv");

    // Save the cleaned reviews to a new CSV file
    reviews.saveToFile("C:\\Users\\lawme\\OneDrive - Asia Pacific University\\Degree\\Sem 2\\Data Structure\\Assignment\\DSTR_P1_Data\\organized_hotel_reviews.csv");

    std::cout << "Data cleaning complete. Cleaned data saved to " << CLEANED_FILE << std::endl;

    return 0;
}
