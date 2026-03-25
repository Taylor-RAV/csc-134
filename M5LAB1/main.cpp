#include <iostream>
#include <string>

using namespace std;

// Struct to manage player state and inventory persistence
struct Player {
    bool hasRelic = false;     // Found in Great Room (Intention)
    bool hasOldKey = false;    // Found in Dark Hallway (Focus)
    bool doorUnlocked = false; // Set when the Ghost is satisfied
    int health = 100;
};

// Function prototypes to keep code modular and readable
void greatHall(Player &p);
void greatRoom(Player &p);
void darkHallway(Player &p);
void treasureRoom();
void checkInventory(Player &p);

int main() {
    Player user;
    int choice;
    bool exploring = true;

    cout << "====================================\n";
    cout << "   WELCOME TO THE FORSAKEN CASTLE   \n";
    cout << "====================================\n";

    while (exploring) {
        cout << "\n--- Castle Hub ---\n";
        cout << "1. Enter the Great Hall (Ghost)\n";
        cout << "2. Enter the Great Room (Monster)\n";
        cout << "3. Enter the Dark Hallway (Explore)\n";
        cout << "4. Check Inventory (Status)\n";

        // This choice reveals its true nature only once unlocked
        if (user.doorUnlocked) {
            cout << "5. ENTER THE TREASURE ROOM (Win!)\n";
        } else {
            cout << "5. Inspect the Locked Mystery Door\n";
        }

        cout << "6. Run away in fear (Quit)\n";
        cout << "Where do you go? ";
        cin >> choice;

        switch (choice) {
            case 1: greatHall(user); break;
            case 2: greatRoom(user); break;
            case 3: darkHallway(user); break;
            case 4: checkInventory(user); break;
            case 5:
                if (user.doorUnlocked) treasureRoom();
                else cout << "\n[System] The door is sealed by a spectral force.\n";
                break;
            case 6:
                cout << "\nYou flee the castle, leaving its secrets behind.\n";
                exploring = false;
                break;
            default:
                cout << "\nInvalid choice. The darkness looms...\n";
        }
    }
    return 0;
}

// Choice 1: Interaction with the Ghost (The Gatekeeper)
void greatHall(Player &p) {
    cout << "\n--- The Great Hall ---\n";
    cout << "A Ghost floats before a massive stone door.\n";
    cout << "1. Approach the Ghost\n2. Leave for now\nChoice: ";
    int c; cin >> c;

    if (c == 1) {
        // Logic for different inventory combinations
        if (!p.hasRelic && !p.hasOldKey) {
            cout << "Ghost: 'To pass, you must find your focus and clear your intentions.'\n";
        }
        else if (p.hasRelic && !p.hasOldKey) {
            cout << "Ghost: 'I see your Intention (Relic)... but you lack the Focus to turn the lock.'\n";
        }
        else if (!p.hasRelic && p.hasOldKey) {
            cout << "Ghost: 'You have found Focus (Key), yet your Intention is still missing.'\n";
        }
        else if (p.hasRelic && p.hasOldKey) {
            cout << "Ghost: 'Focus and Intention are one. The path is clear.'\n";
            cout << "[System] The Treasure Room door is now UNLOCKED!\n";
            p.doorUnlocked = true;
        }
    }
}

// Choice 2: Monster encounter to gain the "Relic of Intention"
void greatRoom(Player &p) {
    cout << "\n--- The Great Room ---\nA Shadow Beast growls in the corner.\n";
    cout << "1. Fight for the Relic of Intention\n2. Leave the Room\nChoice: ";
    int c; cin >> c;

    if (c == 1) {
        if (!p.hasRelic) {
            cout << "You defeated the beast! You obtained the **Ancient Relic**.\n";
            p.hasRelic = true;
        } else {
            cout << "The beast is gone. The room is quiet.\n";
        }
    }
}

// Choice 3: Exploring the area to gain the "Key to Focus"
void darkHallway(Player &p) {
    cout << "\n--- The Dark Hallways ---\nRows of dusty shelves line the walls.\n";
    cout << "1. Search for the Key to Focus\n2. Leave the Room\nChoice: ";
    int c; cin >> c;

    if (c == 1) {
        if (!p.hasOldKey) {
            cout << "You found the **Old Key** hidden inside a hollow book!\n";
            p.hasOldKey = true;
        } else {
            cout << "The shelves are bare. You've already been here.\n";
        }
    }
}

// Choice 4: A simple status check to track progress
void checkInventory(Player &p) {
    cout << "\n--- Inventory Status ---\n";
    cout << "Relic (Intention): " << (p.hasRelic ? "FOUND" : "MISSING") << "\n";
    cout << "Key (Focus):       " << (p.hasOldKey ? "FOUND" : "MISSING") << "\n";
    cout << "Current Health:    " << p.health << "\n";
}

// Choice 5: Terminal win condition
void treasureRoom() {
    cout << "\n************************************\n";
    cout << "   YOU STEP INTO THE TREASURE ROOM!  \n";
    cout << "   Gold and jewels pile to the ceiling. \n";
    cout << "   YOU HAVE CONQUERED THE CASTLE!    \n";
    cout << "************************************\n";
    exit(0);
}

