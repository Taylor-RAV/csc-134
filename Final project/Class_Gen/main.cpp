#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <filesystem>
#include "shared_data.h"

namespace fs = std::filesystem;
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));

    // FIX: Removed the fs::current_path line that causes the crash/termination

    string country = (argc >= 2) ? argv[1] : "The Iron Crown";
    Character pc;
    pc.playerName = country;

    // SHOP MODE - Fixed argv check
    if (argc >= 4 && string(argv[3]) == "SHOP") {
        if(loadCitizen(pc, argv[1], argv[2])) {
            cout << "\n[ MARKETPLACE ]\n1. Buy Potion (50gp) | 2. Exit\nChoice: ";
            int sh; cin >> sh;
            if(sh == 1 && pc.gold >= 50) {
                pc.gold -= 50;
                pc.inventory.push_back("Health Potion");
                cout << "Scribe: 'A wise purchase!'" << endl;
            }
            saveCitizen(pc);
        }
        return 0;
    }

    // THEME: THE SCRIBE
    cout << "\n[ REGISTRATION TENT ]" << endl;
    cout << "Scribe: 'State your name for the records.'" << endl;
    cout << "Name: "; cin >> pc.name;

    cout << "Race (1.Human 2.Elf 3.Dwarf): ";
    int rCh; cin >> rCh;
    pc.race = (rCh == 2 ? "Elf" : rCh == 3 ? "Dwarf" : "Human");

    cout << "Class (1.Fighter 2.Rogue 3.Wizard): ";
    int cCh; cin >> cCh;
    string cl[] = {"Fighter", "Rogue", "Wizard"};
    pc.charClass = cl[cCh-1];

    // THEME: ROLLING STATS
    cout << "\nScribe: 'I shall use the *Quill of Destiny* to improve your stats.'" << endl;
    for(int i=0; i<6; i++) {
        pc.baseStats[i] = (rand()%6 + rand()%6 + rand()%6 + 3);
    }

    pc.hp = 40;
    pc.ac = 12;
    pc.gold = 100;
    pc.inDungeon = false; // Initialize to false for new players
    pc.lastRoom = 0;

    saveCitizen(pc);
    cout << "\nScribe: 'Record complete. You are ready! " << pc.name << " of " << pc.playerName << ".'" << endl;

    // Safety pause so you can see the message
    cout << "[ Press Enter to return to Town ]";
    cin.ignore(1000, '\n');
    cin.get();

    return 0;
}
