/**
 * @file Hub_Main.cpp
 * @author James Taylor
 * @brief THE OOZING CROWN: Central Hub and Session Manager.
 */

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <conio.h>
#include "shared_data.h"

namespace fs = std::filesystem;
using namespace std;

void printStats(const Character& pc) {
    cout << "====================================================" << endl;
    cout << " [LVL " << pc.level << " " << pc.race << " " << pc.charClass << "] " << pc.name << " of " << pc.playerName << endl;
    cout << " HP: " << pc.hp << "/" << pc.maxHp << " | AC: " << pc.ac << " | GOLD: " << pc.gold << "gp" << endl;
    if(pc.milestoneReached) cout << " ** RITE OF PASSAGE AWAITS: VISIT THE SCRIBE **" << endl;
    cout << " INV: ";
    if (pc.inventory.empty()) cout << "[Empty]";
    else for (const auto& i : pc.inventory) cout << "[" << i << "] ";
    cout << "\n====================================================" << endl;
}

int main(int argc, char* argv[]) {
    string countryName = "", citizenName = "";
    Character pc;

    if (argc >= 3) {
        countryName = argv[1]; citizenName = argv[2];
        if (loadCitizen(pc, countryName, citizenName)) goto townSquare;
    }

    while (true) {
        system("cls");
        cout << "\n--- THE GATES OF THE IRON CROWN ---" << endl;
        cout << "A gruff City Guard blocks your path with a heavy halberd." << endl;

        vector<string> nations;
        if (fs::exists("players")) {
            for (const auto& entry : fs::directory_iterator("players"))
                if (entry.is_directory()) nations.push_back(entry.path().filename().string());
        }

        for (size_t i = 0; i < nations.size(); i++) cout << i + 1 << ". " << nations[i] << endl;
        cout << nations.size() + 1 << ". [Register New Nation]" << endl;
        cout << "\nChoice: ";

        int nChoice; cin >> nChoice;
        if (nChoice == (int)nations.size() + 1) {
            system("start /WAIT \"\" \"Class_Gen.exe\"");
            continue;
        }
        if (nChoice > 0 && nChoice <= (int)nations.size()) countryName = nations[nChoice - 1];
        else continue;

        while (true) {
            system("cls");
            cout << "\nGuard: 'And which traveler of " << countryName << " are you?'\n" << endl;
            vector<string> citizens;
            string pPath = "players/" + countryName;
            if (fs::exists(pPath)) {
                for (const auto& entry : fs::directory_iterator(pPath))
                    if (entry.path().extension() == ".txt") citizens.push_back(entry.path().stem().string());
            }

            for (size_t i = 0; i < citizens.size(); i++) cout << i + 1 << ". " << citizens[i] << endl;
            cout << citizens.size() + 1 << ". [New Traveler] | " << citizens.size() + 2 << ". [Back]" << endl;
            cout << "\nChoice: ";

            int cChoice; cin >> cChoice;
            if (cChoice == (int)citizens.size() + 1) {
                system(("start /WAIT \"\" \"Class_Gen.exe\" \"" + countryName + "\"").c_str());
                continue;
            }
            if (cChoice == (int)citizens.size() + 2) break;

            if (cChoice > 0 && cChoice <= (int)citizens.size()) {
                citizenName = citizens[cChoice - 1];
                if (loadCitizen(pc, countryName, citizenName)) goto townSquare;
            }
        }
    }

townSquare:
    while (true) {
        system("cls");
        cout << "\n--- THE COBBLESTONE TOWN SQUARE ---" << endl;
        printStats(pc);
        cout << "1. Adventure (Enter the Mansion)" << endl;
        cout << "2. Visit the Blacksmith" << endl;
        cout << "3. Visit the Apothecary" << endl;
        cout << "4. Visit the Scribe" << endl;
        cout << "5. Rest at the Inn (10gp)" << endl;
        cout << "6. Switch Citizen" << endl;
        cout << "7. Exit Game" << endl;
        cout << "> ";

        int choice; cin >> choice;
        string cmdBase = "start /WAIT \"\" \"Class_Gen.exe\" \"" + pc.playerName + "\" \"" + pc.name + "\" ";

        if (choice == 1) {
            saveCitizen(pc);
            string prog = pc.inDungeon ? "Dungeon_phase.exe" : "Mansion_phase.exe";
            system(("start \"\" \"" + prog + "\" \"" + pc.playerName + "\" \"" + pc.name + "\"").c_str());
            return 0;
        }
        else if (choice == 2) { system((cmdBase + "BLACKSMITH").c_str()); loadCitizen(pc, pc.playerName, pc.name); }
        else if (choice == 3) { system((cmdBase + "APOTHECARY").c_str()); loadCitizen(pc, pc.playerName, pc.name); }
        else if (choice == 4) { system((cmdBase + "SCRIBE").c_str()); loadCitizen(pc, pc.playerName, pc.name); }
        else if (choice == 5 && pc.gold >= 10) {
            pc.gold -= 10; pc.hp = pc.maxHp; saveCitizen(pc);
            cout << "\nHP Restored!"; system("pause");
        }
        else if (choice == 6) { saveCitizen(pc); system("start \"\" \"Hub_Main.exe\""); return 0; }
        else if (choice == 7) { saveCitizen(pc); return 0; }
    }
}
