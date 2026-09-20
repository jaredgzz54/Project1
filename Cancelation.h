#ifndef CANCELATION_H
#define CANCELATION_H

#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct CancelationNode {
	string studentName;

};

/*
	Stack Functions (Context is CancelationHistory)
		CancelationHistory.top();	// Access first element (Can be used as a read or write)
		CancelationHistory.push();	// Add element to top of stack (Requires data)
		CancelationHistory.pop();	// Removes top element of stack
		CancelationHistory.empty(); // Checks if stack is empty (If empty will output 0
*/
class CanelationHistoryClass {
	private:
		stack<CancelationNode> CancelationHistory;

	public:
		void DisplayCancelationHistory(); // Cannot be declared as const because what we plan to do with stack
};







#endif
