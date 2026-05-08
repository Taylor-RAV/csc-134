/**
 * @file shared_data.h
 * @author James Taylor
 * @brief THE OOZING CROWN: Master Data Bridge.
 * Standardized structure for cross-executable character persistence.
 */

#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;
using namespace std;

struct Character {
    string playerName;
    string name;
    string race;
    string charClass;
    int baseStats[6];  // STR, DEX, CON, INT, WIS, CHA
    int level = 1;
    bool milestoneReached = false;
    int hp = 40;
    int maxHp = 40;
    int ac = 12;
    int gold = 100;
    vector<string> inventory;
    bool inDungeon = false;
    bool rackMoved = false;
    int lastRoom = 0;
};

inline bool saveCitizen(const Character& pc) {
    string path = "players/" + pc.playerName;
    if (!fs::exists(path)) fs::create_directories(path);
    ofstream fout(path + "/" + pc.name + ".txt");
    if (!fout) return false;

    fout << pc.playerName << "\n" << pc.name << "\n" << pc.race << "\n" << pc.charClass << "\n";
    for(int i=0; i<6; i++) fout << pc.baseStats[i] << (i==5 ? "" : " ");
    fout << "\n" << pc.level << " " << (pc.milestoneReached ? 1 : 0) << " " << pc.hp << " " << pc.maxHp << " " << pc.ac << " " << pc.gold << "\n";
    fout << pc.inventory.size() << "\n";
    for(const auto& item : pc.inventory) fout << item << "\n";
    fout << pc.lastRoom << " " << (pc.inDungeon ? 1 : 0) << " " << (pc.rackMoved ? 1 : 0) << "\n";
    fout.close();
    return true;
}

inline bool loadCitizen(Character& pc, string nation, string name) {
    ifstream fin("players/" + nation + "/" + name + ".txt");
    if (!fin) return false;

    getline(fin, pc.playerName); getline(fin, pc.name); getline(fin, pc.race); getline(fin, pc.charClass);
    for(int i=0; i<6; i++) fin >> pc.baseStats[i];
    int msFlag, dungFlag, rackFlag;
    fin >> pc.level >> msFlag >> pc.hp >> pc.maxHp >> pc.ac >> pc.gold;
    pc.milestoneReached = (msFlag == 1);
    int invSize; fin >> invSize; fin.ignore();
    pc.inventory.clear();
    for(int i=0; i<invSize; i++) { string item; getline(fin, item); pc.inventory.push_back(item); }
    fin >> pc.lastRoom >> dungFlag >> rackFlag;
    pc.inDungeon = (dungFlag == 1); pc.rackMoved = (rackFlag == 1);
    fin.close();
    return true;
}

#endif
