#include <iostream>
#include "ReservationManager.h"

int main() {
    ReservationManager manager;
    manager.loadResources("resources.txt");

    int choice = 0;
    do {
        std::cout << "\n===== Campus Resource Reservation System =====\n";
        std::cout << "1. View Resources\n";
        std::cout << "2. Create Reservation\n";
        std::cout << "3. Cancel Reservation\n";
        std::cout << "4. View Active Reservations\n";
        std::cout << "5. Undo Cancellation\n";
        std::cout << "6. View Waiting List\n";
        std::cout << "7. View Cancellation History Stack\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter Choice: ";
        
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
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
                std::cout << "Exiting system. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please select between 1 and 8.\n";
        }
    } while (choice != 8);

    return 0;
}
