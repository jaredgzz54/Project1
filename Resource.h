#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <stack>
#include <vector>

struct WaitingRequest {
    std::string studentId;
    std::string studentName;
    std::string resourceId;
};

class WaitingList {
private:
    std::string resourceId;
    std::queue<WaitingRequest> requests;

public:
    explicit WaitingList(const std::string& resourceID = "");

    bool enqueue(const WaitingRequest& request);
    bool dequeue(WaitingRequest& next);
    bool removeStudent(const std::string& studentID);
    bool peek(WaitingRequest& front) const;
    bool contains(const std::string& studentID) const;
    bool isEmpty() const;
    int size() const;
    std::string getResourceId() const;
    void display() const;
};

class Resource {
private:
    std::string resourceId;
    std::string resourceName;
    std::string resourceType;
    bool isAvailable;

public:
    Resource();
    Resource(std::string id, std::string name, std::string type, bool available);

    std::string getResourceId() const;
    std::string getResourceName() const;
    std::string getResourceType() const;
    bool getAvailability() const;

    void setAvailability(bool available);
    void display() const;
};

#endif
