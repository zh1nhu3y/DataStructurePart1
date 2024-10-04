#include <iostream>
#include <string>

using namespace std;

class WordNode {
public:
    string word;
    int frequency;
    WordNode* next;

    WordNode(const string& word, int frequency) 
        : word(word), frequency(frequency), next(nullptr) {}
};

class SkipSearch {
public:
    static WordNode* skipSearch(WordNode* head, const std::string& target, int k) {
        if (!head) return nullptr;

        WordNode* current = head;
        WordNode* lastSkipped = nullptr;

        // Skip nodes in increments of k
        while (current != nullptr && current->word < target) {
            lastSkipped = current; // Keep track of the last valid node
            for (int i = 0; i < k && current != nullptr; ++i) {
                current = current->next; // Skip k nodes
            }
        }

        // Perform linear search from the last valid node
        WordNode* searchNode = lastSkipped;
        while (searchNode != nullptr) {
            if (searchNode->word == target) {
                return searchNode; // Found the target
            }
            searchNode = searchNode->next;
        }

        return nullptr; // Target not found
    }
};
