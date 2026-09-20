#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

using namespace std;

//Global Variables
const int SIZE = 8;
enum options { ViewR = 1, CreateR = 2, CancelR = 3, ViewW = 4, UndoC = 5, SearchR = 6, SortR = 7, GenerateRepo = 8, Exit = 9 };

struct Node
{
    int data;
    Node* next;
    Node* prev;
};

class DoublyLinkedList
{
private:

    Node* head;
    Node* tail;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void DLLPreppend(DoublyLinkedList* list, int item);
    void DLLPreppendNode(DoublyLinkedList* list, Node* newNode);
    void DLLRemove(DoublyLinkedList* list, Node* itemToRemove);
    Node* DLLSearch(DoublyLinkedList* list, int itemToSearch);
};

#endif