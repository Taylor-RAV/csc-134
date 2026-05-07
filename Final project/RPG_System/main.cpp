/**
 * @file RPG_System.cpp
 * @brief The Entry Hub. Manages character loading and the City Guard narrative.
 * Updated to restore narrative flavor and improve playtester readability.
 */

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <conio.h>
#include "shared_data.h"

namespace fs = std::filesystem;
using namespace std;

/**
 * @brief Displays the Character Sheet header at the top of the hub.
 */
void printStats(const Character& pc) {
    cout << "======================================================================" << endl;
    cout << " [LVL " << pc.level << " " << pc.race << " " << pc.charClass << "] " << pc.name << " of " << pc.playerName << endl;
    cout << " HP: " << pc.hp << "/" << pc.maxHp << " | AC: " << pc.ac << " | GOLD: " << pc.gold << "gp" << endl;

    if(pc.milestoneReached) {
        cout << " ** RITE OF PASSAGE AWAITS: VISIT THE SCRIBE TO ADVANCE **" << endl;
    }

    cout << " INV: ";
    if (pc.inventory.empty()) {
        cout << "[Empty]";
    } else {
        for (const auto& i : pc.inventory) cout << "[" << i << "] ";
    }
    cout << "\n======================================================================" << endl;
}

int main(int argc, char* argv[]) {
    string countryName = "", citizenName = "";
    Character pc;

    // --- AUTO-LOGIN HANDOFF ---
    if (argc >= 3) {
        countryName = argv[1];
        citizenName = argv[2];
        if (loadCitizen(pc, countryName, citizenName)) {
            goto townSquare;
        }
    }

    // --- NATION SELECTION ---
    while (true) {
        system("cls");
        cout << "\n--- THE GATES OF THE IRON CROWN ---" << endl;
        cout << "A gruff City Guard blocks your path with a heavy halberd." << endl;
        cout << "Guard: 'State your Nation for the ledger before you enter!'" << endl;
        cout << "--------------------------------------------------------" << endl;

        vector<string> nations;
        if (fs::exists("players")) {
            for (const auto& entry : fs::directory_iterator("players")) {
                if (entry.is_directory()) {
                    nations.push_back(entry.path().filename().string());
                }
            }
        }

        for (size_t i = 0; i < nations.size(); i++) {
            cout << i + 1 << ". " << nations[i] << endl;
        }
        cout << nations.size() + 1 << ". [Register New Nation/Party]" << endl;
        cout << "\nChoice: ";

        int nChoice;
        if (!(cin >> nChoice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (nChoice == (int)nations.size() + 1) {
            system("start /WAIT \"\" \"Class_Gen.exe\"");
            continue;
        }

        if (nChoice > 0 && nChoice <= (int)nations.size()) {
            countryName = nations[nChoice - 1];
        } else {
            continue;
        }

        // --- CITIZEN SELECTION ---
        while (true) {
            system("cls");
            cout << "\n--- REGISTRY OF " << countryName << " ---" << endl;
            cout << "Guard: 'And which citizen are you? Don't make me ask twice!'" << endl;
            cout << "--------------------------------------------------------" << endl;

            vector<string> citizens;
            string pPath = "players/" + countryName;
            if (fs::exists(pPath)) {
                for (const auto& entry : fs::directory_iterator(pPath)) {
                    if (entry.path().extension() == ".txt") {
                        citizens.push_back(entry.path().stem().string());
                    }
                }
            }

            for (size_t i = 0; i < citizens.size(); i++) {
                cout << i + 1 << ". " << citizens[i] << endl;
            }
            cout << citizens.size() + 1 << ". [New Traveler]" << endl;
            cout << citizens.size() + 2 << ". [Back to Nations]" << endl;
            cout << "\nChoice: ";

            int cChoice;
            cin >> cChoice;

            if (cChoice == (int)citizens.size() + 1) {
                system(("start /WAIT \"\" \"Class_Gen.exe\" \"" + countryName + "\"").c_str());
                continue;
            }
            if (cChoice == (int)citizens.size() + 2) break;

            if (cChoice > 0 && cChoice <= (int)citizens.size()) {
                citizenName = citizens[cChoice - 1];
                if (loadCitizen(pc, countryName, citizenName)) {
                    goto townSquare;
                }
            }
        }
    }

townSquare:
    while (true) {
        system("cls");
        cout << "\n--- THE COBBLESTONE TOWN SQUARE ---" << endl;
        printStats(pc);
        cout << "The town is tense. Green ooze seeps through the sewer grates." << endl;
        cout << "1. Adventure (Investigate the Ascension Mansion)" << endl;
        cout << "2. The Iron Anvil (Visit the Blacksmith)" << endl;
        cout << "3. The Bubbling Cauldron (Visit the Apothecary)" << endl;
        cout << "4. The Scribe's Archive (Request Rite of Passage)" << endl;
        cout << "5. The Restful Inn (10gp - Restore HP)" << endl;
        cout << "6. Log Out (Switch Citizen)" << endl;
        cout << "7. Exit Game" << endl;
        cout << "\nWhere will you go? ";

        int choice;
        cin >> choice;

        string cmdBase = "start /WAIT \"\" \"Class_Gen.exe\" \"" + pc.playerName + "\" \"" + pc.name + "\" ";

        if (choice == 1) {
            saveCitizen(pc);
            string prog = pc.inDungeon ? "Dungeon_phase.exe" : "Mansion_phase.exe";
            system(("start \"\" \"" + prog + "\" \"" + pc.playerName + "\" \"" + pc.name + "\"").c_str());
            return 0;
        }
        else if (choice == 2) {
            system((cmdBase + "BLACKSMITH").c_str());
            loadCitizen(pc, pc.playerName, pc.name);
        }
        else if (choice == 3) {
            system((cmdBase + "APOTHECARY").c_str());
            loadCitizen(pc, pc.playerName, pc.name);
        }
        else if (choice == 4) {
            system((cmdBase + "SCRIBE").c_str());
            loadCitizen(pc, pc.playerName, pc.name);
        }
        else if (choice == 5) {
            if (pc.gold >= 10) {
                pc.gold -= 10;
                pc.hp = pc.maxHp;
                saveCitizen(pc);
                cout << "\nYou rest deeply. HP and spirit restored!" << endl;
            } else {
                cout << "\nThe Innkeeper scoffs. 'No coin, no bed!'" << endl;
            }
            system("pause");
        }
        else if (choice == 6) {
            saveCitizen(pc);
            system("start \"\" \"RPG_System.exe\"");
            return 0;
        }
        else if (choice == 7) {
            saveCitizen(pc);
            return 0;
        }
    }
}
