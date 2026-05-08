/**
 * @file Trial_Minigame.cpp
 * @author James Taylor
 * @brief THE OOZING CROWN: Alchemical Roulette.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include "shared_data.h"

using namespace std;

class AlchemicalRoulette {
    int pHP, bossHP; vector<int> vessel; mt19937 rng; Character& pc;
public:
    AlchemicalRoulette(Character& player) : rng(time(0)), pc(player) { bossHP=120; pHP=pc.hp; }

    void reload() {
        int e = rand()%2+2, s = 6-e; vessel.clear();
        for(int i=0; i<e; i++) vessel.push_back(1);
        for(int i=0; i<s; i++) vessel.push_back(0);
        shuffle(vessel.begin(), vessel.end(), rng);
        cout << "\n[VESSEL LOADED] Essences (Live): " << e << " | Scraps (Blank): " << s << endl;
    }

    void start() {
        system("color 0A");
        while(bossHP > 0 && pHP > 0) {
            reload();
            size_t i = 0;
            while(i < vessel.size() && bossHP > 0 && pHP > 0) {
                system("cls");
                cout << "--- THE ALCHEMICAL ROULETTE ---\nBOSS: " << bossHP << " | " << pc.name << ": " << pHP << endl;
                cout << "1. Strike Boss  2. Strike Self\nChoice: ";
                int choice; cin >> choice;
                if(choice == 1) { if(vessel[i]) bossHP-=30; i++; }
                else { if(vessel[i]) pHP-=30; else { cout << "EXTRA TURN!"; system("pause"); i++; continue; } i++; }

                if(i < vessel.size() && bossHP > 0 && pHP > 0) {
                    cout << "\nBoss actions its turn...";
                    if(vessel[i]) pHP-=30;
                    i++;
                }
                system("pause");
            }
        }
        if(bossHP <= 0) { cout << "VICTORY! The Slime Key is yours."; pc.inventory.push_back("Slime Key"); }
        saveCitizen(pc);
    }
};

int main(int argc, char* argv[]) {
    Character pc; if(argc<3||!loadCitizen(pc, argv[1], argv[2])) return 1;
    AlchemicalRoulette game(pc); game.start(); return 0;
}
