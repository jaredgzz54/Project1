#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <vector>

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


// Cancelation code \\
/* 
    Structure for a cancelation node
*/
struct CancelationNode {
	string studentName;

};

/*
	Stack Functions (Context is CancelationHistory)
		CancelationHistory.top();	// Access first element (Can be used as a read or write)
		CancelationHistory.push();	// Add element to top of stack (Requires data)
		CancelationHistory.pop();	// Removes top element of stack
		CancelationHistory.empty(); // Checks if stack is empty (If empty will output 0
*/
class CancelationHistoryClass {
	private:
		stack<CancelationNode> CancelationHistory;

	public:
		void DisplayCancelationHistory(); // Cannot be declared as const because what we plan to do with stack
};
#endif
