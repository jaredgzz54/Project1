#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>
#include <queue>
#include <string>

// ===================== Waiting List (Milestone 1) =====================

struct WaitingRequest
{
    std::string studentID;
    std::string studentName;
    std::string resourceID;
};

/*
 * WaitingList
 * FIFO waiting list for ONE resource
 * the first student to join is the first student served
 * each resource owns one
 * when a resource becomes available, call dequeue() to get the next student and create a reservation for them
 */

class WaitingList
{
private:
    std::string resourceID;               // resource this list belongs to
    std::queue<WaitingRequest> requests;  // FIFO queue of waiting students

public:
    // creates an empty waiting list for given resourceID 
    explicit WaitingList(const std::string& resourceID = "");

    /*
     * adds a student to the back of the waiting list
     * returns false & prints message if student is already waiting
     */

    bool enqueue(const WaitingRequest& request);

    /*
     * removes and returns the student at the FRONT of the list FIFO
     * returns false if the list is empty; next on success
     */

    bool dequeue(WaitingRequest& next);

    /*
     * removes a student from anywhere in the list
     */

    bool removeStudent(const std::string& studentID);

    /** copies front request into front & keeps it */

    bool peek(WaitingRequest& front) const;

    /** returns true if student is in wating list */

    bool contains(const std::string& studentID) const;

    bool isEmpty() const;
    int size() const;
    const std::string& getResourceID() const;

    /** prints waiting list in order. */

    void display() const;
};

// ===================== resource class below =====================
/*
 * Resource
 * stores the info for one campus resource (study room, laptop, calculator, etc.)
 * each resource owns its own waiting list
 */

class Resource
{
private:
    std::string resourceID;
    std::string resourceName;
    std::string resourceType;
    bool available;               // true = can be reserved right now
    WaitingList waitingList;      // students waiting for this resource
    int requestCount;             // how many times students asked for this resource (popularity)

public:
    Resource(const std::string& id, const std::string& name, const std::string& type, bool isAvailable);

    std::string getResourceId() const;
    std::string getResourceName() const;
    std::string getResourceType() const;
    bool getAvailability() const;
    void setAvailability(bool isAvailable);
    int getRequestCount() const;
    void addRequest();            // adds 1 to requestCount

    // gives access to this resource's waiting list
    WaitingList& getWaitingList();              // used when adding/removing students
    const WaitingList& getWaitingList() const;  // used when only displaying

    /** prints all info for this resource on one line */

    void display() const;
};


#endif
