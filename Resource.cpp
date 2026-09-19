#include "Resource.h"

using namespace std;

// ===================== Waiting List (Milestone 1) =====================

WaitingList::WaitingList(const string& resourceID)
    : resourceID(resourceID)
{
}

// O(n) complexity
bool WaitingList::enqueue(const WaitingRequest& request)
{
    if (contains(request.studentID))
    {
        cout << "Student " << request.studentID
             << " is already on the waiting list for " << resourceID << "." << endl;
        return false;
    }

    requests.push(request);
    return true;
}

// O(1)
bool WaitingList::dequeue(WaitingRequest& next)
{
    if (requests.empty())
    {
        cout << "The waiting list for " << resourceID << " is empty." << endl;
        return false;
    }

    next = requests.front();
    requests.pop();
    return true;
}

// O(n)
bool WaitingList::removeStudent(const string& studentID)
{
    bool found = false;
    int count = static_cast<int>(requests.size());

    for (int i = 0; i < count; i++)
    {
        WaitingRequest current = requests.front();
        requests.pop();

        if (!found && current.studentID == studentID)
        {
            found = true;            // drop this one
        }
        else
        {
            requests.push(current);  // keep everyone else in order
        }
    }

    if (!found)
    {
        cout << "Student " << studentID << " was not found on the waiting list for "
             << resourceID << "." << endl;
    }
    return found;
}

// O(1)
bool WaitingList::peek(WaitingRequest& front) const
{
    if (requests.empty())
    {
        return false;
    }
    front = requests.front();
    return true;
}

// O(n) works on a copy so the real queue isnt bothered
bool WaitingList::contains(const string& studentID) const
{
    queue<WaitingRequest> copy = requests;

    while (!copy.empty())
    {
        if (copy.front().studentID == studentID)
        {
            return true;
        }
        copy.pop();
    }
    return false;
}

bool WaitingList::isEmpty() const
{
    return requests.empty();
}

int WaitingList::size() const
{
    return static_cast<int>(requests.size());
}

const string& WaitingList::getResourceID() const
{
    return resourceID;
}

// O(n)
void WaitingList::display() const
{
    cout << "--- Waiting List for Resource " << resourceID << " ---" << endl;

    if (requests.empty())
    {
        cout << "No students are currently waiting." << endl;
        return;
    }

    queue<WaitingRequest> copy = requests;
    int position = 1;

    while (!copy.empty())
    {
        const WaitingRequest& r = copy.front();
        cout << position << ". " << r.studentName
             << " (Student ID: " << r.studentID << ")" << endl;
        copy.pop();
        position++;
    }
}

// ===================== Resource class implementation goes below =====================
