/**
 * @file Class_Gen.cpp
 * @author James Taylor
 * @brief THE OOZING CROWN: Creation and Shop Suite.
 */

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include "shared_data.h"

using namespace std;

int getMod(int stat) { return (stat >= 10) ? (stat - 10) / 2 : (stat - 11) / 2; }

void showScribe(Character& pc) {
    while (true) {
        system("cls");
        cout << "\n[ THE SCRIBE'S ARCHIVE ]" << endl;
        cout << "1. Ask: 'What happened to the King?'\n2. Rite of Passage (Level Up)\n3. Leave\nChoice: ";
        int ch; cin >> ch;
        if (ch == 1) cout << "\n'He shed the bone-prison of his humanity to become Unity. You follow in his steps.'\n";
        else if (ch == 2) {
            if (pc.milestoneReached) {
                pc.level++; pc.milestoneReached = false;
                int hitDie = (pc.charClass == "Fighter") ? 10 : (pc.charClass == "Wizard" ? 6 : 8);
                int gain = (rand() % hitDie) + 1 + getMod(pc.baseStats[2]);
                pc.maxHp += max(1, gain); pc.hp = pc.maxHp;
                cout << "\n--- THE RITE IS COMPLETE ---\nYou reached Level " << pc.level << "!\n";
            } else cout << "\n'You have not yet discovered any truths worth archiving.'\n";
        }
        else if (ch == 3) break;
        system("pause");
    }
}

void showBlacksmith(Character& pc) {
    while (true) {
        system("cls");
        cout << "\n[ THE IRON ANVIL ]\n1. Steel Blade (150gp)\n2. Plate Polish (200gp)\n3. Leave\nChoice: ";
        int ch; cin >> ch;
        if (ch == 1 && pc.gold >= 150) { pc.gold -= 150; pc.inventory.push_back("Steel Blade"); }
        else if (ch == 2 && pc.gold >= 200) { pc.gold -= 200; pc.ac += 2; }
        else if (ch == 3) break;
        system("pause");
    }
}

int rollStat(int &bonus) {
    int r[4], low = 6, sum = 0, counts[7] = {0};
    for(int i=0; i<4; i++){ r[i]=(rand()%6)+1; counts[r[i]]++; if(r[i]<low) low=r[i]; sum+=r[i]; }
    sum -= low;
    for(int i=1; i<=6; i++) if(counts[i]>=3) bonus++;
    return sum;
}

int main(int argc, char* argv[]) {
    srand(time(0)); Character pc;
    if (argc >= 4) {
        if (loadCitizen(pc, argv[1], argv[2])) {
            string mode = argv[3];
            if (mode == "BLACKSMITH") showBlacksmith(pc);
            else if (mode == "SCRIBE") showScribe(pc);
            saveCitizen(pc);
        } return 0;
    }
    system("cls"); cout << "\n[ NATION REGISTRATION ]\nNation: ";
    if (argc < 2) getline(cin >> ws, pc.playerName); else pc.playerName = argv[1];
    cout << "Name: "; getline(cin >> ws, pc.name);
    cout << "Race (1.Human 2.Elf 3.Dwarf 4.Halfling): "; int r; cin >> r;
    pc.race = (vector<string>{"Human", "Elf", "Dwarf", "Halfling"})[max(0,min(3,r-1))];
    cout << "Class (1.Fighter 2.Rogue 3.Wizard 4.Cleric): "; int c; cin >> c;
    pc.charClass = (vector<string>{"Fighter", "Rogue", "Wizard", "Cleric"})[max(0,min(3,c-1))];
    int bonus = 0, raw[6]; for(int i=0; i<6; i++) raw[i] = rollStat(bonus);
    sort(raw, raw+6, greater<int>());
    for(int i=0; i<6; i++) pc.baseStats[i] = raw[i];
    pc.hp = pc.maxHp; pc.gold = 100;
    saveCitizen(pc); return 0;
}
