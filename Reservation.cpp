#include "Reservation.h"

// Prints one reservation on a single line
void displayReservationRecord(const ReservationRecord& record) {
    std::cout << "Reservation ID: " << record.reservationId
        << " | Student: " << record.studentName
        << " (ID: " << record.studentId << ")"
        << " | Resource ID: " << record.resourceId
        << " | Date: " << record.reservationDate << "\n";
}

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

//allocates new node with items as the data for the node and adds to the end of the list
void DoublyLinkedList::insert(const ReservationRecord& record)
{
    Node* newNode = new Node;
    newNode->data = record;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

//finds the reservation by ID, copies it into removedRecord, then unlinks and deletes the node
bool DoublyLinkedList::remove(const std::string& reservationId, ReservationRecord& removedRecord)
{
    Node* current = search(reservationId);
    if (current == nullptr) {
        return false; // reservation not found
    }

    removedRecord = current->data;

    if (current == head && current == tail) {
        head = tail = nullptr;
    }
    else if (current == head) {
        head = head->next;
        head->prev = nullptr;
    }
    else if (current == tail) {
        tail = tail->prev;
        tail->next = nullptr;
    }
    else {
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

bool DoublyLinkedList::isEmpty() const {
    return head == nullptr;
}

// Counts every node in the list
int DoublyLinkedList::size() const {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// Linear search through the whole list, counts reservations that use this resource
int DoublyLinkedList::countByResource(const std::string& resourceId) const {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        if (current->data.resourceId == resourceId) {
            count++;
        }
        current = current->next;
    }
    return count;
}

// Linear search through the whole list, prints every reservation made by this student
int DoublyLinkedList::displayByStudent(const std::string& studentId) const {
    int found = 0;
    Node* current = head;
    while (current != nullptr) {
        if (current->data.studentId == studentId) {
            displayReservationRecord(current->data);
            found++;
        }
        current = current->next;
    }
    return found;
}



// Cancelation cpp Code
void CancelationHistoryClass::DisplayCancelationHistory() {
    // Handles empty stack
    if (CancelationHistory.empty() == 1) {
        cout << "No cancellations to show." << endl;
        return;
    }

    int const arrSize = static_cast<int>(CancelationHistory.size());
    vector<CancelationNode> data;

    // Ittrates throughout entire stack and displays information
    while (CancelationHistory.empty() == 0) {

        // Display information here
        cout << "Reservation ID: " << CancelationHistory.top().data.reservationId
            << " | Student: " << CancelationHistory.top().data.studentName
            << " | Resource ID: " << CancelationHistory.top().data.resourceId
            << " | Date: " << CancelationHistory.top().data.reservationDate << endl;


        // Add item to vector then delete top
        data.push_back(CancelationHistory.top());
        CancelationHistory.pop();
    }



    // Add items back to stack
    // Starts from the end of the vector so the stack keeps its original order
    for (int i = arrSize - 1; i >= 0; i--) {
        CancelationHistory.push(data.at(i));
    }
}

// Adds a cancelled reservation to the top of the stack
void CancelationHistoryClass::AddCancelation(const ReservationRecord& record) {
    CancelationNode node;
    node.data = record;
    CancelationHistory.push(node);
}

// Takes the most recent cancellation off the stack and returns it
ReservationRecord CancelationHistoryClass::RemoveLastCancelation() {
    ReservationRecord record = CancelationHistory.top().data;
    CancelationHistory.pop();
    return record;
}

bool CancelationHistoryClass::IsEmpty() const {
    return CancelationHistory.empty();
}
