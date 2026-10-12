#include <iostream>
#include <queue>
#include <set>
#include <string>

using namespace std;

// We can only use cstdio and iostream, so we'll implement our own min and max heaps
// using priority_queue with appropriate comparators

class Elevator {
private:
    int currentFloor;
    bool movingUp; // true for up, false for down
    
    // Two sets to store floor requests (using set for efficient removal)
    // We use set instead of priority_queue to support cancel operation
    set<int> upRequests;    // Requests above current floor that need upward movement
    set<int> downRequests;  // Requests below current floor that need downward movement
    
    // Also keep track of all requests to handle cancel properly
    set<int> allRequests;

public:
    Elevator() : currentFloor(0), movingUp(true) {}
    
    void addRequest(int floor) {
        // Add to appropriate request set based on floor position
        if (floor > currentFloor) {
            upRequests.insert(floor);
        } else if (floor < currentFloor) {
            downRequests.insert(floor);
        }
        allRequests.insert(floor);
    }
    
    void cancelRequest(int floor) {
        // Remove from all sets
        upRequests.erase(floor);
        downRequests.erase(floor);
        allRequests.erase(floor);
    }
    
    void action() {
        // If no requests, do nothing (keep current direction)
        if (allRequests.empty()) {
            return;
        }
        
        // Check if there are requests in the current direction
        if (movingUp && !upRequests.empty()) {
            // Go to the closest floor in the upward direction
            currentFloor = *upRequests.begin();
            upRequests.erase(upRequests.begin());
            allRequests.erase(currentFloor);
        } else if (!movingUp && !downRequests.empty()) {
            // Go to the closest floor in the downward direction
            currentFloor = *downRequests.rbegin();
            downRequests.erase(prev(downRequests.end()));
            allRequests.erase(currentFloor);
        } else {
            // No requests in current direction, reverse direction
            movingUp = !movingUp;
            
            // Now handle the request in the new direction
            if (movingUp && !upRequests.empty()) {
                currentFloor = *upRequests.begin();
                upRequests.erase(upRequests.begin());
                allRequests.erase(currentFloor);
            } else if (!movingUp && !downRequests.empty()) {
                currentFloor = *downRequests.rbegin();
                downRequests.erase(prev(downRequests.end()));
                allRequests.erase(currentFloor);
            }
        }
    }
    
    int getCurrentFloor() const {
        return currentFloor;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    Elevator elevator;
    
    for (int i = 0; i < n; i++) {
        string operation;
        cin >> operation;
        
        if (operation == "action") {
            elevator.action();
        } else if (operation == "add") {
            int floor;
            cin >> floor;
            elevator.addRequest(floor);
        } else if (operation == "cancel") {
            int floor;
            cin >> floor;
            elevator.cancelRequest(floor);
        } else if (operation == "locate") {
            cout << elevator.getCurrentFloor() << endl;
        }
    }
    
    return 0;
}