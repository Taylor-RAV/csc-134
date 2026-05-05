#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <filesystem>
#include "shared_data.h"

namespace fs = std::filesystem;
using namespace std;

enum Room { ENTRANCE, ANTECHAMBER, HALLWAY, OFFERING_ROOM, HIDDEN_CRYPT, W_HALL_1, NUM_ROOMS };
struct DungeonRoom { string name, desc; int exits[4]; string item; int gold; bool looted; };

int getMod(int v) { return (v - 10) / 2; }
bool has(Character &c, string i) { return find(c.inventory.begin(), c.inventory.end(), i) != c.inventory.end(); }

int main(int argc, char* argv[]) {
    srand(time(0));
    //fs::current_path(fs::path(argv[0]).parent_path());
    Character pc;
    if (argc < 3 || !loadCitizen(pc, argv[1], argv[2])) return 1;

    DungeonRoom d[NUM_ROOMS] = {
        {"Entrance", "Stone steps.", {1,-1,-1,-1}, "", 0, 1},
        {"Antechamber", "Cold.", {-1,-1,0,2}, "Dagger", 15, 0},
        {"Hallway", "Trapped.", {3,1,-1,-1}, "", 0, 1},
        {"Offering Room", "Shrine.", {4,-1,2,-1}, "Delian Sword", 50, 0},
        {"Hidden Crypt", "Altar.", {-1,-1,3,-1}, "", 200, 0},
        {"Secret Vault", "Filled with Gold.", {-1,0,-1,-1}, "Emerald", 500, 0}
    };

    int cur = pc.lastRoom;
    bool bossDefeated = false;

    while(pc.hp > 0) {
        pc.lastRoom = cur;
        saveCitizen(pc);

        if(has(pc, "Delian Sword")) d[0].exits[3] = 5; // Reveal Vault

        cout << "\nLOC: " << d[cur].name << "\n(n,e,s,w | loot | q) > ";
        string cmd; cin >> cmd;

        if(cmd == "q") {
            system(("start \"\" \".\\RPG_System.exe\" \"" + pc.playerName + "\" \"" + pc.name + "\"").c_str());
            return 0;
        }

        if(cmd == "loot" && !d[cur].looted) {
            pc.gold += d[cur].gold; d[cur].looted = true;
            if(!d[cur].item.empty()) pc.inventory.push_back(d[cur].item);
            cout << "Looted " << d[cur].gold << "gp and items!" << endl;
        }

        int dr = (cmd=="n"?0:cmd=="e"?1:cmd=="s"?2:cmd=="w"?3:-1);
        if(dr != -1 && d[cur].exits[dr] != -1) cur = d[cur].exits[dr];
    }
    return 0;
}
