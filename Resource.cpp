#include "Resource.h"
#include <iostream>

Resource::Resource() : resourceId(0), name("Default Resource"), isAvailable(true), reservationCount(0) {}

Resource::Resource(int id, string resName, bool available) 
    : resourceId(id), name(resName), isAvailable(available), reservationCount(0) {}

int Resource::getResourceId() const { return resourceId; }
string Resource::getName() const { return name; }
bool Resource::getAvailability() const { return isAvailable; }
int Resource::getReservationCount() const { return reservationCount; }

void Resource::setAvailability(bool available) { isAvailable = available; }
void Resource::incrementReservationCount() { reservationCount++; }

void Resource::display() const {
    cout << "ID: " << resourceId 
         << " | Name: " << name 
         << " | Status: " << (isAvailable ? "Available" : "Reserved") 
         << " | Total Reservations: " << reservationCount << endl;
}
