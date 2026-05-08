/**
 * @file Dungeon_phase.cpp
 * @author James Taylor
 * @brief THE OOZING CROWN: Tactical Crawl.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <conio.h>
#include "shared_data.h"

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int currentFloor = 0;

int dungeonGrid[3][10][10] = {
    {{0,0,0,0,0,0,0,0,0,0},{0,2,1,1,1,4,1,1,5,0},{0,0,0,1,0,0,0,0,1,0},{0,4,1,1,1,1,1,0,1,0},{0,1,0,0,0,0,1,0,1,0},{0,1,0,4,1,1,1,0,1,0},{0,1,0,0,0,0,0,0,1,0},{0,1,1,1,1,6,1,1,3,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}},
    {{0,0,0,0,0,0,0,0,0,0},{0,2,1,1,0,1,1,1,4,0},{0,0,0,1,0,1,0,0,0,0},{0,1,1,1,1,1,1,1,1,0},{0,1,0,0,0,0,0,0,1,0},{0,1,1,1,7,1,1,1,1,0},{0,0,0,0,0,0,0,0,1,0},{0,4,1,1,1,1,1,1,3,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}},
    {{0,0,0,0,0,0,0,0,0,0},{0,2,1,1,0,0,0,0,17,0},{0,0,0,1,0,0,0,0,1,0},{0,17,1,1,1,1,1,1,17,0},{0,1,0,0,8,0,0,0,1,0},{0,17,1,1,1,1,1,1,17,0},{0,0,0,0,0,0,0,0,1,0},{0,4,1,1,0,0,0,0,4,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}}
};

void runDungeonEncounter(Character& pc, int tile) {
    system("cls");
    if (tile == 17) {
        cout << "--- INVESTIGATING THE HUSK ---\nA golden husk slumped on the floor, pulsing with wet sound.\nThe King has left this bone-prison behind." << endl;
    }
    else if (tile == 8) {
        cout << "You step onto the ritual platform. The air solidifies..." << endl;
        saveCitizen(pc);
        string cmd = "start /WAIT \"\" \"Trial_Minigame.exe\" \"" + pc.playerName + "\" \"" + pc.name + "\"";
        system(cmd.c_str());
        exit(0);
    }
    system("pause");
}

int main(int argc, char* argv[]) {
    srand(time(0)); Character pc; if (argc < 3 || !loadCitizen(pc, argv[1], argv[2])) return 1;
    currentFloor = pc.lastRoom; int px = 1, py = 1;
    while(true) {
        system("cls");
        cout << "--- OUBLIETTE FLOOR " << currentFloor + 1 << " ---" << endl;
        cout << "[@] = " << pc.name << " | HP: " << pc.hp << "/" << pc.maxHp << endl;
        for(int i=0; i<10; i++) {
            cout << "               ";
            for(int j=0; j<10; j++) {
                if(i==py && j==px) cout << "[@]";
                else {
                    int t = dungeonGrid[currentFloor][i][j];
                    switch(t) {
                        case 0: cout << "###"; break;
                        case 1: cout << " . "; break;
                        case 2: cout << "[^]"; break;
                        case 3: cout << "[v]"; break;
                        case 4: cout << " $ "; break;
                        case 6: cout << "[G]"; break;
                        case 8: cout << "[B]"; break;
                        case 17: cout << "[P]"; break;
                        default: cout << "   "; break;
                    }
                }
            } cout << endl;
        }
        int ch = _getch(); if (tolower(ch) == 's') runDungeonEncounter(pc, dungeonGrid[currentFloor][py][px]);
        int nx=px, ny=py;
        if(ch == 0 || ch == 224) { switch(_getch()){case KEY_UP:ny--;break;case KEY_DOWN:ny++;break;case KEY_LEFT:nx--;break;case KEY_RIGHT:nx++;break;} }
        if (nx < 0 || nx > 9 || ny < 0 || ny > 9 || dungeonGrid[currentFloor][ny][nx] == 0) continue;
        px = nx; py = ny;
        if(dungeonGrid[currentFloor][ny][nx] == 3) { currentFloor++; pc.lastRoom = currentFloor; px=1; py=1; }
    }
}
