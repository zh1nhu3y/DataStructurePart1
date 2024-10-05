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
};

#endif
