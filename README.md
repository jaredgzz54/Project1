  Hey, guys. I'm Jared, and this is the repo for CSCE 2110 project 1. We need to complete this by or before 9/20/2026. We need to focus on Resource Management, Reservation Management, and Waiting List Management. Each one has its own subs in a way. A Linked List must be used to create the reservation and to be able to traverse and delete items, as well as Display. 
     When canceling reservations, the order of the canceled items must be stored in a stack so we can undo if it was a *mistake*. In the reservation system, if items are being reserved by multiple people, it must use a queue to keep track of how many people are in front of you.
     Lastly, we need to load previous info of people that already reserved items using fstream. Other items are needed, but aren't code. One is Big-O notation for the complexity. Please be respectful and use meaningful comments to talk with each other and explain why you are writing code the way you are. Keep it brief. Let's work on this together and do the best we can. 

I am working on the resource management files.
Waiting List Management - Jacob S

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# Campus Resource Reservation System - User Guide

## Overview
The Campus Resource Reservation System is a command-line application designed to manage university resources (such as projectors, laptops, and rooms), active bookings via a doubly linked list, waiting lists via a queue, and cancellation undo operations via a stack. 

---

## Getting Started & Compilation
To compile and run the program on the UNT CSE CELL machines:
```bash
g++ -std=c++11 Main.cpp Resource.cpp Reservation.cpp -o reservation_system
./reservation_system

Menu Navigation & Features
When you launch the program, you will be presented with a 9-option interactive menu:

Display Resources: Shows all available and reserved campus resources loaded from resources.txt, including their current status and total booking counts.

Create Reservation: Prompts for a Resource ID. If available, it assigns the resource, updates its availability, increments its utilization count, and adds it to the active reservation list. If reserved, it offers to place the student onto the waiting list queue.

Cancel Reservation: Prompts for a Resource ID, removes it from active reservations, marks the resource as available again, and pushes it to the cancellation stack for undo tracking.

Display Active Reservations: Lists all current active bookings currently managed by the Doubly Linked List.

Manage Waiting List / Display Active List: Displays current system queue states and active lists.

Search Resource (Custom Binary Search): Prompts for a Resource ID and runs a hand-written binary search algorithm on the master resource collection.

Sort Active Reservations (Custom Merge Sort): Organizes active reservations by Resource ID using a custom-implemented merge sort algorithm.

Generate System Reports: Displays resource utilization statistics, total system bookings, queue sizes, and stack depths.

Exit: Safely closes the application.

# Campus Resource Reservation System

## Project Overview
A complete C++ campus resource management platform built collaboratively for university project evaluation. It handles resource tracking, active reservations via a doubly linked list, waiting lists via a queue, cancellation rollbacks via a stack, and features hand-written sorting (Merge Sort) and searching (Binary Search) algorithms.

## Project Structure
* `Resource.h` / `Resource.cpp`: Manages individual campus assets, availability, and utilization counters.
* `Reservation.h` / `Reservation.cpp`: Implements the Doubly Linked List, node structures, custom Merge Sort, and custom search routines.
* `Main.cpp`: Manages the interactive menu interface, queues, stacks, reporting, and robust error handling.
* `resources.txt`: External configuration file for loading resource items.

## Compilation & Execution on UNT CSE CELL Machines
```bash
g++ -std=c++11 Main.cpp Resource.cpp Reservation.cpp -o reservation_system
./reservation_system
