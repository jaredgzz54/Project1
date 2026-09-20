#include "Cancelation.h"

void CanelationHistoryClass::DisplayCancelationHistory() {
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

