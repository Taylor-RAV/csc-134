/**
 * @file Class_Gen.cpp
 * @brief Character Creation and Shop logic. Features full 4d6 rolling flavor and "Ascension" lore.
 */

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <functional>
#include <iomanip>
#include "shared_data.h"

using namespace std;

int getMod(int stat) { return (stat >= 10) ? (stat - 10) / 2 : (stat - 11) / 2; }

/**
 * @brief Prints the "Official Registry Document" character sheet.
 */
void printSheet(const Character& pc) {
    system("cls");
    string stats[6] = {"STR", "DEX", "CON", "INT", "WIS", "CHA"};
    cout << "========================================================" << endl;
    cout << "              OFFICIAL REGISTRY DOCUMENT                " << endl;
    cout << "========================================================" << endl;
    cout << " Name:  " << pc.name << " of " << pc.playerName << endl;
    cout << " Race:  " << pc.race << "      Class: " << pc.charClass << endl;
    cout << " Level: " << pc.level << "          Gold:  " << pc.gold << "gp" << endl;
    cout << " HP:    " << pc.hp << "/" << pc.maxHp << "      AC:    " << pc.ac << endl;
    cout << "--------------------------------------------------------" << endl;
    for(int i=0; i<6; i++) {
        int mod = getMod(pc.baseStats[i]);
        cout << " " << stats[i] << ": " << setw(2) << pc.baseStats[i]
             << " (" << (mod >= 0 ? "+" : "") << mod << ")" << endl;
    }
    cout << "--------------------------------------------------------" << endl;
    cout << " INVENTORY: ";
    if(pc.inventory.empty()) cout << "[Empty]";
    else for(auto& i : pc.inventory) cout << "[" << i << "] ";
    cout << "\n========================================================" << endl;
    system("pause");
}

void showScribe(Character& pc) {
    while (true) {
        system("cls");
        cout << "\n[ THE SCRIBE'S ARCHIVE ]" << endl;
        cout << "1. Ask: 'What happened to the King?'" << endl;
        cout << "2. Ask: 'Tell me about the Five Volumes.'" << endl;
        cout << "3. Rite of Passage (Level Assessment)" << endl;
        cout << "4. Leave" << endl;
        cout << "Choice: ";
        int ch; cin >> ch;
        if (ch == 1) cout << "\nScribe: 'The town thinks he died of rot. They are wrong. He didn't want to die;\nhe wanted to shed his \"rigid bone prison\" and become fluid... become Unity.'" << endl;
        else if (ch == 2) cout << "\nScribe: 'The books contain the stages of his change. S-L-I-M-E.\nThe word itself is the password to his deepest, greenest secrets.'" << endl;
        else if (ch == 3) {
            if (pc.milestoneReached) {
                pc.level++; pc.milestoneReached = false;
                int die = (pc.charClass == "Fighter") ? 10 : (pc.charClass == "Wizard" ? 6 : 8);
                int gain = (rand() % die) + 1 + getMod(pc.baseStats[2]);
                pc.maxHp += max(1, gain); pc.hp = pc.maxHp;
                cout << "\n--- THE RITE IS COMPLETE ---\nYou reached Level " << pc.level << "! Choose a new Talent:\n";
                vector<string> t;
                if(pc.charClass=="Fighter") t={"Second Wind", "Shield Wall"};
                else if(pc.charClass=="Wizard") t={"Magic Missile", "Mage Armor"};
                else if(pc.charClass=="Rogue") t={"Sneak Attack", "Vanish"};
                else t={"Cure Wounds", "Holy Smite"};
                for(int i=0; i<2; i++) cout << i+1 << ". " << t[i] << endl;
                int p; cin >> p; pc.inventory.push_back(t[max(0,min(1,p-1))]);
                printSheet(pc);
            } else cout << "\nScribe: 'You have not yet discovered any forbidden truths.'" << endl;
        }
        else if (ch == 4) break;
        system("pause");
    }
}

void showBlacksmith(Character& pc) {
    while (true) {
        system("cls");
        cout << "\n[ THE IRON ANVIL ]" << endl;
        cout << "1. Ask: 'Did the King order weapons?'" << endl;
        cout << "2. Steel Blade (150gp) [+5 Power]" << endl;
        cout << "3. Plate Polish (200gp) [+2 AC]" << endl;
        cout << "4. Leave" << endl;
        int ch; cin >> ch;
        if (ch == 1) cout << "\nBlacksmith: 'No weapons. But he had me forge a massive iron box.\nHe wasn't keeping something OUT. He was keeping something IN.'" << endl;
        else if (ch == 2 && pc.gold >= 150) { pc.gold -= 150; pc.inventory.push_back("Steel Blade"); }
        else if (ch == 3 && pc.gold >= 200) { pc.gold -= 200; pc.ac += 2; }
        else if (ch == 4) break;
        system("pause");
    }
}

void showApothecary(Character& pc) {
    while (true) {
        system("cls");
        cout << "\n[ THE BUBBLING CAULDRON ]" << endl;
        cout << "1. Ask: 'Is there a cure for the green rot?'" << endl;
        cout << "2. Caustic Solvent (50gp) [+10 Power]" << endl;
        cout << "3. Health Potion (50gp)" << endl;
        cout << "4. Leave" << endl;
        int ch; cin >> ch;
        if (ch == 1) cout << "\nApothecary: 'The rot is a catalyst. He was using solvents to peel off his skin!'" << endl;
        else if (ch == 2 && pc.gold >= 50) { pc.gold -= 50; pc.inventory.push_back("Caustic Solvent"); }
        else if (ch == 3 && pc.gold >= 50) { pc.gold -= 50; pc.inventory.push_back("Health Potion"); }
        else if (ch == 4) break;
        system("pause");
    }
}

int rollStat(int &bonus) {
    int r[4], low = 6, sum = 0, counts[7] = {0};
    cout << "  Rolling 4d6: [ ";
    for(int i=0; i<4; i++){ r[i]=(rand()%6)+1; cout << r[i] << " "; counts[r[i]]++; if(r[i]<low) low=r[i]; sum+=r[i]; }
    sum -= low; cout << "] -> Dropped " << low << " | Score: " << sum;
    if(counts[6]==4) { bonus+=2; cout << " <FOUR 6s! +2 Bonus>"; }
    else for(int i=1; i<=6; i++) if(counts[i]>=3){ bonus++; cout << " <TRIPLE " << i << "s! +1 Bonus>"; break; }
    cout << endl; return sum;
}

int main(int argc, char* argv[]) {
    srand(time(0)); Character pc;
    if (argc >= 4) {
        if (loadCitizen(pc, argv[1], argv[2])) {
            string m = argv[3];
            if (m == "BLACKSMITH") showBlacksmith(pc);
            else if (m == "APOTHECARY") showApothecary(pc);
            else if (m == "SCRIBE") showScribe(pc);
            saveCitizen(pc);
        } return 0;
    }
    system("cls");
    cout << "\n[ NATION REGISTRATION ]\nNation Name: ";
    if (argc < 2) getline(cin >> ws, pc.playerName); else pc.playerName = argv[1];
    cout << "Character Name: "; getline(cin >> ws, pc.name);
    cout << "Race (1.Human 2.Elf 3.Dwarf 4.Halfling): "; int r; cin >> r;
    pc.race = (vector<string>{"Human", "Elf", "Dwarf", "Halfling"})[max(0,min(3,r-1))];
    cout << "Class (1.Fighter 2.Rogue 3.Wizard 4.Cleric): "; int c; cin >> c;
    pc.charClass = (vector<string>{"Fighter", "Rogue", "Wizard", "Cleric"})[max(0,min(3,c-1))];

    cout << "\n--- DIVINING YOUR ATTRIBUTES ---" << endl;
    int bonus = 0, raw[6]; for(int i=0; i<6; i++) raw[i] = rollStat(bonus);
    sort(raw, raw+6, greater<int>());
    int f[]={0,2,1,4,5,3}, ro[]={1,2,3,4,5,0}, w[]={3,2,1,4,5,0}, cl[]={4,2,0,1,5,3}, *p;
    if(pc.charClass=="Fighter") p=f; else if(pc.charClass=="Rogue") p=ro; else if(pc.charClass=="Wizard") p=w; else p=cl;
    for(int i=0; i<6; i++) pc.baseStats[p[i]] = raw[i];

    while(bonus > 0){ cout << "\nYou have " << bonus << " bonus point(s). Assign to (1.STR-6.CHA): "; int s; cin >> s; if(s>=1&&s<=6){pc.baseStats[s-1]++; bonus--;} }
    int con=getMod(pc.baseStats[2]), dex=getMod(pc.baseStats[1]);
    if(pc.charClass=="Fighter"){ pc.maxHp=(10+con)*4; pc.ac=18; pc.inventory={"Chainmail","Longsword"}; }
    else if(pc.charClass=="Rogue"){ pc.maxHp=(8+con)*4; pc.ac=11+dex; pc.inventory={"Leather","Twin Daggers","Thieves' Tools"}; }
    else if(pc.charClass=="Wizard"){ pc.maxHp=(6+con)*4; pc.ac=10+dex; pc.inventory={"Spellbook"}; }
    else { pc.maxHp=(8+con)*4; pc.ac=15; pc.inventory={"Chain Shirt","Mace"}; }
    pc.hp = pc.maxHp; pc.gold = 100;
    printSheet(pc); saveCitizen(pc); return 0;
}
