// Franck Limtung
// 2021-Feb-08
// CSCI235
#include <iostream>
#include <vector>

/*
 * 
 can only move one disc at a time
discs must be either in transit or on a tower (never on the ground)
you can never place a larger disc on a smaller disc
*/

void hanoi_iter(int n) {
	// Deal with small cases
	if (n < 3) {
		if (n <= 0) std::cout << "No steps needed/possible.\n";
		if (n == 1) std::cout << "Move disc 1 from Source tower to Target tower.\n";
		if (n == 2) {
			std::cout << "Move disc 1 from Source tower to Temporary tower.\n";
			std::cout << "Move disc 2 from Source tower to Target tower.\n";
			std::cout << "Move disc 1 from Temporary tower to Target tower.\n";
		}

		return;
	}
	// Pairs connect a tower to its original name even if we change our usage of the towers
	std::pair<std::string, std::vector<int>> src;
	src.first = "Source tower";
	std::pair<std::string, std::vector<int>> dst;
	dst.first = "Destination tower";
	std::pair<std::string, std::vector<int>> tmp;
	tmp.first = "Temporary tower";

	// Fill source with n discs
	for (int i = 0; i < n; i++) {
		src.second.push_back(n - i);
	}

	// Pointers to the three towers. In this algorithm, the pointers change every time we complete an iteration
	std::pair<std::string, std::vector<int>>* targetTower;
	std::pair<std::string, std::vector<int>>* tempTower;
	std::pair<std::string, std::vector<int>>* startTower = &src;

	// The height of the disc stack determines the first target tower
	if (n % 2 == 0) {
		targetTower = &tmp;
		tempTower = &dst;
	}
	else {
		targetTower = &dst;
		tempTower = &tmp;
	}

	bool done = false;
	while (!done) {
		// Treat the top 3 discs as one unit which is moved to the next tower (looping around) every iteration. The 3 discs start at startTower, and end up at targetTower when they are moved.
		// This leaves startTower and tempTower open for manipulation
		targetTower->second.push_back(startTower->second.back()); // Move disc 1 to target
		startTower->second.pop_back();
		std::cout << "Move disc " << targetTower->second.back() << " from " << startTower->first << " to " << targetTower->first << ".\n";
		tempTower->second.push_back(startTower->second.back()); // Move disc 2 to temporary
		startTower->second.pop_back();
		std::cout << "Move disc " << tempTower->second.back() << " from " << startTower->first << " to " << tempTower->first << ".\n";
		tempTower->second.push_back(targetTower->second.back());// Stack disc 1 on disc 2
		targetTower->second.pop_back();
		std::cout << "Move disc " << tempTower->second.back() << " from " << targetTower->first << " to " << tempTower->first << ".\n";
		targetTower->second.push_back(startTower->second.back()); // Move disc 3 to target
		startTower->second.pop_back();
		std::cout << "Move disc " << targetTower->second.back() << " from " << startTower->first << " to " << targetTower->first << ".\n";
		startTower->second.push_back(tempTower->second.back()); // Move disc 1 to start
		tempTower->second.pop_back();
		std::cout << "Move disc " << startTower->second.back() << " from " << tempTower->first << " to " << startTower->first << ".\n";
		targetTower->second.push_back(tempTower->second.back()); // Stack disc 2 on disc 3
		tempTower->second.pop_back();
		std::cout << "Move disc " << targetTower->second.back() << " from " << tempTower->first << " to " << targetTower->first << ".\n";
		targetTower->second.push_back(startTower->second.back()); // Stack disc 1 on disc 2 and 3
		startTower->second.pop_back();
		std::cout << "Move disc " << targetTower->second.back() << " from " << startTower->first << " to " << targetTower->first << ".\n";
		if (src.second.size() == 0 && tmp.second.size() == 0) {
			// We are done
			done = true;
		}
		else {
			// We freed up the startTower and the tempTower. Now we move a disc from one to the other
			// We move a disc so that it either fills an empty space or builds a stack
			if ((startTower->second.size() > 0 && (tempTower->second.size() == 0 || startTower->second.back() < tempTower->second.back()))) {
				// startTower is not empty, plus tempTower is either empty or has a bigger disc on it
				tempTower->second.push_back(startTower->second.back());
				startTower->second.pop_back();
				std::cout << "Move disc " << tempTower->second.back() << " from " << startTower->first << " to " << tempTower->first << ".\n";
			}
			else if (startTower->second.size() == 0 || tempTower->second.back() < startTower->second.back()) {
				// Opposite of the above
				startTower->second.push_back(tempTower->second.back());
				tempTower->second.pop_back();
				std::cout << "Move disc " << startTower->second.back() << " from " << tempTower->first << " to " << startTower->first << ".\n";
			}

			// Iteration done; temp now becomes the target, target becomes the start, and start becomes the temp for the next iteration

			std::pair<std::string, std::vector<int>>* swapPtr = &*targetTower;
			targetTower = &*tempTower;
			tempTower = &*startTower;
			startTower = &*swapPtr;
		}
	}
}

// I couldn't figure out a way to do this recursively so I used tail recursion of the iterative one
void hanoi(std::pair<std::string, std::vector<int>>* startTower, std::pair<std::string, std::vector<int>>* tempTower, std::pair<std::string, std::vector<int>>* targetTower) {
	targetTower->second.push_back(startTower->second.back()); // Move disc 1 to target
	startTower->second.pop_back();
	std::cout << "Move disc " << targetTower->second.back() << " from " << startTower->first << " to " << targetTower->first << ".\n";
	tempTower->second.push_back(startTower->second.back()); // Move disc 2 to temporary
	startTower->second.pop_back();
	std::cout << "Move disc " << tempTower->second.back() << " from " << startTower->first << " to " << tempTower->first << ".\n";
	tempTower->second.push_back(targetTower->second.back());// Stack disc 1 on disc 2
	targetTower->second.pop_back();
	std::cout << "Move disc " << tempTower->second.back() << " from " << targetTower->first << " to " << tempTower->first << ".\n";
	targetTower->second.push_back(startTower->second.back()); // Move disc 3 to target
	startTower->second.pop_back();
	std::cout << "Move disc " << targetTower->second.back() << " from " << startTower->first << " to " << targetTower->first << ".\n";
	startTower->second.push_back(tempTower->second.back()); // Move disc 1 to start
	tempTower->second.pop_back();
	std::cout << "Move disc " << startTower->second.back() << " from " << tempTower->first << " to " << startTower->first << ".\n";
	targetTower->second.push_back(tempTower->second.back()); // Stack disc 2 on disc 3
	tempTower->second.pop_back();
	std::cout << "Move disc " << targetTower->second.back() << " from " << tempTower->first << " to " << targetTower->first << ".\n";
	targetTower->second.push_back(startTower->second.back()); // Stack disc 1 on disc 2 and 3
	startTower->second.pop_back();
	std::cout << "Move disc " << targetTower->second.back() << " from " << startTower->first << " to " << targetTower->first << ".\n";
	if (startTower->second.size() == 0 && tempTower->second.size() == 0) {
			// We are done
			return;
	}
	else {
		if ((startTower->second.size() > 0 && (tempTower->second.size() == 0 || startTower->second.back() < tempTower->second.back()))) {
			tempTower->second.push_back(startTower->second.back());
			startTower->second.pop_back();
			std::cout << "Move disc " << tempTower->second.back() << " from " << startTower->first << " to " << tempTower->first << ".\n";
			}
		else if (startTower->second.size() == 0 || tempTower->second.back() < startTower->second.back()) {
			startTower->second.push_back(tempTower->second.back());
			tempTower->second.pop_back();
			std::cout << "Move disc " << startTower->second.back() << " from " << tempTower->first << " to " << startTower->first << ".\n";
		}
		hanoi(targetTower, startTower, tempTower);
	}
}

void hanoi(int n) {
	if (n < 3) {
		if (n <= 0) std::cout << "No steps needed/possible.\n";
		if (n == 1) std::cout << "Move disc 1 from Source tower to Target tower.\n";
		if (n == 2) {
			std::cout << "Move disc 1 from Source tower to Temporary tower.\n";
			std::cout << "Move disc 2 from Source tower to Target tower.\n";
			std::cout << "Move disc 1 from Temporary tower to Target tower.\n";
		}

		return;
	}
	std::pair<std::string, std::vector<int>> src;
	src.first = "Source tower";
	std::pair<std::string, std::vector<int>> dst;
	dst.first = "Destination tower";
	std::pair<std::string, std::vector<int>> tmp;
	tmp.first = "Temporary tower";

	for (int i = 0; i < n; i++) {
		src.second.push_back(n - i);
	}

	std::pair<std::string, std::vector<int>>* targetTower;
	std::pair<std::string, std::vector<int>>* tempTower;
	std::pair<std::string, std::vector<int>>* startTower = &src;

	if (n % 2 == 0) {
		targetTower = &tmp;
		tempTower = &dst;
	}
	else {
		targetTower = &dst;
		tempTower = &tmp;
	}

	hanoi(startTower, tempTower, targetTower);
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Error; Please input number of discs when running program.\n";
		return 0;
	}
	hanoi(atoi(argv[1]));
	
	return 0;
}
