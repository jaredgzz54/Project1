#include "ReservationManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>


// ===================== Lambda Functions =====================
Resource* findResource(vector<Resource>& resources, const string& resourceId) {
    for (int i = 0; i < static_cast<int>(resources.size()); i++) {
        if (resources[i].getResourceId() == resourceId) {
            return &resources[i];
        }
    }
    return nullptr;
}

string generateReservationId(const DoublyLinkedList& list, int& nextNumber) {
    string newId;
    do {
        newId = to_string(nextNumber);
        nextNumber++;
    } while (list.search(newId) != nullptr);
    return newId;
}

void mergeResources(vector<Resource>& list, int left, int mid, int right, int sortChoice) {
    vector<Resource> temp;
    int i = left;      // start of the left half
    int j = mid + 1;   // start of the right half

    while (i <= mid && j <= right) {
        bool takeLeft;
        if (sortChoice == 1) {
            takeLeft = list[i].getResourceName() <= list[j].getResourceName();   // A to Z
        }
        else if (sortChoice == 2) {
            takeLeft = list[i].getRequestCount() >= list[j].getRequestCount();   // most requested first
        }
        else {
            takeLeft = list[i].getResourceId() <= list[j].getResourceId();       // ID order
        }

        if (takeLeft) {
            temp.push_back(list[i]);
            i++;
        }
        else {
            temp.push_back(list[j]);
            j++;
        }
    }

    // Copy whatever is left over in either half
    while (i <= mid) {
        temp.push_back(list[i]);
        i++;
    }
    while (j <= right) {
        temp.push_back(list[j]);
        j++;
    }

    // Put the merged items back into the original list
    for (int k = 0; k < static_cast<int>(temp.size()); k++) {
        list[left + k] = temp[k];
    }
}

void mergeSortResources(vector<Resource>& list, int left, int right, int sortChoice) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSortResources(list, left, mid, sortChoice);
        mergeSortResources(list, mid + 1, right, sortChoice);
        mergeResources(list, left, mid, right, sortChoice);
    }
}

// ===================== ReservationManager =====================
ReservationManager::ReservationManager() : nextReservationNumber(301) {}

void ReservationManager::loadResources(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening resource file. Using default mock resources.\n";
        resources.push_back(Resource("R205", "Study Room A", "Study Room", true));
        resources.push_back(Resource("L101", "Dell Latitude Laptop", "Laptop", true));
        resources.push_back(Resource("C01", "TI-84 Calculator", "Calculator", true));
        return;
    }

    string id, name, type, status;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');

        // Only add the resource if the whole line was read correctly
        if (ss >> status) {
            resources.push_back(Resource(id, name, type, status == "Available"));
        }

    }
    file.close();
    cout << "Loaded " << resources.size() << " resources from " << filename << ".\n";
}

void ReservationManager::loadReservations(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening reservation file. Starting with no active reservations.\n";
        return;
    }

    string line;
    int loaded = 0;
    int skipped = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        ReservationRecord record;
        getline(ss, record.reservationId, '|');
        getline(ss, record.studentId, '|');
        getline(ss, record.studentName, '|');
        getline(ss, record.resourceId, '|');

        // Skip blank or broken lines
        if (!(ss >> record.reservationDate)) {
            continue;
        }

        // Skip reservations for resources that do not exist or IDs that are already used
        Resource* res = findResource(resources, record.resourceId);
        if (res == nullptr || activeReservations.search(record.reservationId) != nullptr) {
            skipped++;
            continue;
        }

        // Availability stays the way resources.txt has it
        activeReservations.insert(record);
        res->addRequest();
        loaded++;

        // New reservation IDs start after the highest ID in the file
        int idNumber = atoi(record.reservationId.c_str());
        if (idNumber >= nextReservationNumber) {
            nextReservationNumber = idNumber + 1;
        }
    }
    file.close();

    cout << "Loaded " << loaded << " reservations from " << filename << ".\n";
    if (skipped > 0) {
        cout << "Skipped " << skipped << " reservations (unknown resource ID or duplicate reservation ID).\n";
    }
}


void ReservationManager::displayAllResources() const {
    cout << "\n===== Campus Resources =====\n";
    for (const auto& res : resources) {
        res.display();
    }
}

void ReservationManager::displayResourceAvailability() const {
    cout << "\n===== Resource Availability =====\n";
    for (const auto& res : resources) {
        cout << res.getResourceId() << " (" << res.getResourceName()
            << ") - " << (res.getAvailability() ? "Available" : "Unavailable") << "\n";
    }
}

void ReservationManager::createReservation() {
    string resId, studentId, studentName, date;
    displayResourceAvailability();
    cout << "Enter Resource ID: ";
    cin >> resId;

    Resource* targetResource = findResource(resources, resId);

    if (!targetResource) {
        cout << "Invalid Resource ID.\n";
        return;
    }

    cout << "Enter Student ID: ";
    cin >> studentId;
    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, studentName);
    cout << "Enter Date (YYYY-MM-DD): ";
    cin >> date;

    // Error Checking
    if (studentName.empty()) {
        cout << "Invalid student name.\n";
        return;
    }
    if (date.length() != 10 || date[2] != '/' || date[5] != '/') {
        cout << "Invalid date. Please use the format MM/DD/YYYY.\n";
        return;
    }

    if (targetResource->getAvailability()) {
        string reservationId = generateReservationId(activeReservations, nextReservationNumber);
        targetResource->setAvailability(false);
        targetResource->addRequest();
        ReservationRecord record{ reservationId, studentId, studentName, resId, date };
        activeReservations.insert(record);
        cout << "Reservation Created Successfully. ID: " << reservationId << "\n";

    }
    else {
        WaitingRequest req{ studentId, studentName, resId };
        if (targetResource->getWaitingList().enqueue(req)) {
            targetResource->addRequest();
            cout << "Resource currently unavailable. Added to waiting list.\n";
        }
    }
}

void ReservationManager::cancelReservation() {
    string resId;
    cout << "Enter Reservation ID to cancel: ";
    cin >> resId;

    ReservationRecord record;
    if (activeReservations.remove(resId, record)) {
        cancellationHistory.push(record);

        // Free up the resource
        for (auto& res : resources) {
            if (res.getResourceId() == record.resourceId) {
                WaitingRequest nextReq;
                if (activeReservations.countByResource(res.getResourceId()) > 0) {
                    cout << "Reservation Cancelled. Resource is still reserved by another student.\n";
                }
                
                else if (!res.getWaitingList().isEmpty()) {
                    res.getWaitingList().dequeue(nextReq);
                    ReservationRecord newRecord{ generateReservationId(activeReservations, nextReservationNumber),
                    nextReq.studentID, nextReq.studentName,
                    res.getResourceId(), record.reservationDate };
                    activeReservations.insert(newRecord);
                    cout << "Reservation Cancelled. Resource automatically assigned to waiting student: "
                         << nextReq.studentName << " (New Reservation ID: " << newRecord.reservationId << ")\n";
                }

                else {
                    res.setAvailability(true);
                    cout << "Reservation Cancelled. Resource is now available.\n";
                }
                break;
            }
        }
        cout << "Added to cancellation history.\n";
    }
    else {
        cout << "Reservation ID not found.\n";
    }
}

void ReservationManager::displayActiveReservations() const {
    cout << "\n===== Active Reservations =====\n";
    activeReservations.display();
}

void ReservationManager::undoCancellation() {
    if (cancellationHistory.empty()) {
        cout << "No cancellation history to undo.\n";
        return;
    }

    ReservationRecord record = cancellationHistory.top();
    cancellationHistory.pop();

    for (auto& res : resources) {
        if (res.getResourceId() == record.resourceId && res.getAvailability()) {
            res.setAvailability(false);
            activeReservations.insert(record);
            cout << "Reservation Restored Successfully for " << record.studentName << "!\n";
            return;
        }
    }
    cout << "Cannot restore reservation; resource is currently occupied.\n";
    cancellationHistory.push(record); // Push back if unable to restore
}

void ReservationManager::displayWaitingList() const {
    cout << "\n===== Waiting List =====\n";
    bool anyoneWaiting = false;
    for (const auto& res : resources) {
        if (!res.getWaitingList().isEmpty()) {
            res.getWaitingList().display();
            anyoneWaiting = true;
        }
    }
    if (!anyoneWaiting) {
        cout << "No students are currently waiting for any resource.\n";
    }

}

void ReservationManager::displayCancellationHistory() const {
    cout << "\n===== Cancellation History (Stack Top) =====\n";
    if (cancellationHistory.empty()) {
        cout << "Stack is empty.\n";
        return;
    }

    
    stack<ReservationRecord> copy = cancellationHistory;
    while (!copy.empty()) {
        ReservationRecord topRec = copy.top();
        cout << "Reservation ID: " << topRec.reservationId
            << " | Student: " << topRec.studentName
            << " | Resource ID: " << topRec.resourceId
            << " | Date: " << topRec.reservationDate << "\n";
        copy.pop();
    }

}

// ===================== Searching =====================
void ReservationManager::searchMenu() {
    int choice;
    cout << "\n===== Search =====\n";
    cout << "1. Search Resource by ID\n";
    cout << "2. Search Reservation by ID\n";
    cout << "3. Search Reservations by Student ID\n";
    cout << "Enter Choice: ";

    if (!(cin >> choice)) {
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    string searchId;
    if (choice == 1) {
        cout << "Enter Resource ID: ";
        cin >> searchId;
        Resource* found = findResource(resources, searchId);
        if (found != nullptr) {
            found->display();
        }
        else {
            cout << "Resource ID not found.\n";
        }
    }
    else if (choice == 2) {
        cout << "Enter Reservation ID: ";
        cin >> searchId;
        Node* found = activeReservations.search(searchId);
        if (found != nullptr) {
            cout << "Reservation ID: " << found->data.reservationId
                << " | Student: " << found->data.studentName
                << " (ID: " << found->data.studentId << ")"
                << " | Resource ID: " << found->data.resourceId
                << " | Date: " << found->data.reservationDate << "\n";
        }
        else {
            cout << "Reservation ID not found.\n";
        }
    }
    else if (choice == 3) {
        cout << "Enter Student ID: ";
        cin >> searchId;
        if (activeReservations.displayByStudent(searchId) == 0) {
            cout << "No active reservations found for student " << searchId << ".\n";
        }
    }
    else {
        cout << "Invalid choice. Please select between 1 and 3.\n";
    }
}

// ===================== Sorting =====================

void ReservationManager::sortResources() {
    int choice;
    cout << "\n===== Sort Resources =====\n";
    cout << "1. Sort by Name\n";
    cout << "2. Sort by Popularity (Most Requested)\n";
    cout << "3. Sort by Resource ID\n";
    cout << "Enter Choice: ";

    if (!(cin >> choice)) {
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    if (choice < 1 || choice > 3) {
        cout << "Invalid choice. Please select between 1 and 3.\n";
        return;
    }

    mergeSortResources(resources, 0, static_cast<int>(resources.size()) - 1, choice);
    cout << "Resources sorted.\n";
    displayAllResources();
}

// ===================== Reporting =====================

void ReservationManager::generateReport() {
    cout << "\n========== System Report ==========\n";

    
    cout << "\n--- Active Reservations ---\n";
    activeReservations.display();

    
    cout << "\n--- Resource Utilization ---\n";
    int totalReservations = 0;
    for (const auto& res : resources) {
        int count = activeReservations.countByResource(res.getResourceId());
        cout << res.getResourceId() << " (" << res.getResourceName() << ") - Reservations: "
            << count << " | " << (res.getAvailability() ? "Available" : "Unavailable") << "\n";
        totalReservations += count;
    }
    cout << "Total Active Reservations: " << totalReservations << "\n";

    
    cout << "\n--- Most Requested Resources (Top 5) ---\n";
    vector<Resource> sortedList = resources;
    mergeSortResources(sortedList, 0, static_cast<int>(sortedList.size()) - 1, 2);
    int rank = 0;
    while (rank < static_cast<int>(sortedList.size()) && rank < 5 && sortedList[rank].getRequestCount() > 0) {
        cout << rank + 1 << ". " << sortedList[rank].getResourceId()
            << " (" << sortedList[rank].getResourceName() << ") - Requests: "
            << sortedList[rank].getRequestCount() << "\n";
        rank++;
    }
    if (rank == 0) {
        cout << "No resources have been requested yet.\n";
    }

    
    cout << "\n--- Waiting-List Statistics ---\n";
    int totalWaiting = 0;
    for (const auto& res : resources) {
        cout << res.getResourceId() << " (" << res.getResourceName() << ") - Students Waiting: "
            << res.getWaitingList().size() << "\n";
        totalWaiting += res.getWaitingList().size();
    }
    cout << "Total Students Waiting: " << totalWaiting << "\n";
}
