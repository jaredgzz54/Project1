#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include "Resource.h"

using namespace std;

enum Options { 
    ViewR = 1, CreateR = 2, CancelR = 3, ViewW = 4, 
    UndoC = 5, SearchR = 6, SortR = 7, GenerateRepo = 8, Exit = 9 
};

struct Node {
    Resource data;
    Node* next;
    Node* prev;
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

    // Helper for custom Merge Sort on Linked List
    Node* sortedMerge(Node* a, Node* b);
    void frontBackSplit(Node* source, Node* frontRef, Node* backRef);
    void mergeSort(Node** headRef);

public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    
    void DLLPreppend(Resource item);
    void DLLPreppendNode(Node* newNode);
    Resource* DLLLinearSearch(int resourceId); // Custom Linear Search
    int DLLBinarySearchByName(const string& targetName); // Custom Search framework
    void DLLRemove(Node* itemToRemove);
    void sortReservations(); // Triggers custom Merge Sort
    
    Node* getHead() const;
    void display() const;
};

#endif
