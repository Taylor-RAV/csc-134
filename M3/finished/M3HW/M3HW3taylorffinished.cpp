// CSC 134
// M3HW1 - Silver
// James Taylor
// 3/09/2026

#include <iostream>
#include <string>
using namespace std;

int main() {


cout << "\nQuestion 4: Escape the Forest" << endl;
    string choice;

    cout << "You are lost in a dark forest. Do you go 'left' toward the mountains or 'right' toward the river? " << endl;
    getline(cin, choice);

    if (choice == "left") {
        cout << "A rockslide blocks your path. Game Over." << endl;
    } 
    else if (choice == "right") {
        cout << "You reach a wide river. Do you 'swim' across or 'build' a raft?" << endl;
        getline(cin, choice);

        if (choice == "swim") {
            cout << "The current is too strong. You are swept away. Defeat!" << endl;
        } 
        else if (choice == "build") {
            cout << "You safely float downstream to a village. Victory!" << endl;
        } 
        else {
            cout << "You hesitated too long... Game Over." << endl;
        }
    } 
    else {
        cout << "Invalid choice. The forest consumes you." << endl;
    }

    return 0;
}