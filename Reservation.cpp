#include "Reservation.h"

DoublyLinkedList::DoublyLinkedList()
{
    head = nullptr;
    tail = nullptr;
}

DoublyLinkedList::~DoublyLinkedList()
{
    Node* currentNode = head;

    while (currentNode != nullptr)
    {
        Node* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }

    head = nullptr;
    tail = nullptr;
}

//allocates new node with item as the data for the node
void DoublyLinkedList::DLLPreppend(DoublyLinkedList* list, int item)
{
    Node* newNode = new Node;
    newNode->data = item;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    DLLPreppendNode(list, newNode);
}

void DoublyLinkedList::DLLPreppendNode(DoublyLinkedList* list, Node* newNode)
{
    if (list->head == nullptr)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        newNode->next = list->head;
        newNode->prev = nullptr;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

//Searches for a node containing itemToSearch
Node* DoublyLinkedList::DLLSearch(DoublyLinkedList* list, int itemToSearch)
{
    Node* currentNode = list->head;

    while (currentNode != nullptr)
    {
        if (currentNode->data == itemToSearch)
        {
            return currentNode;
        }

        currentNode = currentNode->next;
    }

    return nullptr;
}

void DoublyLinkedList::DLLRemove(DoublyLinkedList* list, Node* itemToRemove)
{
    if (itemToRemove == nullptr)
    {
        cout << "Item not found" << endl;
        return;
    }

    Node* successor = itemToRemove->next;
    Node* predecessor = itemToRemove->prev;

    if (successor != nullptr)
    {
        successor->prev = predecessor;
    }

    if (predecessor != nullptr)
    {
        predecessor->next = successor;
    }

    if (itemToRemove == list->head)
    {
        list->head = successor;
    }

    if (itemToRemove == list->tail)
    {
        list->tail = predecessor;
    }

    delete itemToRemove;
}



// Cancelation cpp Code
void CancelationHistoryClass::DisplayCancelationHistory() {
	int const arrSize = CancelationHistory.size();
	vector<CancelationNode> data;

	// Ittrates throughout entire stack and displays information
	while (CancelationHistory.empty() == 1) {

		// Display information here
		cout << CancelationHistory.top().studentName << endl;

		// Add item to vector then delete top
		data.push_back(CancelationHistory.top());
		CancelationHistory.pop();
	}



	// Add items back to stack
	while (data.empty() == 1) {

		// Adds item 0 from vector to stack again
		CancelationHistory.push(data.at(0));

		// Delete item 0 from vector
		data.erase(data.begin());
	}
}
