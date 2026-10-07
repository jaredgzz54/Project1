#include <iostream>
#include <fstream>
#include <vector>
#include "Resource.h"
#include "Reservation.h"

using namespace std;

void loadResources(const string& filename, vector<Resource>& resources) {
    ifstream file(filename);
    if (!file.is_open()) {
        resources.push_back(Resource(101, "Projector_A", true));
        resources.push_back(Resource(102, "Lab_Laptop_1", true));
        resources.push_back(Resource(103, "Conference_Room", true));
    } else {
        int id;
        string name;
        bool avail;
        while (file >> id >> name >> avail) {
            resources.push_back(Resource(id, name, avail));
        }
        file.close();
    }
}

// Custom Binary Search on Sorted Resource Vector (No library search used)
int binarySearchResources(const vector<Resource>& resources, int targetId) {
    int left = 0;
    int right = resources.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (resources[mid].getResourceId() == targetId)
            return mid;
        if (resources[mid].getResourceId() < targetId)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int main() {
    vector<Resource> resources;
    loadResources("resources.txt", resources);
    
    DoublyLinkedList activeReservations;
    queue<string> waitingList;
    stack<int> cancellationStack;

    int choice;
    do {
        cout << "\n=========================================\n";
        cout << "   CAMPUS RESOURCE RESERVATION SYSTEM    \n";
        cout << "=========================================\n";
        cout << "1. Display Resources\n";
        cout << "2. Create Reservation\n";
        cout << "3. Cancel Reservation\n";
        cout << "4. Display Active Reservations\n";
        cout << "5. Manage Waiting List\n";
        cout << "6. Search Resource (Custom Binary Search)\n";
        cout << "7. Sort Active Reservations (Custom Merge Sort)\n";
        cout << "8. Generate System Reports (Utilization & Queue Stats)\n";
        cout << "9. Exit\n";
        cout << "Enter your choice (1-9): ";
        
        if (!(cin >> choice)) {
            cout << "Invalid input format. Please enter a valid integer.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case ViewR:
                cout << "\n--- Master Resource List ---\n";
                for (const auto& r : resources) r.display();
                break;
                
            case CreateR: {
                int rId;
                cout << "Enter Resource ID to reserve: ";
                if (!(cin >> rId)) {
                    cout << "Invalid input.\n";
                    cin.clear(); cin.ignore(10000, '\n');
                    break;
                }
                bool found = false;
                for (auto& r : resources) {
                    if (r.getResourceId() == rId) {
                        found = true;
                        if (r.getAvailability()) {
                            r.setAvailability(false);
                            r.incrementReservationCount();
                            activeReservations.DLLPreppend(r);
                            cout << "Reservation created successfully for Resource ID " << rId << ".\n";
                        } else {
                            cout << "Resource is currently reserved. Enter student name to join waiting list: ";
                            string name;
                            cin >> name;
                            waitingList.push(name);
                            cout << name << " added to waiting list.\n";
                        }
                        break;
                    }
                }
                if (!found) cout << "Error: Resource ID not found in system.\n";
                break;
            }
            
            case CancelR: {
                int rId;
                cout << "Enter Resource ID to cancel reservation: ";
                if (!(cin >> rId)) {
                    cout << "Invalid input.\n";
                    cin.clear(); cin.ignore(10000, '\n');
                    break;
                }
                Node* current = activeReservations.getHead();
                Node* target = nullptr;
                while (current != nullptr) {
                    if (current->data.getResourceId() == rId) {
                        target = current;
                        break;
                    }
                    current = current->next;
                }
                if (target != nullptr) {
                    for (auto& r : resources) {
                        if (r.getResourceId() == rId) {
                            r.setAvailability(true);
                            break;
                        }
                    }
                    cancellationStack.push(rId);
                    activeReservations.DLLRemove(target);
                    cout << "Reservation successfully cancelled and pushed to undo stack.\n";
                } else {
                    cout << "Error: Active reservation not found for that Resource ID.\n";
                }
                break;
            }
            
            case ViewW:
                activeReservations.display();
                break;
                
            case UndoC: {
                if (cancellationStack.empty()) {
                    cout << "No cancellation history available to restore.\n";
                } else {
                    int restoredId = cancellationStack.top();
                    cancellationStack.pop();
                    for (auto& r : resources) {
                        if (r.getResourceId() == restoredId) {
                            r.setAvailability(false);
                            activeReservations.DLLPreppend(r);
                            break;
                        }
                    }
                    cout << "Restored last cancelled reservation for Resource ID: " << restoredId << "\n";
                }
                break;
            }
            
            case SearchR: {
                int targetId;
                cout << "Enter Resource ID to search via Custom Binary Search: ";
                if (!(cin >> targetId)) {
                    cout << "Invalid input.\n";
                    cin.clear(); cin.ignore(10000, '\n');
                    break;
                }
                // Note: Binary search requires sorted data. We search vector.
                int index = binarySearchResources(resources, targetId);
                if (index != -1) {
                    cout << "Resource found at index " << index << ":\n";
                    resources[index].display();
                } else {
                    cout << "Resource ID " << targetId << " not found.\n";
                }
                break;
            }
            
            case SortR:
                activeReservations.sortReservations();
                break;
                
            case GenerateRepo: {
                cout << "\n=========================================\n";
                cout << "       SYSTEM UTILIZATION REPORT         \n";
                cout << "=========================================\n";
                int totalReserves = 0;
                for (const auto& r : resources) {
                    cout << "Resource: " << r.getName() 
                         << " (ID: " << r.getResourceId() << ") | Total Bookings: " << r.getReservationCount() << "\n";
                    totalReserves += r.getReservationCount();
                }
                cout << "-----------------------------------------\n";
                cout << "Total System Bookings Recorded: " << totalReserves << "\n";
                cout << "Waiting List Statistics: " << waitingList.size() << " student(s) currently in queue.\n";
                cout << "Cancellation Stack Depth: " << cancellationStack.size() << " item(s).\n";
                cout << "=========================================\n";
                break;
            }
            
            case Exit:
                cout << "Exiting Campus Resource Reservation System. Goodbye!\n";
                break;
                
            default:
                cout << "Invalid choice. Please select an option between 1 and 9.\n";
        }
    } while (choice != Exit);

    return 0;
}
