/**
 * @file mansion_standalone.cpp
 * @author James Taylor
 * @brief M6HW1 STANDALONE ASSIGNMENT: THE MANSION QUEST
 *
 * BRONZE Tier: 3 Rooms with exits (Foyer, Pantry, Study).
 * SILVER Tier: NPC Dialogue (Caretaker) and Item Interaction (Brass Key).
 * GOLD Tier: Lock/Key Mechanic and a definitive "Deed" Victory Ending.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <conio.h>
#include <ctime>

using namespace std;

// Key Codes for movement
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27

// Room IDs to track where the player is located
enum RoomID { FOYER = 0, PANTRY = 1, STUDY = 2 };

struct Player {
    string name;
    vector<string> inventory;
    RoomID currentRoom;
    bool hasWon;

    // Helper to check for items in the dynamic inventory vector
    bool hasItem(string item) {
        return find(inventory.begin(), inventory.end(), item) != inventory.end();
    }
};

/**
 * Tile Legend:
 * 0: Wall (###)
 * 1: Path ( . )
 * 2: Door to Foyer [F]
 * 3: Door to Pantry [P]
 * 4: Door to Study [S] (LOCKED requirement for Gold)
 * 5: NPC (The Caretaker) [N]
 * 6: Item (Brass Key) [K]
 * 7: Victory Item (The Deed) [V]
 */

int maps[3][7][7] = {
    // ROOM 0: THE FOYER (Bronze Requirement 1)
    {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 5, 1, 1, 0}, // NPC Caretaker [N] at (3,1)
        {0, 1, 0, 0, 0, 1, 0},
        {3, 1, 1, 1, 1, 1, 4}, // Exit Left to Pantry (3), Exit Right to Study (4)
        {0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0}
    },
    // ROOM 1: THE PANTRY (Bronze Requirement 2)
    {
        {0, 0, 0, 2, 0, 0, 0}, // Exit Up to Foyer (2)
        {0, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 1, 0},
        {0, 6, 0, 1, 0, 1, 0}, // Brass Key [K] at (1,3)
        {0, 1, 0, 1, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0}
    },
    // ROOM 2: THE STUDY (Bronze Requirement 3)
    {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 7, 0, 1, 0}, // Master's Deed [V] at (3,2)
        {2, 1, 0, 0, 0, 1, 0}, // Exit Left to Foyer (2)
        {0, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0}
    }
};

void drawGame(int px, int py, const Player& pc) {
    system("cls"); // Clear console screen
    string roomName = (pc.currentRoom == FOYER) ? "GRAND FOYER" :
                      (pc.currentRoom == PANTRY) ? "THE PANTRY" : "MASTER'S STUDY";

    cout << " === MANSION QUEST | AUTHOR: JAMES TAYLOR === " << endl;
    cout << " CURRENT LOCATION: " << roomName << endl;
    cout << " INVENTORY: ";
    if (pc.inventory.empty()) cout << "[None]";
    else for (const auto& i : pc.inventory) cout << "[" << i << "] ";
    cout << "\n --------------------------------------------" << endl;

    for (int i = 0; i < 7; i++) {
        cout << "               ";
        for (int j = 0; j < 7; j++) {
            if (i == py && j == px) cout << "[@]"; // Display Player Avatar
            else {
                int t = maps[pc.currentRoom][i][j];
                switch (t) {
                    case 0: cout << "###"; break; // Wall
                    case 1: cout << " . "; break; // Walkable path
                    case 2: cout << "[F]"; break; // Foyer Door
                    case 3: cout << "[P]"; break; // Pantry Door
                    case 4: cout << "[S]"; break; // Study Door (Locked)
                    case 5: cout << "[N]"; break; // NPC
                    case 6: cout << "[K]"; break; // Key Item
                    case 7: cout << "[V]"; break; // Victory Item
                    default: cout << "   "; break;
                }
            }
        }
        cout << endl;
    }
    cout << "\n CONTROLS: Arrow Keys to move, [S] to interact, [ESC] to quit." << endl;
}

void handleInteraction(Player& pc, int px, int py) {
    int tile = maps[pc.currentRoom][py][px];
    system("cls");

    if (tile == 5) { // SILVER REQUIREMENT: NPC Dialogue
        cout << "--- THE CARETAKER ---" << endl;
        cout << "'Welcome, traveler. I am the caretaker of the Taylor Estate.'" << endl;
        cout << "'The Master has left the Deed in the Study, but the door is locked.'" << endl;
        cout << "'I believe the Brass Key was left in the Pantry. Find it to claim your prize!'" << endl;
    }
    else if (tile == 6) { // SILVER REQUIREMENT: Item Interaction
        cout << "--- ITEM FOUND ---" << endl;
        cout << "You picked up the Brass Key! This should open the Study door." << endl;
        pc.inventory.push_back("Brass Key");
        maps[pc.currentRoom][py][px] = 1; // Change tile to path after pickup
    }
    else if (tile == 7) { // GOLD REQUIREMENT: Definitive Ending
        cout << "--- THE MASTER'S DEED ---" << endl;
        cout << "You retrieve the dusty document. The Taylor Mansion is now yours." << endl;
        cout << "\nCongratulations! You have successfully finished the quest." << endl;
        pc.hasWon = true;
    }
    else {
        cout << "There is nothing to interact with here." << endl;
    }
    system("pause");
}

int main() {
    // Initializing the player state
    Player pc;
    pc.name = "Traveler";
    pc.currentRoom = FOYER;
    pc.hasWon = false;

    int px = 1, py = 3; // Starting position in the Foyer
    bool running = true;

    while (running && !pc.hasWon) {
        drawGame(px, py, pc);

        // Input handling
        int ch = _getch();
        if (ch == KEY_ESC) break;
        if (tolower(ch) == 's') handleInteraction(pc, px, py);

        int nx = px, ny = py;
        // Handling arrow key extended codes
        if (ch == 0 || ch == 224) {
            switch (_getch()) {
                case KEY_UP:    ny--; break;
                case KEY_DOWN:  ny++; break;
                case KEY_LEFT:  nx--; break;
                case KEY_RIGHT: nx++; break;
            }
        }

        // Boundary and Collision Logic
        if (nx >= 0 && nx < 7 && ny >= 0 && ny < 7) {
            int targetTile = maps[pc.currentRoom][ny][nx];

            // Wall Collision
            if (targetTile == 0) continue;

            // BRONZE REQUIREMENT: Exits between rooms
            if (targetTile == 2) { // Transition to Foyer
                if (pc.currentRoom == PANTRY) { pc.currentRoom = FOYER; px = 3; py = 1; }
                else if (pc.currentRoom == STUDY) { pc.currentRoom = FOYER; px = 5; py = 3; }
                continue;
            }

            if (targetTile == 3) { // Transition to Pantry
                pc.currentRoom = PANTRY; px = 3; py = 1;
                continue;
            }

            // GOLD REQUIREMENT: Lock and Key Mechanic
            if (targetTile == 4) {
                if (pc.hasItem("Brass Key")) {
                    cout << "\n[System] You use the Brass Key. The Study door clicks open." << endl;
                    system("pause");
                    pc.currentRoom = STUDY; px = 1; py = 3;
                } else {
                    cout << "\n[System] The Study door is locked tight. You need a key." << endl;
                    system("pause");
                }
                continue;
            }

            // Finalizing the move if no transition triggered
            px = nx;
            py = ny;
        }
    }

    system("cls");
    if (pc.hasWon) {
        cout << "==========================================" << endl;
        cout << "               YOU WIN!                   " << endl;
        cout << "==========================================" << endl;
        cout << " James Taylor's Mansion Quest Complete.   " << endl;
    } else {
        cout << "Ending session. Goodbye, Traveler." << endl;
    }

    return 0;
}
