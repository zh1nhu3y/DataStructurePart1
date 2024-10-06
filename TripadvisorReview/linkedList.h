/**
 * linkedList.h
 * 
 * A template-based linked list implementation designed to manage nodes containing words and their
 * frequencies. Includes basic operations like sorting and searching, along with
 * word frequency analysis functionalities
 */

#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;


// Node class represents an element in the linked list, containing data, frequency, and a pointer to the next node
template <typename T>
class Node
{
public:
    T data;
    int frequency;
    Node *next;

    Node(T value) : data(value), frequency(1), next(nullptr) {}
};

// LinkedList class manages a list of nodes, providing operations such as insertion, searching, sorting, and clearing
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

    // Inserts a new value or increments the frequency if it already exists
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

    // Finds and returns a node with the specified value, or nullptr if not found
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

    // Checks if a value exists in the list
    bool contains(const T &value)
    {
        return find(value) != nullptr;
    }

    // Returns the frequency of the specified word, or 0 if not found
    int getWordFrequency(const T &value) const
    {
        Node<T> *node = find(value);
        return node ? node->frequency : 0;
    }

    // Clears the linked list
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

    // Returns the head node
    Node<T> *getHead() const
    {
        return head;
    }

    // Returns the size of the list
    int getSize() const
    {
        return size;
    }

    // Sorts the linked list by frequency using Bubble Sort
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

    // Sorts the linked list by frequency using Insertion Sort
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

    // Performs linear search and calculates the frequency of a word
    int linearSearch(const string &word)
    {
        const int iterations = 1000; // For more accurate timing
        int frequency = 0;
        
        auto start = high_resolution_clock::now();
        
        // Run the search multiple times to measure performance
        for (int i = 0; i < iterations; i++) {
            frequency = 0;  // Reset frequency for each iteration
            Node<T> *current = head;
            
            // Traverse the linked list
            while (current != nullptr)
            {
                if (current->data == word)
                {
                    frequency += current->frequency;  // Count frequency of the word
                }
                current = current->next;
            }
        }
        
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        double avgTime = static_cast<double>(duration.count()) / iterations;
        
        // Display timing results
        cout << "Linear Search took an average of " << avgTime << " microseconds (" 
            << duration.count() << " microseconds total for " << iterations << " iterations)\n";
        
        return frequency;  // Return the frequency of the word found
    }

    // Performs two-pointer search to find the frequency of a word
    int twoPointerSearch(const string &word)
    {
        const int iterations = 1000; // For more accurate timing
        int frequency = 0;
        
        auto start = high_resolution_clock::now();
        
        // Run the search multiple times to measure performance
        for (int i = 0; i < iterations; i++) {
            frequency = 0;  // Reset frequency for each iteration

            if (head == nullptr) continue;  // Edge case: Empty list

            Node<T> *slow = head;
            Node<T> *fast = head;
            
            // Traverse the linked list using two pointers
            while (fast != nullptr && fast->next != nullptr)
            {
                if (slow->data == word)
                {
                    frequency += slow->frequency;  // Count frequency for slow pointer
                }
                if (fast->data == word)
                {
                    frequency += fast->frequency;  // Count frequency for fast pointer
                }
                if (fast->next->data == word)
                {
                    frequency += fast->next->frequency;  // Count frequency for fast->next
                }

                slow = slow->next;
                fast = fast->next->next;
            }
            
            // Edge case: Handle remaining nodes
            if (fast != nullptr && slow != fast && fast->data == word)
            {
                frequency += fast->frequency;
            }
            if (slow != nullptr && slow->data == word)
            {
                frequency += slow->frequency;
            }
        }
        
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        double avgTime = static_cast<double>(duration.count()) / iterations;
        
        // Display timing results
        cout << "Two-Pointer Search took an average of " << avgTime << " microseconds (" 
            << duration.count() << " microseconds total for " << iterations << " iterations)\n";
        
        return frequency;  // Return the frequency of the word found
    }

    // Binary search to check if a word exists in a sorted word array
    bool binarySearch(const string& word, const WordArray& wordArray) const {
        int left = 0;
        int right = wordArray.getWordCount() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            string midWord = wordArray.getWordAt(mid);
            
            if (midWord == word)
                return true;
            
            if (midWord < word)
                left = mid + 1;
            else
                right = mid - 1;
        }
        
        return false;
    }
};