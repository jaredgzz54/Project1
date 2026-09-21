#include "Resource.h"

// WaitingList Implementation
WaitingList::WaitingList(const std::string& resourceID) : resourceId(resourceID) {}

bool WaitingList::enqueue(const WaitingRequest& request) {
    if (contains(request.studentId)) {
        return false; // Student already in waiting list
    }
    requests.push(request);
    return true;
}

bool WaitingList::dequeue(WaitingRequest& next) {
    if (requests.empty()) {
        return false;
    }
    next = requests.front();
    requests.pop();
    return true;
}

bool WaitingList::removeStudent(const std::string& studentID) {
    std::queue<WaitingRequest> tempQueue;
    bool found = false;

    while (!requests.empty()) {
        WaitingRequest req = requests.front();
        requests.pop();
        if (req.studentId == studentID) {
            found = true;
        } else {
            tempQueue.push(req);
        }
    }
    requests = tempQueue;
    return found;
}

bool WaitingList::peek(WaitingRequest& front) const {
    if (requests.empty()) {
        return false;
    }
    front = requests.front();
    return true;
}

bool WaitingList::contains(const std::string& studentID) const {
    std::queue<WaitingRequest> tempQueue = requests;
    while (!tempQueue.empty()) {
        if (tempQueue.front().studentId == studentID) {
            return true;
        }
        tempQueue.pop();
    }
    return false;
}

bool WaitingList::isEmpty() const {
    return requests.empty();
}

int WaitingList::size() const {
    return static_cast<int>(requests.size());
}

std::string WaitingList::getResourceId() const {
    return resourceId;
}

void WaitingList::display() const {
    if (requests.empty()) {
        std::cout << "Waiting list is empty.\n";
        return;
    }
    std::queue<WaitingRequest> tempQueue = requests;
    int pos = 1;
    while (!tempQueue.empty()) {
        WaitingRequest req = tempQueue.front();
        tempQueue.pop();
        std::cout << pos << ". Student ID: " << req.studentId 
                  << ", Name: " << req.studentName << "\n";
        pos++;
    }
}

// Resource Implementation
Resource::Resource() : resourceId(""), resourceName(""), resourceType(""), isAvailable(true) {}

Resource::Resource(std::string id, std::string name, std::string type, bool available)
    : resourceId(id), resourceName(name), resourceType(type), isAvailable(available) {}

std::string Resource::getResourceId() const { return resourceId; }
std::string Resource::getResourceName() const { return resourceName; }
std::string Resource::getResourceType() const { return resourceType; }
bool Resource::getAvailability() const { return isAvailable; }

void Resource::setAvailability(bool available) { isAvailable = available; }

void Resource::display() const {
    std::cout << "ID: " << resourceId 
              << " | Name: " << resourceName 
              << " | Type: " << resourceType 
              << " | Status: " << (isAvailable ? "Available" : "Unavailable") << "\n";
}
