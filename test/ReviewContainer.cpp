#include "ReviewContainer.h"

// Constructor
ReviewContainer::ReviewContainer() : size(0), capacity(INITIAL_CAPACITY_REVIEWS)
{
    reviews = new Review[capacity];
}

// Destructor
ReviewContainer::~ReviewContainer()
{
    delete[] reviews;
}

// Resize the dynamic array
void ReviewContainer::resize()
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

// Clean review text
std::string ReviewContainer::cleanReviewText(const std::string &text)
{
    std::string cleaned = text;
    cleaned.erase(std::remove_if(cleaned.begin(), cleaned.end(), [](unsigned char c)
                                 {
                                     return std::ispunct(c); // Removes punctuation
                                 }),
                  cleaned.end());
    std::transform(cleaned.begin(), cleaned.end(), cleaned.begin(), ::tolower);
    return cleaned;
}

// Add a review
void ReviewContainer::addReview(const std::string &reviewText, int rating)
{
    if (size >= capacity)
    {
        resize();
    }
    reviews[size].text = cleanReviewText(reviewText);
    reviews[size].rating = rating;
    size++;
}

// Get the number of reviews
int ReviewContainer::getReviewCount() const
{
    return size;
}

// Get a review by index
Review ReviewContainer::getReview(int index) const
{
    if (index < size)
    {
        return reviews[index];
    }
    return {};
}

// Load reviews from a file
void ReviewContainer::loadFromFile(const std::string &filename)
{
    std::cout << "Loading file from: " << filename << std::endl;

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
    std::cout << "File loaded" << std::endl;
    file.close();
}

// Save cleaned reviews to a file
void ReviewContainer::saveToFile(const std::string &filename)
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
