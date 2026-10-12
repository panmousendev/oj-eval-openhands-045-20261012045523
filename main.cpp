#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    // Just output 0 for locate to see if it compiles
    for (int i = 0; i < n; i++) {
        char op[10];
        cin >> op;
        if (op[0] == 'l') {
            cout << 0 << endl;
        }
    }
    
    return 0;
}