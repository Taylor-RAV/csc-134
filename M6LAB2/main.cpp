#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 1. Enumerations for readability
enum Direction { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3, NUM_DIRECTIONS = 4 };
const string DIRECTION_NAMES[NUM_DIRECTIONS] = { "north", "east", "south", "west" };

// HIDDEN_SANCTUM added to the Room list
enum Room { CASTLE_GATE, GREAT_HALL, SCRIPTORIUM, KITCHEN, COURTYARD, DUNGEON, HIDDEN_SANCTUM, NUM_ROOMS };

int main() {
    // 2. Parallel Arrays: Names, Descriptions, and starting Items
    string roomNames[NUM_ROOMS] = {
        "Castle Gate", "Great Hall", "Scriptorium", "Castle Kitchen", "Outer Courtyard", "Dungeon", "Hidden Sanctum"
    };

    string roomDescriptions[NUM_ROOMS] = {
        "You stand before a massive iron gate. An elderly butler watches you closely.",
        "The hall is vast and cold. A large, dusty tapestry hangs on the north wall.",
        "The room is filled with dusty scrolls and the smell of old parchment.",
        "The kitchen is cluttered with iron pots. A faint smell of stew lingers.",
        "The wind whistles through this open stone courtyard.",
        "It is dark and damp here. You hear water dripping in the distance.",
        "A secret room filled with golden light and ancient treasures. You've found the heart of the fortress!"
    };

    // Parallel Array for Items: Each index corresponds to the Room enum
    string roomItems[NUM_ROOMS] = { "", "", "Sliver of Glass", "Rusty Key", "Stone Fragment", "Iron Gear", "" };

    // 3. Adjacency List (The Map)
    int connections[NUM_ROOMS][NUM_DIRECTIONS];
    for (int i = 0; i < NUM_ROOMS; i++) {
        for (int j = 0; j < NUM_DIRECTIONS; j++) connections[i][j] = -1;
    }

    // Set up initial map connections
    connections[CASTLE_GATE][NORTH] = GREAT_HALL;
    connections[GREAT_HALL][SOUTH]  = CASTLE_GATE;
    connections[GREAT_HALL][NORTH]  = SCRIPTORIUM;
    connections[GREAT_HALL][EAST]   = KITCHEN;
    connections[GREAT_HALL][WEST]   = COURTYARD;
    connections[SCRIPTORIUM][SOUTH] = GREAT_HALL;
    connections[KITCHEN][WEST]      = GREAT_HALL;
    connections[KITCHEN][SOUTH]     = DUNGEON;
    connections[COURTYARD][EAST]    = GREAT_HALL;
    connections[DUNGEON][NORTH]     = KITCHEN;

    int currentRoom = CASTLE_GATE;
    bool hasPermission = false;
    int puzzlePieces = 0;
    bool secretRevealed = false;
    vector<string> inventory;
    bool gameRunning = true;

    cout << "--- Fortress of the Iron Crown ---" << endl;

    while (gameRunning) {
        cout << "\n==========================================" << endl;
        cout << "LOCATION: " << roomNames[currentRoom] << endl;
        cout << roomDescriptions[currentRoom] << endl;

       // Show available exits
cout << "Available exits: ";
bool first = true;
for (int i = 0; i < NUM_DIRECTIONS; i++) {
    if (connections[currentRoom][i] != -1) {
        // Special check: don't show North at the Gate if they don't have permission
        if (currentRoom == CASTLE_GATE && i == NORTH && !hasPermission) continue;

        if (!first) cout << ", ";
        cout << DIRECTION_NAMES[i];
        first = false;
    }
}
cout << endl;

 // Butler Logic at the Gate
        if (currentRoom == CASTLE_GATE) {
            if (!hasPermission) {
                cout << "[!] Butler: 'You may not pass without a proper greeting (type 'greet').'" << endl;
            } else if (puzzlePieces == 4 && !secretRevealed) {
                cout << "[!] Butler: 'I see you've found all the pieces. There is a door behind the tapestry in the Great Hall...'" << endl;
                // Modify the map to allow access to the hidden room
                connections[GREAT_HALL][NORTH] = HIDDEN_SANCTUM;
                secretRevealed = true;
            }
        }

        // Check if an item is in the room
        if (roomItems[currentRoom] != "") {
            cout << "You see a " << roomItems[currentRoom] << " here." << endl;
        }

        cout << "\n(n, s, e, w | take | greet | i | q)" << endl;
        string command;
        cout << "> ";
        cin >> command;

        if (command == "q" || command == "quit") {
            gameRunning = false;
        }
        else if (command == "greet" && currentRoom == CASTLE_GATE) {
            cout << "The Butler bows. 'Enter, but keep an eye out for the 4 lost puzzle pieces.'" << endl;
            hasPermission = true;
        }
        else if (command == "take") {
            if (roomItems[currentRoom] != "") {
                cout << "You picked up the " << roomItems[currentRoom] << "!" << endl;
                inventory.push_back(roomItems[currentRoom]);
                roomItems[currentRoom] = ""; // Remove item from room
                puzzlePieces++;
            } else {
                cout << "Nothing to take here." << endl;
            }
        }
        else if (command == "i" || command == "inventory") {
            cout << "Puzzle Pieces: " << puzzlePieces << "/4. Items: ";
            for (const string& item : inventory) cout << "[" << item << "] ";
            cout << endl;
        }
        else {
            int dir = -1;
            if (command == "n" || command == "north") dir = NORTH;
            else if (command == "e" || command == "east") dir = EAST;
            else if (command == "s" || command == "south") dir = SOUTH;
            else if (command == "w" || command == "west") dir = WEST;

            if (dir != -1) {
                if (currentRoom == CASTLE_GATE && dir == NORTH && !hasPermission) {
                    cout << "The butler blocks your path!" << endl;
                } else if (connections[currentRoom][dir] != -1) {
                    currentRoom = connections[currentRoom][dir];
                } else {
                    cout << "You cannot go that way." << endl;
                }
            } else {
                cout << "Unknown command." << endl;
            }
        }

        // Winning condition check
        if (currentRoom == HIDDEN_SANCTUM) {
            cout << "\nCongratulations! You've found the Hidden Sanctum and won the game!" << endl;
            gameRunning = false;
        }
    }

    cout << "Thanks for playing!" << endl;
    return 0;
}
/*
   AI Help Used: Claude/Google AI
   Prompt: "Help me remove unneeded parts of my code to fit M6 Lab 2 specs,
   using parallel arrays for descriptions/items and an adjacency list.
   Add a 4-item puzzle and a hidden room unlocked by a butler."
*/
