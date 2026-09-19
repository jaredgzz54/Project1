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
 * FIFO waiting list for ONE resource, built on std::queue.
 * the first student to join is the first student served.
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

#endif
