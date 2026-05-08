/**
 * @file Mansion_phase.cpp
 * @author James Taylor
 * @brief THE OOZING CROWN: Investigative Exploration.
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

int currentMapID = 0;

int mansionMaps[6][7][7] = {
    {{0,0,0,6,0,0,0}, {0,8,1,1,1,8,0}, {11,1,0,1,0,1,13}, {0,17,0,1,17,1,0}, {12,1,0,9,0,1,14}, {0,1,1,1,1,1,0}, {0,0,0,0,0,0,0}},
    {{0,0,0,0,0,0,0}, {0,18,1,1,1,1,0}, {0,1,1,1,1,15,1}, {0,1,0,0,0,1,0}, {0,1,1,1,1,1,0}, {0,1,1,1,1,1,0}, {0,0,0,0,0,6,0}},
    {{0,0,0,0,0,0,0}, {0,20,1,1,1,1,0}, {0,1,1,0,1,1,0}, {0,1,1,1,1,1,0}, {0,1,1,0,1,1,0}, {15,1,1,1,1,1,0}, {6,1,0,0,0,1,0}},
    {{0,0,0,0,0,0,0}, {0,17,1,1,1,1,0}, {0,19,0,0,0,1,0}, {0,19,1,1,1,1,0}, {0,1,0,0,0,1,0}, {0,1,1,1,1,1,0}, {0,6,0,0,0,1,0}},
    {{0,0,0,0,0,0,0}, {0,7,1,0,1,1,0}, {0,1,1,0,18,1,0}, {0,1,1,1,1,1,0}, {0,0,0,6,0,0,0}, {0,1,1,1,1,1,0}, {0,1,0,0,0,1,0}},
    {{0,0,0,0,0,0,0}, {0,8,8,10,8,8,0}, {0,8,1,1,1,8,0}, {0,8,1,17,1,8,0}, {0,8,1,1,1,8,0}, {0,8,8,8,8,8,0}, {0,0,0,6,0,0,0}}
};

void drawMansion(int px, int py, const Character& pc) {
    system("cls");
    string names[] = {"MAIN HALL", "KITCHEN", "THE STUDY", "THE LIBRARY", "THE BEDCHAMBER", "THE CELLAR"};
    cout << " LOCATION: " << names[currentMapID] << " | HP: " << pc.hp << "/" << pc.maxHp << endl;
    for(int i=0; i<7; i++) {
        cout << "               ";
        for(int j=0; j<7; j++) {
            int t = mansionMaps[currentMapID][i][j];
            if(i==py && j==px) cout << "[@]";
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
                    case 17: cout << "[P]"; break;
                    case 18: cout << "[A]"; break;
                    case 19: cout << "[B]"; break;
                    case 20: cout << "[C]"; break;
                    default: cout << "   "; break;
                }
            }
        } cout << endl;
    }
}

void runEncounter(Character& pc, int rID, int tID) {
    system("cls"); cout << "--- INVESTIGATION ---\n";
    if (tID == 17) {
        if (rID == 0) cout << "The Royal Family Portrait. The King's face is scratched out with green ooze.";
        else if (rID == 3) cout << "Landscape of the Vale. The mountains look like they are melting.";
        else if (rID == 5) cout << "The Shadow of the Successor. The eyes seem to track your steps.";
        else cout << "A moldy oil painting.";
    }
    else if (tID == 20) {
        if (!pc.rackMoved) cout << "The console is dark.";
        else { cout << "Cipher: "; string s; cin >> s; transform(s.begin(), s.end(), s.begin(), ::toupper);
               if(s=="SLIME") { pc.inDungeon = true; pc.milestoneReached = true; cout << "Gate raised!"; } }
    }
    else if (tID == 10) {
        if (pc.inDungeon) { saveCitizen(pc); system(("start \"\" \"Dungeon_phase.exe\" \"" + pc.playerName + "\" \"" + pc.name + "\"").c_str()); exit(0); }
    }
    system("pause");
}

int main(int argc, char* argv[]) {
    srand(time(0)); Character pc; if (argc < 3 || !loadCitizen(pc, argv[1], argv[2])) return 1;
    int px = 3, py = 1;
    while(true) {
        drawMansion(px, py, pc);
        int ch = _getch(); if(tolower(ch) == 's') runEncounter(pc, currentMapID, mansionMaps[currentMapID][py][px]);
        int nx=px, ny=py;
        if(ch == 0 || ch == 224) { switch(_getch()){case KEY_UP:ny--;break;case KEY_DOWN:ny++;break;case KEY_LEFT:nx--;break;case KEY_RIGHT:nx++;break;} }
        if(nx < 0 || nx > 6 || ny < 0 || ny > 6) continue;
        int next = mansionMaps[currentMapID][ny][nx];
        if (next == 0 || next == 8) continue;
        if (next == 6) {
            if (currentMapID == 0) break;
            else {
                int p = currentMapID; currentMapID = 0;
                if(p == 1) { px = 1; py = 2; } else if(p == 2) { px = 1; py = 4; } else if(p == 4) { px = 5; py = 2; } else if(p == 3) { px = 5; py = 4; } else if(p == 5) { px = 3; py = 5; }
                continue;
            }
        }
        if(currentMapID == 0) { if(next == 11) { currentMapID = 1; px = 5; py = 5; continue; } if(next == 12) { currentMapID = 2; px = 1; py = 5; continue; } if(next == 13) { currentMapID = 4; px = 3; py = 3; continue; } if(next == 14) { currentMapID = 3; px = 1; py = 5; continue; } }
        px = nx; py = ny;
    }
    saveCitizen(pc); system(("start \"\" \"Hub_Main.exe\" \"" + pc.playerName + "\" \"" + pc.name + "\"").c_str());
    return 0;
}
