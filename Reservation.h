#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

using namespace std;

//Global Variables
const int SIZE = 8;
enump options {ViewR = 1, CreateR = 2, CancelR = 3, ViewW = 4, UndoC = 5, SearchR = 6, SortR = 7, GenerateRepo = 8, Exit = 9};

struct Node{
    int data;
    Node* next;
    Node* prev;
}
class DoublyLinkedList{

        private:

        Node* head;
        Node* tail;

        public:
        //xx is a place holder to be the name for list that will be added later in the main
        DoublyLinkedList();
        ~DoublyLinkedList();
        DDLAppend(xx,item);
        DDLAppendNode(xx, newNode);
        DDLRemove(xx,itemToRemove);
        DDLSearch(xx,itemtosearch);


}

clas




#endif