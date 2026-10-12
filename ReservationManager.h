#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include "Resource.h"
#include "Reservation.h"
#include <vector>
#include <stack>

using namespace std;

class ReservationManager {
private:
    vector<Resource> resources;
    DoublyLinkedList activeReservations;
    stack<ReservationRecord> cancellationHistory;
    int nextReservationNumber; // used to make new reservation IDs

public:
    ReservationManager();

    void loadResources(const string& filename);
    void loadReservations(const string& filename);
    void displayAllResources() const;
    void displayResourceAvailability() const;

    void createReservation();
    void cancelReservation();
    void displayActiveReservations() const;
    void undoCancellation();
    void displayWaitingList() const;
    void displayCancellationHistory() const;

    void searchMenu();
    void sortResources();
    void generateReport();
};

#endif
