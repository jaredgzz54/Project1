#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
using namespace std;

class Resource {
private:
    int resourceId;
    string name;
    bool isAvailable;
    int reservationCount; // Tracks utilization

public:
    Resource();
    Resource(int id, string resName, bool available);
    
    int getResourceId() const;
    string getName() const;
    bool getAvailability() const;
    int getReservationCount() const;
    
    void setAvailability(bool available);
    void incrementReservationCount();
    void display() const;
};

#endif
