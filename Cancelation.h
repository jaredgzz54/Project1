#ifndef CANCELATION_H
#define CANCELATION_H

#include <iostream>
#include <stack>

using namespace std;

struct CancelationNode {

};

/*
	Stack Functions (Context is CancelationHistory)
		CancelationHistory.top();	// Access first element (Can be used as a read or write)
		CancelationHistory.push();	// Add element to top of stack (Requires data)
		CancelationHistory.pop();	// Removes top element of stack
		CancelationHistory.empty(); // Checks if stack is empty (If empty will output 0
*/
stack<CancelationNode> CancelationHistory;






#endif
