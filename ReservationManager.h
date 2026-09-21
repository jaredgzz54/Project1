#include "ReservationManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

ReservationManager::ReservationManager() {}

void ReservationManager::loadResources(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening resource file. Using default mock resources.\n";
        resources.push_back(Resource("R205", "Study Room A", "Study Room", true));
        resources.push_back(Resource("L101", "Dell Latitude Laptop", "Laptop", true));
        resources.push_back(Resource("C01", "TI-84 Calculator", "Calculator", true));
        return;
    }

    std::string id, name, type;
    int avail;
    while (file >> id >> name >> type >> avail) {
        resources.push_back(Resource(id, name, type, avail == 1));
    }
    file.close();
}

void ReservationManager::displayAllResources() const {
    std::cout << "\n===== Campus Resources =====\n";
    for (const auto& res : resources) {
        res.display();
    }
}

void ReservationManager::displayResourceAvailability() const {
    std::cout << "\n===== Resource Availability =====\n";
    for (const auto& res : resources) {
        std::cout << res.getResourceId() << " (" << res.getResourceName() 
                  << ") - " << (res.getAvailability() ? "Available" : "Unavailable") << "\n";
    }
}

void ReservationManager::createReservation() {
    std::string resId, studentId, studentName, date;
    std::cout << "Enter Resource ID: ";
    std::cin >> resId;

    Resource* targetResource = nullptr;
    for (auto& res : resources) {
        if (res.getResourceId() == resId) {
            targetResource = &res;
            break;
        }
    }

    if (!targetResource) {
        std::cout << "Invalid Resource ID.\n";
        return;
    }

    std::cout << "Enter Student ID: ";
    std::cin >> studentId;
    std::cout << "Enter Student Name: ";
    std::cin.ignore();
    std::getline(std::cin, studentName);
    std::cout << "Enter Date (YYYY-MM-DD): ";
    std::cin >> date;

    std::string reservationId = "RES" + std::to_string(rand() % 900 + 100);

    if (targetResource->getAvailability()) {
        targetResource->setAvailability(false);
        ReservationRecord record{reservationId, studentId, studentName, resId, date};
        activeReservations.insert(record);
        std::cout << "Reservation Created Successfully. ID: " << reservationId << "\n";
    } else {
        WaitingRequest req{studentId, studentName, resId};
        waitingList.enqueue(req);
        std::cout << "Resource currently unavailable. Added to waiting list.\n";
    }
}

void ReservationManager::cancelReservation() {
    std::string resId;
    std::cout << "Enter Reservation ID to cancel: ";
    std::cin >> resId;

    ReservationRecord record;
    if (activeReservations.remove(resId, record)) {
        cancellationHistory.push(record);
        
        // Free up the resource
        for (auto& res : resources) {
            if (res.getResourceId() == record.resourceId) {
                WaitingRequest nextReq;
                if (waitingList.dequeue(nextReq)) {
                    ReservationRecord newRecord{"RES" + std::to_string(rand() % 900 + 100), 
                                                nextReq.studentId, nextReq.studentName, 
                                                res.getResourceId(), record.reservationDate};
                    activeReservations.insert(newRecord);
                    std::cout << "Reservation Cancelled. Resource automatically assigned to waiting student: " 
                              << nextReq.studentName << "\n";
                } else {
                    res.setAvailability(true);
                    std::cout << "Reservation Cancelled. Resource is now available.\n";
                }
                break;
            }
        }
    } else {
        std::cout << "Reservation ID not found.\n";
    }
}

void ReservationManager::displayActiveReservations() const {
    std::cout << "\n===== Active Reservations =====\n";
    activeReservations.display();
}

void ReservationManager::undoCancellation() {
    if (cancellationHistory.empty()) {
        std::cout << "No cancellation history to undo.\n";
        return;
    }

    ReservationRecord record = cancellationHistory.top();
    cancellationHistory.pop();

    for (auto& res : resources) {
        if (res.getResourceId() == record.resourceId && res.getAvailability()) {
            res.setAvailability(false);
            activeReservations.insert(record);
            std::cout << "Reservation Restored Successfully for " << record.studentName << "!\n";
            return;
        }
    }
    std::cout << "Cannot restore reservation; resource is currently occupied.\n";
    cancellationHistory.push(record); // Push back if unable to restore
}

void ReservationManager::displayWaitingList() const {
    std::cout << "\n===== Waiting List =====\n";
    waitingList.display();
}

void ReservationManager::displayCancellationHistory() const {
    std::cout << "\n===== Cancellation History (Stack Top) =====\n";
    if (cancellationHistory.empty()) {
        std::cout << "Stack is empty.\n";
        return;
    }
    ReservationRecord topRec = cancellationHistory.top();
    std::cout << "Most Recent Cancellation -> ID: " << topRec.reservationId 
              << " | Student: " << topRec.studentName 
              << " | Resource ID: " << topRec.resourceId << "\n";
}
