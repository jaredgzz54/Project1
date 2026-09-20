#include "Reservation.h"

DoublyLinkedList::DoublyLinkedList()
{

}

//allocates new node with items as the data for the node
void DoublyLinkedList::DLLPreppend(xx, item)
{
    Node newNode = item;
    DLLPreppendNode(xx, newNode)
}

void DoublyLinkedList::DLLPreppendNode(xx, newNode)
{
    if(xx->head == null)
    {
        xx->head = newNode;
        xx->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
}
//xy is the name of the class for resources and the data type of itemtosearch
Resource DoublyLinkedList::DLLSearch(xx, itemtosearch)
{
    currentNode = list->head;
    while(currentNode != null)
    {
        if(currentNode->head == itemtosearch)
        {
            return itemtosearch;
        }
        currentNode = currentNode->next
    }

    return null;
}

DoublyLinkedList::DLLRemove(xx, itemToRemove)
{   
    if(DLLSearch(xx, itemToRemove) == null){
        cout << "Item not found" << endl;
        break;
    }
    successor = itemToRemove->next;
    predecessor = itemToRemove->prev;

    if(successor != null)
    {
        successor->prev = predecessor
    }

    if(predecessor != null)
    {
        predecessor->next = successor
    }

    if(currentNode == xx->head)
    {
        xx->head = successor
    }

    if(currentNode == xx->tail)
    {
        xx->tail == predecessor
    }
}