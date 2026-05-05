#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include "shared_data.h"

namespace fs = std::filesystem;
using namespace std;

// --- HUB MAIN ---
int main(int argc, char* argv[]) {
    // Note: Removed the path fix here to prevent the "Blank Screen" bug.

    string countryName = "", citizenName = "";
    Character pc;
    bool countryActive = true;
    bool inTown = true;

    // Handle incoming character data from other projects
    if (argc >= 3) {
        countryName = argv[1];
        citizenName = argv[2];
        if (loadCitizen(pc, countryName, citizenName)) goto townSquare;
    }

    while (true) {
        if (countryName == "") {
            cout << "\n[ GATE OF THE IRON CROWN ]" << endl;
            cout << "An armored guard blocks your path. 'Halt!'" << endl;
            cout << "Guard: 'Do you hail from a recognized Nation?' (y/n): ";
            char gate; cin >> gate; cin.ignore(1000, '\n');

            if (tolower(gate) == 'n') {
                cout << "\nGuard: 'An outsider, eh? Tell me the name of your people: ";
                getline(cin, countryName);
                cout << "Guard: 'Very well. Go to the Registration Tent to record your name.'" << endl;

                // FIXED CMD: Removed the sub-path to find Class_gen.exe in the same folder
                string cmd = "start /WAIT \"\" \"Class_Gen.exe\" \"" + countryName + "\"";
                system(cmd.c_str());
                return 0;
            } else {
                vector<string> countries;
                if (fs::exists("players")) {
                    for (const auto& entry : fs::directory_iterator("players"))
                        if (entry.is_directory()) countries.push_back(entry.path().filename().string());
                }
                if (countries.empty()) {
                    cout << "\nGuard: 'The records are empty! What nation do you represent?'" << endl;
                    getline(cin, countryName);
                } else {
                    cout << "\nGuard: 'Which nation do you hale from?'" << endl;
                    for(size_t i=0; i<countries.size(); i++) cout << i+1 << ". " << countries[i] << endl;
                    int pChoice; cin >> pChoice; cin.ignore(1000, '\n'); countryName = countries[pChoice-1];
                }
            }
        }

        countryActive = true;
        while (countryActive) {
            if (citizenName == "") {
                vector<string> citizens;
                string pPath = "players/" + countryName;
                if (fs::exists(pPath)) {
                    for (const auto& entry : fs::directory_iterator(pPath))
                        if (entry.path().extension() == ".txt") citizens.push_back(entry.path().stem().string());
                }
                if (citizens.empty()) {
                    cout << "\nGuard: 'I see no record of your name here. Off to the Registration Tent!'" << endl;
                    string cmd = "start /WAIT \"\" \"Class_Gen.exe\" \"" + countryName + "\"";
                    system(cmd.c_str());
                    return 0;
                } else {
                    cout << "\n[ NATION: " << countryName << " ]" << endl;
                    cout << "Guard: 'And who might you be, specifically?'" << endl;
                    for(size_t i=0; i<citizens.size(); i++) cout << i+1 << ". " << citizens[i] << endl;
                    cout << citizens.size()+1 << ". [Register New Citizen]\nChoice: ";
                    int cChoice; cin >> cChoice; cin.ignore(1000, '\n');
                    if (cChoice > (int)citizens.size()) {
                        string cmd = "start /WAIT \"\" \"Class_Gen.exe\" \"" + countryName + "\"";
                        system(cmd.c_str());
                        return 0;
                    }
                    citizenName = citizens[cChoice-1];
                }
            }

            if (!loadCitizen(pc, countryName, citizenName)) { citizenName = ""; continue; }

        townSquare:
            inTown = true;
            while(inTown) {
                loadCitizen(pc, countryName, citizenName);

                // CHECK FOR SPECIAL TRIAL ITEM
                bool hasSword = false;
                for(const string& item : pc.inventory) if(item == "Delian Sword") hasSword = true;

                cout << "\n================ TOWN SQUARE ================" << endl;
                cout << "Citizen: " << pc.name << " | Class: " << pc.charClass << " | Gold: " << pc.gold << "gp" << endl;
                cout << "1. Adventure | 2. Marketplace | 3. Rest (10gp)\n4. Switch Citizen | 5. Change Country | 6. Exit";
                if(hasSword) cout << "\n7. [TRIAL OF THE IRON CROWN]";
                cout << "\n> ";

                int choice;
                if (!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); continue; }

                if (choice == 1) {
                    saveCitizen(pc);
                    string prog = pc.inDungeon ? "Dungeon_phase.exe" : "Mansion_phase.exe";
                    string fullCmd = "start \"\" \"" + prog + "\" \"" + countryName + "\" \"" + citizenName + "\"";
                    system(fullCmd.c_str());
                    return 0;
                }
                else if (choice == 2) {
                    saveCitizen(pc);
                    string shopCmd = "start /WAIT \"\" \"Class_Gen.exe\" \"" + countryName + "\" \"" + citizenName + "\" \"SHOP\"";
                    system(shopCmd.c_str());
                }
                else if (choice == 3) {
                    if (pc.gold >= 10) {
                        pc.gold -= 10; pc.hp = 40;
                        saveCitizen(pc); cout << "[INN] Restored health!" << endl;
                    } else cout << "[INN] Not enough gold." << endl;
                }
                else if (choice == 4) { citizenName = ""; inTown = false; }
                else if (choice == 5) { countryName = ""; citizenName = ""; inTown = false; countryActive = false; }
                else if (choice == 6) { return 0; }
                else if (choice == 7 && hasSword) {
                    saveCitizen(pc);
                    string tCmd = "start /WAIT \"\" \"Trial_Minigame.exe\" \"" + countryName + "\" \"" + citizenName + "\"";
                    system(tCmd.c_str());
                }
            }
        }
    }
}

