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

//allocates new node with items as the data for the node
void DoublyLinkedList::DLLPreppend(xx, item)
{
    Node newNode = item;
    DLLPreppendNode(xx, newNode)
}

void DoublyLinkedList::DLLPreppendNode(xx, newNode)
{
    if(xx->head == null)
    {
        xx->head = newNode;
        xx->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
}
//xy is the name of the class for resources and the data type of itemtosearch
Resource DoublyLinkedList::DLLSearch(xx, itemtosearch)
{
    currentNode = list->head;
    while(currentNode != null)
    {
        if(currentNode->head == itemtosearch)
        {
            return itemtosearch;
        }
        currentNode = currentNode->next
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
