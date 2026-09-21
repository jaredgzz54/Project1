#include "Reservation.h"

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

bool DoublyLinkedList::isEmpty() const {
    return head == nullptr;
}

void DoublyLinkedList::insert(const ReservationRecord& record) {
    Node* newNode = new Node{record, nullptr, nullptr};
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

bool DoublyLinkedList::remove(const std::string& reservationId, ReservationRecord& removedRecord) {
    Node* current = search(reservationId);
    if (current == nullptr) {
        return false;
    }

    removedRecord = current->data;

    if (current == head && current == tail) {
        head = tail = nullptr;
    } else if (current == head) {
        head = head->next;
        head->prev = nullptr;
    } else if (current == tail) {
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    delete current;
    return true;
}

Node* DoublyLinkedList::search(const std::string& reservationId) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.reservationId == reservationId) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void DoublyLinkedList::display() const {
    if (isEmpty()) {
        std::cout << "No active reservations.\n";
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        std::cout << "Reservation ID: " << current->data.reservationId 
                  << " | Student: " << current->data.studentName 
                  << " (ID: " << current->data.studentId << ")"
                  << " | Resource ID: " << current->data.resourceId 
                  << " | Date: " << current->data.reservationDate << "\n";
        current = current->next;
    }
}
