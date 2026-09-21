#ifndef RESERVATION_H
#define RESERVATION_H

#include "Resource.h"
#include <iostream>
#include <string>

struct ReservationRecord {
    std::string reservationId;
    std::string studentId;
    std::string studentName;
    std::string resourceId;
    std::string reservationDate;
};

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
    bool remove(const std::string& reservationId, ReservationRecord& removedRecord);
    Node* search(const std::string& reservationId) const;
    void display() const;
    bool isEmpty() const;
};

#endif
