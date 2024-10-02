#ifndef REVIEW_CONTAINER_H
#define REVIEW_CONTAINER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>

static const int INITIAL_CAPACITY_REVIEWS = 10;

struct Review
{
    std::string text;
    int rating;
};

class ReviewContainer
{
private:
    Review *reviews;
    int size;
    int capacity;

    void resize();
    std::string cleanReviewText(const std::string &text);

public:
    ReviewContainer();
    ~ReviewContainer();
    void addReview(const std::string &reviewText, int rating);
    int getReviewCount() const;
    Review getReview(int index) const;
    void loadFromFile(const std::string &filename);
    void saveToFile(const std::string &filename);
};

#endif // REVIEW_CONTAINER_H
