GitHub Repository URL: https://github.com/jaredgzz54/Project1.git

Group Contribution Report: https://docs.google.com/document/d/1mC1DFmTWcgEdEb5bEbnaNe5KoyBJ3EarcvYEoPTYydw/edit?usp=sharing

Hey, guys. I'm Jared, and this is the repo for CSCE 2110 project 1. We need to complete this by or before 9/20/2026. We need to focus on Resource Management, Reservation Management, and Waiting List Management. Each one has its own subs in a way. A Linked List must be used to create the reservation and to be able to traverse and delete items, as well as Display. When canceling reservations, the order of the canceled items must be stored in a stack so we can undo if it was a mistake. In the reservation system, if items are being reserved by multiple people, it must use a queue to keep track of how many people are in front of you. Lastly, we need to load previous info of people that already reserved items using fstream. Other items are needed, but aren't code. One is Big-O notation for the complexity. Please be respectful and use meaningful comments to talk with each other and explain why you are writing code the way you are. Keep it brief. Let's work on this together and do the best we can.

Campus Resource Reservation System
==================================

A menu-driven C++ program for reserving campus resources (study rooms,
laptops, calculators, lab equipment, tutoring). It supports reservations,
cancellations, per-resource waiting lists, undoing the most recent
cancellation, searching, sorting, and system reports.

Folder Layout
-------------
include/   Header files (Resource.h, Reservation.h, ReservationManager.h)
src/       Source files (main.cpp, Resource.cpp, Reservation.cpp, ReservationManager.cpp)
data/      resources.txt and reservations.txt (loaded at startup)

Data File Formats
-----------------
resources.txt    - ID|Name|Type|Availability   (Available or Unavailable)
                   R101|Study Room 101|Study Room|Available
reservations.txt - ReservationID|StudentID|StudentName|ResourceID|Date
                   301|1001|Alice Smith|R101|09/15/2026

Each resource starts with the availability listed in resources.txt.
Reservations whose resource ID does not exist, or whose reservation ID is
already used, are skipped when loading. New reservation IDs continue after
the highest ID in reservations.txt. A cancelled resource only becomes free
(or goes to the next waiting student) once it has no other active
reservations.

Menu
----
1. View Resources              7. View Cancellation History Stack
2. Create Reservation          8. Search
3. Cancel Reservation          9. Sort Resources
4. View Active Reservations    10. Generate Report
5. Undo Cancellation           11. Exit
6. View Waiting List

Data Structures Used
--------------------
Linked List (DoublyLinkedList)  - stores active reservations
Queue (WaitingList)             - one FIFO waiting list per resource
Stack (in ReservationManager)   - cancellation history and undo
Vector                          - resource inventory (and sorting)

Searching
---------
Linear search, written by the team (no library search functions):
- Resource by ID: findResource (ReservationManager.cpp)
- Reservation by ID: DoublyLinkedList::search
- Reservations by student: DoublyLinkedList::displayByStudent
Linear search was chosen because the reservations are in a linked list
(no random access) and it does not require the data to be sorted first.

Sorting
-------
Merge sort, written by the team: mergeSortResources and
mergeResources in ReservationManager.cpp. Resources can be sorted by name,
by popularity (most requested first), or by resource ID. The report
sorts a copy of the list so the main resource list is not changed.

Reports
-------
- Active reservations (total count and list)
- Resource utilization (each resource and its number of active reservations)
- Most requested resources (top 5 by request count)
- Waiting-list statistics (students waiting per resource and total)

Complexity Analysis
-------------------
n = active reservations, r = resources, w = students on a waiting list,
k = cancellations on the stack

Reservation insertion: O(1) for the linked list insert, since the new node
is attached at the tail pointer. Creating a reservation overall is O(r + n)
because it linearly searches for the resource ID and checks the list so the
new reservation ID is not a duplicate.

Reservation removal: O(n). Finding the reservation by ID is a linear search
through the list. Unlinking the node once found is O(1) because each node
has prev and next pointers. Checking whether another reservation still uses
the resource is another O(n) pass.

Waiting-list processing: enqueue is O(w) because it first checks that the
student is not already waiting; the push itself is O(1). dequeue (giving the
resource to the next student) is O(1). removeStudent and display are O(w).

Undo cancellation: O(r). Popping the top of the stack is O(1) and
re-inserting into the linked list is O(1); the linear search for the
resource to check availability is O(r). Displaying the full history is O(k).

Searching: O(r) for a resource, O(n) for a reservation or a student's
reservations (worst case checks every item).

Sorting: merge sort is O(r log r) in every case and uses O(r) extra space
for the temporary vector during merging.

Report: O(r * n), because utilization counts each resource's reservations
by walking the linked list once per resource.

Documentation By: Isaac N.
