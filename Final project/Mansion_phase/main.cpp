#include <iostream>
#include <string>
#include <algorithm>
#include <filesystem>
#include "shared_data.h"

namespace fs = std::filesystem;
using namespace std;

enum Room { ENTRANCE, LIBRARY, STUDY, KITCHEN, CELLAR, NUM_ROOMS };
struct MansionRoom { string name, desc; int exits[4]; string item; };

bool has(Character &c, string i) { return find(c.inventory.begin(), c.inventory.end(), i) != c.inventory.end(); }

int main(int argc, char* argv[]) {
    // Portability Fix
    //fs::current_path(fs::path(argv[0]).parent_path());

    Character pc;
    if (argc < 3 || !loadCitizen(pc, argv[1], argv[2])) return 1;

    MansionRoom m[NUM_ROOMS] = {
        {"Foyer", "A grand entrance. There is an empty sword stand here.", {KITCHEN,-1,-1,-1}, ""},
        {"Library", "Walls of books. A map is on the table.", {-1,STUDY,ENTRANCE,-1}, "Dungeon Map"},
        {"Study", "A quiet room with a silver key on the desk.", {-1,-1,-1,LIBRARY}, "Library Key"},
        {"Kitchen", "Smells of old bread. A hatch leads to the Cellar.", {-1,-1,ENTRANCE,CELLAR}, ""},
        {"Cellar", "The stone stairs lead deep underground.", {-1,KITCHEN,-1,-1}, ""}
    };

    int cur = ENTRANCE;
    cout << "\n--- THE ABANDONED MANSION ---" << endl;

    while(true) {
        if(has(pc, "Library Key")) m[ENTRANCE].exits[1] = LIBRARY; // Lock & Key check
        saveCitizen(pc);

        cout << "\n[" << m[cur].name << "]\n" << m[cur].desc << endl;
        if(!m[cur].item.empty()) cout << "Item here: " << m[cur].item << endl;
        cout << "(n,e,s,w | take | q) > ";
        string cmd; cin >> cmd;

        if(cmd == "q") {
            if(cur == CELLAR && has(pc, "Dungeon Map")) {
                pc.inDungeon = true;
                saveCitizen(pc);
                cout << "You descend into the darkness..." << endl;
            }
            system(("start \"\" \".\\RPG_System.exe\" \"" + pc.playerName + "\" \"" + pc.name + "\"").c_str());
            return 0;
        }

        if(cmd == "take") {
            if(!m[cur].item.empty()) {
                pc.inventory.push_back(m[cur].item);
                cout << "Picked up " << m[cur].item << "!" << endl;
                m[cur].item = "";
            } else if (cur == ENTRANCE && has(pc, "Delian Sword")) {
                cout << "\n[!] You place the Delian Sword on the stand. A secret passage opens!" << endl;
                cout << "Enter the Trial? (y/n): ";
                char tri; cin >> tri;
                if(tolower(tri) == 'y') {
                    saveCitizen(pc);
                    system(("start /WAIT \"\" \".\\Trial_Minigame.exe\" \"" + pc.playerName + "\" \"" + pc.name + "\"").c_str());
                    loadCitizen(pc, pc.playerName, pc.name);
                }
            } else cout << "Nothing here to take." << endl;
        }

        int dr = (cmd=="n"?0:cmd=="e"?1:cmd=="s"?2:cmd=="w"?3:-1);
        if(dr != -1) {
            if(m[cur].exits[dr] != -1) cur = m[cur].exits[dr];
            else cout << "[Locked] You need a key or map." << endl;
        }
    }
}
