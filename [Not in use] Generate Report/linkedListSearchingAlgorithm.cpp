// LinkedListSearchingAlgorithms.hpp - Reusable searching algorithms for linked lists
class LinkedListSearchingAlgorithms {
public:
    // Linear Search
    static WordNode* linearSearch(WordNode* head, const std::string& word) {
        WordNode* current = head;
        while (current != nullptr) {
            if (current->word == word) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};
