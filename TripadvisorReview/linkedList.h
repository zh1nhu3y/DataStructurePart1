/**
 * linkedList.h
 */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Node
{
public:
    T data;
    int frequency;
    Node *next;

    Node(T value) : data(value), frequency(1), next(nullptr) {}
};

template <typename T>
class LinkedList
{
private:
    Node<T> *head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList()
    {
        clear();
    }

    void insert(const T &value)
    {
        Node<T> *existingNode = find(value);
        if (existingNode)
        {
            existingNode->frequency++;
        }
        else
        {
            Node<T> *newNode = new Node<T>(value);
            newNode->next = head;
            head = newNode;
            size++;
        }
    }

    Node<T> *find(const T &value) const
    {
        Node<T> *current = head;
        while (current != nullptr)
        {
            if (current->data == value)
                return current;
            current = current->next;
        }
        return nullptr;
    }

    bool contains(const T &value) const
    {
        return find(value) != nullptr;
    }

    int getWordFrequency(const T &value) const
    {
        Node<T> *node = find(value);
        return node ? node->frequency : 0;
    }

    void clear()
    {
        while (head != nullptr)
        {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    Node<T> *getHead() const
    {
        return head;
    }

    int getSize() const
    {
        return size;
    }

    void bubbleSort()
    {
        if (!head || !head->next)
            return;

        bool swapped;
        Node<T> *current;
        Node<T> *last = nullptr;

        do
        {
            swapped = false;
            current = head;

            while (current->next != last)
            {
                if (current->data.frequency < current->next->data.frequency)
                {
                    // Swap the nodes' data
                    T temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next;
            }
            last = current;
        } while (swapped);
    }

    void insertionSort()
    {
        if (!head || !head->next)
            return;

        Node<T> *sorted = nullptr;
        Node<T> *current = head;

        while (current != nullptr)
        {
            Node<T> *next = current->next;

            if (sorted == nullptr || sorted->data.frequency <= current->data.frequency)
            {
                current->next = sorted;
                sorted = current;
            }
            else
            {
                Node<T> *search = sorted;
                while (search->next != nullptr &&
                       search->next->data.frequency > current->data.frequency)
                {
                    search = search->next;
                }
                current->next = search->next;
                search->next = current;
            }

            current = next;
        }

        head = sorted;
    }

    // Searching algorithm

    // Linear Search
    int linearSearch(const string &word)
    {
        using Clock = std::chrono::high_resolution_clock;
        auto start = Clock::now(); // Start timing

        Node<T> *current = head;
        int frequency = 0;

        while (current != nullptr)
        {
            if (current->data == word)
            {
                frequency = current->frequency;
                break;
            }
            current = current->next;
        }

        auto end = Clock::now(); // End timing
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "Linear Search took " << duration.count() << " ns\n";

        return frequency;
    }

    // Two-Pointer Search
    int twoPointerSearch(const string &word)
    {
        using Clock = std::chrono::high_resolution_clock;
        auto start = Clock::now(); // Start timing

        if (head == nullptr)
        {
            auto end = Clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            std::cout << "Two-Pointer Search took " << duration.count() << " ns\n";
            return 0;
        }

        Node<T> *slow = head;
        Node<T> *fast = head;
        int frequency = 0;

        // Perform search with two-pointer technique
        while (fast != nullptr && fast->next != nullptr)
        {
            // Check slow pointer
            if (slow->data == word)
            {
                frequency = slow->frequency;
                break;
            }

            // Check fast pointer
            if (fast->data == word)
            {
                frequency = fast->frequency;
                break;
            }
            if (fast->next->data == word)
            {
                frequency = fast->next->frequency;
                break;
            }

            // Move pointers
            slow = slow->next;
            fast = fast->next->next;
        }

        // Edge case: Check if the list is of odd length
        if (fast != nullptr && slow != fast && fast->data == word)
        {
            frequency = fast->frequency;
        }

        // Edge case: slow and fast are still the same, check if slow has the word
        if (frequency == 0 && slow != nullptr && slow->data == word)
        {
            frequency = slow->frequency;
        }

        auto end = Clock::now(); // End timing
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "Two-Pointer Search took " << duration.count() << " nanoseconds\n";

        return frequency;
    }
};

#endif
