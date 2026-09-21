#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include "Resource.h"
#include "Reservation.h"
#include <vector>
#include <stack>

class ReservationManager {
private:
    std::vector<Resource> resources;
    DoublyLinkedList activeReservations;
    std::stack<ReservationRecord> cancellationHistory;
    WaitingList waitingList; // Simplified single waiting list tracker for milestone

public:
    ReservationManager();

    void loadResources(const std::string& filename);
    void displayAllResources() const;
    void displayResourceAvailability() const;
    
    void createReservation();
    void cancelReservation();
    void displayActiveReservations() const;
    void undoCancellation();
    void displayWaitingList() const;
    void displayCancellationHistory() const;
};

#endif
#include "ReservationManager.h"
