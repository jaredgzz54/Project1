// Require header files 
#include "Reservation.h"
#include "Resource.h"
#include "ReservationManager.h"

using namespace std;

int main() {
    ReservationManager manager;
    manager.loadResources("resources.txt");

    int choice = 0;
    do {
        cout << "\n===== Campus Resource Reservation System =====\n";
        cout << "1. View Resources\n";
        cout << "2. Create Reservation\n";
        cout << "3. Cancel Reservation\n";
        cout << "4. View Active Reservations\n";
        cout << "5. Undo Cancellation\n";
        cout << "6. View Waiting List\n";
        cout << "7. View Cancellation History Stack\n";
        cout << "8. Exit\n";
        cout << "Enter Choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
        case 1:
            manager.displayResourceAvailability();
            break;
        case 2:
            manager.createReservation();
            break;
        case 3:
            manager.cancelReservation();
            break;
        case 4:
            manager.displayActiveReservations();
            break;
        case 5:
            manager.undoCancellation();
            break;
        case 6:
            manager.displayWaitingList();
            break;
        case 7:
            manager.displayCancellationHistory();
            break;
        case 8:
            cout << "Exiting system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please select between 1 and 8.\n";
        }
    } while (choice != 8);

    return 0;
}
