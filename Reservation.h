#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <string>

using namespace std;

struct ReservationRecord {
    string reservationId;
    string studentId;
    string studentName;
    string resourceId;
    string reservationDate;
};

// Prints one reservation on a single line
void displayReservationRecord(const ReservationRecord& record);

struct Node {
    ReservationRecord data;
    Node* next;
    Node* prev;
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insert(const ReservationRecord& record);
    bool remove(const string& reservationId, ReservationRecord& removedRecord);
    Node* search(const string& reservationId) const;
    void display() const;
    bool isEmpty() const;
    int size() const;                                             
    int countByResource(const std::string& resourceId) const;   
    int displayByStudent(const std::string& studentId) const;    
};

// Cancelation code \\
// Structure for a cancelation node
struct CancelationNode {
    ReservationRecord data; // Holds the full reservation that was cancelled

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
    void AddCancelation(const ReservationRecord& record); // Pushes a cancelled reservation on top
    ReservationRecord RemoveLastCancelation();             // Pops the most recent one (check IsEmpty first)
    bool IsEmpty() const;
};
#endif
