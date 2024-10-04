// LinkedListSortingAlgorithms.hpp - Reusable sorting algorithms for linked lists
class LinkedListSortingAlgorithms {
public:
    // Bubble Sort
    static void bubbleSort(WordNode*& head) {
        if (!head || !head->next) return;

        bool swapped;
        WordNode* ptr1;
        WordNode* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr) {
                if (ptr1->frequency < ptr1->next->frequency) {
                    std::swap(ptr1->word, ptr1->next->word);
                    std::swap(ptr1->frequency, ptr1->next->frequency);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }

    // Insertion Sort
    static void insertionSort(WordNode*& head) {
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
};
