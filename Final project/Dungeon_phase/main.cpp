/**
 * @file Dungeon_phase.cpp
 * @brief 3-Floor gauntlet. Features Interactive Chests, Mimics, and Milestones.
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
    {{0,0,0,0,0,0,0,0,0,0},{0,2,1,1,0,4,1,1,5,0},{0,0,0,1,0,0,0,0,1,0},{0,4,1,1,1,1,1,0,1,0},{0,1,0,0,0,0,1,0,1,0},{0,1,0,4,1,1,1,0,1,0},{0,1,0,0,0,0,0,0,1,0},{0,1,1,1,1,6,1,1,3,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}},
    {{0,0,0,0,0,0,0,0,0,0},{0,2,1,1,0,1,1,1,4,0},{0,0,0,1,0,1,0,0,0,0},{0,1,1,1,1,1,1,1,1,0},{0,1,0,0,0,0,0,0,1,0},{0,1,1,1,7,1,1,1,1,0},{0,0,0,0,0,0,0,0,1,0},{0,4,1,1,1,1,1,1,3,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}},
    {{0,0,0,0,0,0,0,0,0,0},{0,2,1,1,0,4,1,1,1,0},{0,0,0,1,0,1,0,0,1,0},{0,1,1,1,1,1,1,1,1,0},{0,1,0,0,0,0,0,0,1,0},{0,1,1,1,1,8,1,1,1,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}}
};

int getMod(int stat) { return (stat >= 10) ? (stat - 10) / 2 : (stat - 11) / 2; }

string runChest(Character& pc) {
    system("cls"); cout << "--- THE HEAVY CHEST ---\nIt is locked tight. How will you open it?\n1. [DEX] Pick the lock carefully.\n2. [STR] Smash the lid off.\nChoice: ";
    if(rand()%100 < 10){ pc.hp-=7; return "IT'S A MIMIC! The chest grows teeth and bites you! -7 HP."; }
    int c; cin >> c;
    if(c==1){
        int r=rand()%20+1+getMod(pc.baseStats[1]);
        if(find(pc.inventory.begin(), pc.inventory.end(), "Thieves' Tools") != pc.inventory.end()) r+=5;
        if(r>=13){ int g=rand()%30+50; pc.gold+=g; return "SUCCESS! You picked the lock and found " + to_string(g) + " gold!"; }
        else return "FAILURE! The pick snapped in the lock.";
    }
    else if(c==2){
        int r=rand()%20+1+getMod(pc.baseStats[0]);
        if(r>=10){ int g=rand()%15+15; pc.gold+=g; return "SMASH! You broke the gold inside, but recovered " + to_string(g) + " coins."; }
        else { pc.hp-=2; return "FAILURE! You hit the chest so hard you hurt your wrist. -2 HP."; }
    }
    return "You step away.";
}

int main(int argc, char* argv[]) {
    srand(time(0)); Character pc; if (argc < 3 || !loadCitizen(pc, argv[1], argv[2])) return 1;
    currentFloor = pc.lastRoom; int px=1, py=1; string act = "Damp stone walls glow green...";
    while(true) {
        system("cls");
        cout << "========================================================\n LOCATION: THE OUBLIETTE - FLOOR " << currentFloor+1 << "\n";
        cout << " HP: " << pc.hp << "/" << pc.maxHp << " | GOLD: " << pc.gold << "gp\n========================================================\n";
        for(int i=0; i<10; i++){ cout<<"               "; for(int j=0; j<10; j++){ if(i==py&&j==px)cout<<"[P]"; else { int t=dungeonGrid[currentFloor][i][j]; switch(t){case 0:cout<<"###";break;case 1:cout<<" . ";break;case 2:cout<<"[^]";break;case 3:cout<<"[v]";break;case 4:cout<<" $ ";break;case 5:cout<<"[?]";break;case 6:cout<<"[K]";break;case 7:cout<<"[M]";break;case 8:cout<<"[B]";break;}} } cout<<endl; }
        cout<<"--------------------------------------------------------\n ACTIONS: [ESC] Retreat to Town | >> ACTION: "<<act<<"\n";
        int ch = _getch(); if(ch==27) break;
        int nx=px, ny=py; if(ch==0||ch==224){ switch(_getch()){case KEY_UP:ny--;break;case KEY_DOWN:ny++;break;case KEY_LEFT:nx--;break;case KEY_RIGHT:nx++;break;} }
        if(nx<0||nx>9||ny<0||ny>9||dungeonGrid[currentFloor][ny][nx]==0) continue;
        int t = dungeonGrid[currentFloor][ny][nx];
        if(t==4){ act=runChest(pc); dungeonGrid[currentFloor][ny][nx]=1; }
        else if(t==6){ if(find(pc.inventory.begin(), pc.inventory.end(), "Rusty Key") != pc.inventory.end()){ dungeonGrid[currentFloor][ny][nx]=1; act="You unlock the iron gate."; } else act = "The gate is locked. Find a key."; }
        else if(t==7){ if(rand()%20+1+getMod(pc.baseStats[0])>=12){ dungeonGrid[currentFloor][ny][nx]=1; if(pc.level==2)pc.milestoneReached=true; act="Mini-Boss Slime Crushed!"; } else { act="The Slime bashes you! -10 HP"; pc.hp-=10; } }
        else if(t==8){ saveCitizen(pc); system(("start /WAIT \"\" \"Trial_Minigame.exe\" \""+pc.playerName+"\" \""+pc.name+"\"").c_str()); break; }
        else { px=nx; py=ny; if(t==5){pc.inventory.push_back("Rusty Key"); dungeonGrid[currentFloor][ny][nx]=1; act="You found the Rusty Key!";} else if(t==3){currentFloor++; pc.lastRoom=currentFloor; px=1; py=1; if(pc.level==1)pc.milestoneReached=true; act = "You descended a floor.";} else if(t==2){if(currentFloor>0){currentFloor--;px=8;py=7; act = "You climbed up a floor.";} else break;} }
        if(pc.hp <= 0) break;
    }
    saveCitizen(pc); system(("start \"\" \"RPG_System.exe\" \""+pc.playerName+"\" \""+pc.name+"\"").c_str()); return 0;
}
