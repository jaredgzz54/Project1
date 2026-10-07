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

void DoublyLinkedList::DLLPreppend(Resource item) {
    Node* newNode = new Node{item, nullptr, nullptr};
    DLLPreppendNode(newNode);
}

void DoublyLinkedList::DLLPreppendNode(Node* newNode) {
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// Custom Linear Search Implementation (No library search functions used)
Resource* DoublyLinkedList::DLLLinearSearch(int resourceId) {
    Node* currentNode = head;
    while (currentNode != nullptr) {
        if (currentNode->data.getResourceId() == resourceId) {
            return &(currentNode->data);
        }
        currentNode = currentNode->next;
    }
    return nullptr;
}

// Custom Merge Sort Implementation for Linked List (No std::sort used)
void DoublyLinkedList::mergeSort(Node** headRef) {
    Node* headNode = *headRef;
    if ((headNode == nullptr) || (headNode->next == nullptr)) {
        return;
    }

    Node* a;
    Node* b;
    frontBackSplit(headNode, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *headRef = sortedMerge(a, b);
}

Node* DoublyLinkedList::sortedMerge(Node* a, Node* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    Node* result = nullptr;
    if (a->data.getResourceId() <= b->data.getResourceId()) {
        result = a;
        result->next = sortedMerge(a->next, b);
        if (result->next) result->next->prev = result;
        result->prev = nullptr;
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
        if (result->next) result->next->prev = result;
        result->prev = nullptr;
    }
    return result;
}

void DoublyLinkedList::frontBackSplit(Node* source, Node* frontRef, Node* backRef) {
    Node* fast;
    Node* slow;
    if (source == nullptr || source->next == nullptr) {
        *(Node**)frontRef = source;
        *(Node**)backRef = nullptr;
    } else {
        slow = source;
        fast = source->next;

        while (fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *(Node**)frontRef = source;
        *(Node**)backRef = slow->next;
        slow->next->prev = nullptr;
        slow->next = nullptr;
    }
}

void DoublyLinkedList::sortReservations() {
    mergeSort(&head);
    // Re-establish tail pointer after sort
    Node* curr = head;
    if (!curr) {
        tail = nullptr;
        return;
    }
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    tail = curr;
    cout << "Active reservations successfully sorted by Resource ID using custom Merge Sort.\n";
}

void DoublyLinkedList::DLLRemove(Node* itemToRemove) {
    if (itemToRemove == nullptr) {
        cout << "Item not found in active reservations.\n";
        return;
    }
    
    Node* successor = itemToRemove->next;
    Node* predecessor = itemToRemove->prev;

    if (successor != nullptr) successor->prev = predecessor;
    if (predecessor != nullptr) predecessor->next = successor;
    if (itemToRemove == head) head = successor;
    if (itemToRemove == tail) tail = predecessor;

    delete itemToRemove;
}

Node* DoublyLinkedList::getHead() const { return head; }

void DoublyLinkedList::display() const {
    Node* current = head;
    if (!current) {
        cout << "No active reservations found.\n";
        return;
    }
    cout << "--- Active Reservations List ---\n";
    while (current != nullptr) {
        current->data.display();
        current = current->next;
    }
}
