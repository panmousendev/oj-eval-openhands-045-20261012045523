#include <iostream>
#include <string>

using namespace std;

// We can only use cstdio and iostream, so we'll implement a simple list-based
// structure to store floor requests

class Elevator {
private:
    int currentFloor;
    bool movingUp; // true for up, false for down
    
    // Maximum number of requests
    static const int MAX_REQUESTS = 500000;
    int requests[MAX_REQUESTS];
    int requestCount;

public:
    Elevator() : currentFloor(0), movingUp(true), requestCount(0) {}
    
    // Check if a floor is already in requests
    bool hasRequest(int floor) {
        for (int i = 0; i < requestCount; i++) {
            if (requests[i] == floor) {
                return true;
            }
        }
        return false;
    }
    
    void addRequest(int floor) {
        // Only add if not already present
        if (!hasRequest(floor)) {
            requests[requestCount++] = floor;
        }
    }
    
    void cancelRequest(int floor) {
        for (int i = 0; i < requestCount; i++) {
            if (requests[i] == floor) {
                // Remove by shifting elements
                for (int j = i; j < requestCount - 1; j++) {
                    requests[j] = requests[j + 1];
                }
                requestCount--;
                break;
            }
        }
    }
    
    void action() {
        // If no requests, do nothing (keep current direction)
        if (requestCount == 0) {
            return;
        }
        
        // Find the next floor to go to based on current direction and rules
        int nextFloor = -1;
        
        // First, check if there are requests in the current direction
        if (movingUp) {
            // Look for the closest floor above current floor
            for (int i = 0; i < requestCount; i++) {
                if (requests[i] > currentFloor) {
                    if (nextFloor == -1 || requests[i] < nextFloor) {
                        nextFloor = requests[i];
                    }
                }
            }
        } else {
            // Look for the closest floor below current floor
            for (int i = 0; i < requestCount; i++) {
                if (requests[i] < currentFloor) {
                    if (nextFloor == -1 || requests[i] > nextFloor) {
                        nextFloor = requests[i];
                    }
                }
            }
        }
        
        // If no request in current direction, reverse direction and find closest
        if (nextFloor == -1) {
            movingUp = !movingUp;
            
            if (movingUp) {
                // Look for the closest floor above current floor
                for (int i = 0; i < requestCount; i++) {
                    if (requests[i] > currentFloor) {
                        if (nextFloor == -1 || requests[i] < nextFloor) {
                            nextFloor = requests[i];
                        }
                    }
                }
            } else {
                // Look for the closest floor below current floor
                for (int i = 0; i < requestCount; i++) {
                    if (requests[i] < currentFloor) {
                        if (nextFloor == -1 || requests[i] > nextFloor) {
                            nextFloor = requests[i];
                        }
                    }
                }
            }
        }
        
        // Update current floor and remove the request
        if (nextFloor != -1) {
            currentFloor = nextFloor;
            cancelRequest(nextFloor);
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