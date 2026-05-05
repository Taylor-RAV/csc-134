#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

struct Ability { std::string name, desc; };

struct Character {
    std::string playerName, name, race, charClass;
    int baseStats[6];
    int hp, ac, gold, resources, lastRoom;
    bool inDungeon;
    std::vector<std::string> inventory;
    std::vector<Ability> chosenAbilities;
};

// Global stable save
inline void saveCitizen(const Character &c) {
    std::filesystem::create_directories("players/" + c.playerName);
    std::ofstream f("players/" + c.playerName + "/" + c.name + ".txt");
    if (!f.is_open()) return;
    f << c.playerName << "\n" << c.name << "\n" << c.race << "\n" << c.charClass << "\n";
    for(int i=0; i<6; i++) f << c.baseStats[i] << (i < 5 ? " " : "\n");
    f << c.hp << "\n" << c.ac << "\n" << c.gold << "\n" << c.resources << "\n";
    f << c.inventory.size() << "\n";
    for(const auto& s : c.inventory) f << s << "\n";
    f << c.chosenAbilities.size() << "\n";
    for(const auto& a : c.chosenAbilities) f << a.name << "\n";
    f << c.lastRoom << "\n" << (int)c.inDungeon << "\n1 1 1 1 1 1";
}

// Global stable load
inline bool loadCitizen(Character &c, std::string country, std::string name) {
    std::ifstream f("players/" + country + "/" + name + ".txt");
    if(!f.is_open()) return false;
    std::getline(f, c.playerName); std::getline(f, c.name); std::getline(f, c.race); std::getline(f, c.charClass);
    for(int i=0; i<6; i++) f >> c.baseStats[i];
    f >> c.hp >> c.ac >> c.gold >> c.resources;
    int is, abs; f >> is; f.ignore(); c.inventory.clear();
    for(int i=0; i<is; i++) { std::string s; std::getline(f, s); c.inventory.push_back(s); }
    f >> abs; f.ignore(); c.chosenAbilities.clear();
    for(int i=0; i<abs; i++) { std::string s; std::getline(f, s); c.chosenAbilities.push_back({s, ""}); }
    f >> c.lastRoom >> c.inDungeon;
    return true;
}
#endif
