/**
 * @file Mansion_phase.cpp
 * @author [Your Name]
 * @brief Exploration phase for The Oozing Crown. Features specific door labels and multi-point Study interactions.
 * @date 2026-05-06
 * --- AI USAGE DISCLOSURE ---
 * This file was reviewed by AI to resolve redefinition errors and ensure
 * proper smart-door transition logic between the Hall and sub-rooms.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <conio.h>
#include "shared_data.h"

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

// Map IDs: 0:Hall, 1:Kitchen, 2:Study, 3:Library, 4:Bedroom, 5:Cellar
int currentMapID = 0;

// Tile IDs:
// 0:Wall, 1:Path, 6:Exit/Door, 7:Nightstand(N), 8:Void, 9:Hatch(H), 10:Gate(G)
// 11:Kitchen(K), 12:Study(S), 13:Bedroom(B), 14:Library(L)
// 15:Rack(R), 16:Mount(M), 17:Painting(P), 18:Cabinet(A), 19:Bookshelf(B), 20:Console(C)
int mansionMaps[6][7][7] = {
    // 0: MAIN HALL (K, S, B, L doors labeled)
    {{0,0,0,6,0,0,0},    // [E] Exit to Town
     {0,8,1,1,1,8,0},
     {11,1,0,1,0,1,13},  // [K] Kitchen Door, [B] Bedroom Door
     {0,17,0,1,17,1,0},
     {12,1,0,9,0,1,14},  // [S] Study Door, [L] Library Door
     {0,1,1,1,1,1,0},
     {0,0,0,0,0,0,0}},

    // 1: KITCHEN (15=Pan Rack)
    {{0,0,0,0,0,0,0},
     {0,18,1,1,1,1,0},
     {0,1,1,1,1,15,1},  // [R] Pan Rack
     {0,1,0,0,0,1,0},
     {0,1,1,1,1,1,0},
     {0,1,1,1,1,1,0},
     {0,0,0,0,0,6,0}},   // [6] Door back to Hall

    // 2: THE ASCENSION STUDY (20=Console, 16=Mount, 15=Rack)
    {{0,0,0,0,0,0,0},
     {0,20,1,1,1,1,0},  // [C] Console
     {0,1,1,0,1,16,0},  // [M] Mount
     {0,1,1,1,1,1,0},
     {0,1,1,0,1,1,0},
     {15,1,1,1,1,1,0},  // [R] Ascension Rack
     {6,1,0,0,0,1,0}},   // [6] Door back to Hall

    // 3: THE DUSTY LIBRARY (19=Bookshelf)
    {{0,0,0,0,0,0,0},
     {0,17,1,1,1,1,0},
     {0,19,0,0,0,1,0},  // [B] Bookshelf
     {0,19,1,1,1,1,0},
     {0,1,0,0,0,1,0},
     {0,1,1,1,1,1,0},
     {0,6,0,0,0,1,0}},   // [6] Door back to Hall

    // 4: THE ROYAL BEDCHAMBER (7=Nightstand)
    {{0,0,0,0,0,0,0},
     {0,7,1,0,1,1,0},   // [N] Nightstand
     {0,1,1,0,18,1,0},  // [A] Cabinet
     {0,1,1,1,1,1,0},
     {0,0,0,6,0,0,0},   // [6] Door back to Hall
     {0,1,1,1,1,1,0},
     {0,1,0,0,0,1,0}},

    // 5: THE CELLAR (10=Gate)
    {{0,0,0,0,0,0,0},
     {0,8,8,10,8,8,0},  // [G] Gate
     {0,8,1,1,1,8,0},
     {0,8,1,17,1,8,0},
     {0,8,1,1,1,8,0},
     {0,8,8,8,8,8,0},
     {0,0,0,6,0,0,0}}    // [6] Hatch back up to Hall
};

bool hasItem(const Character& pc, const string& itemName) {
    return find(pc.inventory.begin(), pc.inventory.end(), itemName) != pc.inventory.end();
}

int getModifier(int stat) { return (stat >= 10) ? (stat - 10) / 2 : (stat - 11) / 2; }

void drawMansion(int px, int py, const Character& pc, string action) {
    system("cls");
    string names[] = {"MAIN HALL", "KITCHEN", "THE ASCENSION STUDY", "THE DUSTY LIBRARY", "THE ROYAL BEDCHAMBER", "THE CELLAR"};
    cout << "========================================================" << endl;
    cout << " LOCATION: " << names[currentMapID] << endl;
    if(pc.milestoneReached) cout << " ** RITE OF PASSAGE AWAITS: VISIT THE SCRIBE **" << endl;
    cout << " NAME: " << pc.name << " | HP: " << pc.hp << "/" << pc.maxHp << endl;
    cout << "========================================================" << endl;
    for(int i=0; i<7; i++) {
        cout << "               ";
        for(int j=0; j<7; j++) {
            int t = mansionMaps[currentMapID][i][j];
            if(i==py && j==px) cout << "[P]";
            else {
                switch(t) {
                    case 0: cout << "###"; break;
                    case 1: cout << " . "; break;
                    case 6: cout << (currentMapID == 0 ? "[E]" : "[D]"); break;
                    case 7: cout << "[N]"; break;
                    case 9: cout << "[H]"; break;
                    case 10: cout << (pc.inDungeon ? "[O]" : "[X]"); break;
                    case 11: cout << "[K]"; break;
                    case 12: cout << "[S]"; break;
                    case 13: cout << "[B]"; break;
                    case 14: cout << "[L]"; break;
                    case 15: cout << "[R]"; break;
                    case 16: cout << "[M]"; break;
                    case 17: cout << "[P]"; break;
                    case 18: cout << "[A]"; break;
                    case 19: cout << "[B]"; break;
                    case 20: cout << "[C]"; break;
                    default: cout << "   "; break;
                }
            }
        }
        cout << endl;
    }
    cout << "--------------------------------------------------------" << endl;
    cout << " ACTIONS: [S] Investigate | Move to [D] to return to Hall" << endl;
    cout << " >> ACTION: " << action << endl;
    cout << "--------------------------------------------------------" << endl;
}

void runEncounter(Character& pc, int roomID, int tileID) {
    system("cls");
    cout << "========================================================" << endl;

    // Painting Interactions
    if (tileID == 17) {
        cout << " ENCOUNTER: A Moldy Oil Painting" << endl;
        cout << "The King's face has been smeared with green ooze." << endl;
        if ((rand() % 100) < 40) {
            cout << "You find a few coins tucked behind the frame! (+20gp)" << endl;
            pc.gold += 20;
        } else cout << "The painting is worthless and damp." << endl;
    }
    // Cabinet Interactions
    else if (tileID == 18) {
        cout << " ENCOUNTER: A Wooden Cabinet" << endl;
        cout << "1. [STR] Force it open." << endl;
        int ch; cin >> ch;
        if (ch == 1 && ((rand()%20)+1 + getModifier(pc.baseStats[0])) >= 10) {
            cout << "You pry the doors open and find 30 gold!" << endl;
            pc.gold += 30;
        } else cout << "The wood is swollen shut." << endl;
    }
    // Nightstand Interaction
    else if (tileID == 7) {
        cout << " ENCOUNTER: The Royal Nightstand" << endl;
        if (!hasItem(pc, "Silver Key")) {
            cout << "You find a heavy SILVER KEY inside the top drawer!" << endl;
            pc.inventory.push_back("Silver Key");
        } else cout << "The nightstand is empty." << endl;
    }
    // Library Interaction
    else if (tileID == 19) {
        cout << " ENCOUNTER: The Jumbled Books" << endl;
        if (!hasItem(pc, "Lettered Books")) {
            cout << "You find the volumes bound in green leather (S, L, I, M, E)!" << endl;
            pc.inventory.push_back("Lettered Books");
        } else cout << "The shelves are empty now." << endl;
    }
    // Rack Interaction (Context Sensitive)
    else if (tileID == 15) {
        if (roomID == 1) {
            cout << " ENCOUNTER: The Mechanical Pan Rack" << endl;
            if (pc.rackMoved) cout << "The lever is already engaged." << endl;
            else {
                cout << "1. [STR] Pull the rusted lever." << endl;
                int ch; cin >> ch;
                if (ch == 1 && ((rand()%20)+1 + getModifier(pc.baseStats[0])) >= 12) {
                    cout << "SUCCESS! Power hums through the floorboards to the STUDY." << endl;
                    pc.rackMoved = true;
                } else cout << "It won't budge." << endl;
            }
        } else cout << "ENCOUNTER: The Grafting Rack. Iron hooks used to peel away human flesh.";
    }
    // Console Interaction
    else if (tileID == 20) {
        cout << " ENCOUNTER: The Ascension Console" << endl;
        if (!pc.rackMoved) cout << "The console has no power. Check the KITCHEN." << endl;
        else if (!hasItem(pc, "Lettered Books")) cout << "You need the cipher books from the LIBRARY to proceed." << endl;
        else {
            cout << "The jumbled books sit in the slots. Enter the 5-Letter Cipher: ";
            string s; cin >> s;
            if (s == "SLIME" || s == "slime") {
                cout << "SUCCESS! The Cellar Gate has been raised." << endl;
                pc.inDungeon = true;
            } else { cout << "ERROR: The console sparks! (-2 HP)"; pc.hp -= 2; }
        }
    }
    else if (tileID == 16) cout << "ENCOUNTER: The Alchemical Mount. A slab of obsidian etched with circles.";
    else if (tileID == 9) {
        if (hasItem(pc, "Silver Key")) { cout << "The Hatch opens. You descend..."; currentMapID = 5; }
        else cout << "Locked. You need the Silver Key from the BEDCHAMBER.";
    }
    else if (tileID == 10) {
        if (pc.inDungeon) {
            saveCitizen(pc); system("pause");
            system(("start \"\" \"Dungeon_phase.exe\" \"" + pc.playerName + "\" \"" + pc.name + "\"").c_str());
            exit(0);
        } else cout << "The iron gate is sealed. Solve the puzzle in the STUDY.";
    }

    system("pause");
}

int main(int argc, char* argv[]) {
    srand(time(0)); Character pc;
    if (argc < 3 || !loadCitizen(pc, argv[1], argv[2])) return 1;
    int px = 3, py = 1;
    while(true) {
        drawMansion(px, py, pc, "Green light pulses behind the wallpaper...");
        int ch = _getch();
        if(ch == 27) break;
        int tile = mansionMaps[currentMapID][py][px];
        if(tolower(ch) == 's') { runEncounter(pc, currentMapID, tile); continue; }

        int nx = px, ny = py;
        if(ch == 0 || ch == 224) {
            switch(_getch()) {
                case KEY_UP: ny--; break; case KEY_DOWN: ny++; break;
                case KEY_LEFT: nx--; break; case KEY_RIGHT: nx++; break;
            }
        }
        if(nx < 0 || nx > 6 || ny < 0 || ny > 6) continue;
        int next = mansionMaps[currentMapID][ny][nx];
        if(next == 0 || next == 8) continue;

        // Transition Logic
        if (next == 6) {
            if (currentMapID == 0) break; // Exit Hall to Town
            else { // Return to Hall from sub-rooms
                int prevMap = currentMapID;
                currentMapID = 0;
                if(prevMap == 1) { px = 1; py = 2; }      // From Kitchen back to K door
                else if(prevMap == 2) { px = 1; py = 4; } // From Study back to S door
                else if(prevMap == 4) { px = 5; py = 2; } // From Bedroom back to B door
                else if(prevMap == 3) { px = 5; py = 4; } // From Library back to L door
                else if(prevMap == 5) { px = 3; py = 5; } // From Cellar back to Hatch
                continue;
            }
        }

        if(currentMapID == 0) {
            if(next == 11) { currentMapID = 1; px = 5; py = 6; continue; }
            if(next == 12) { currentMapID = 2; px = 0; py = 6; continue; }
            if(next == 13) { currentMapID = 4; px = 3; py = 4; continue; }
            if(next == 14) { currentMapID = 3; px = 1; py = 6; continue; }
        }
        px = nx; py = ny;
    }
    saveCitizen(pc);
    system(("start \"\" \"Hub_Main.exe\" \"" + pc.playerName + "\" \"" + pc.name + "\"").c_str());
    return 0;
}
