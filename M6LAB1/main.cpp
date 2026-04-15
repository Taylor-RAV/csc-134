#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>

enum class Tile { Slime, Water, Empty };
enum class Item { MagnifyingGlass, Soap, Handcuffs };

class SlimeGunGame {
private:
    int pHP, dHP, numShells, roundNum;
    int pWins, dWins; // Track wins through the game
    bool isPlayerTurn, dealerCuffed;
    std::vector<Tile> magazine;
    std::vector<Item> inventory;
    std::mt19937 rng;

    std::string getItemName(Item it) {
        if (it == Item::MagnifyingGlass) return "Magnifying Glass (Peek)";
        if (it == Item::Soap) return "Soap (+1 HP)";
        return "Handcuffs (Skip Dealer Turn)";
    }

public:
    SlimeGunGame() : rng(std::time(0)) {
        roundNum = 1;
        numShells = 3;
        pWins = dWins = 0;
        isPlayerTurn = true;
    }

    void prepareRound() {
        int slimeCount = numShells / 2;
        int waterCount = numShells - slimeCount;
        pHP = dHP = (numShells + 1) / 2; // HP scales per round
        dealerCuffed = false;

        std::cout << "\n========================================";
        std::cout << "\nROUND " << roundNum << " / 10 | SCORE: " << pWins << " - " << dWins;
        std::cout << "\nHEALTH RESET TO: " << pHP;
        std::cout << "\nLOADING: " << slimeCount << " SLIME, " << waterCount << " WATER";
        std::cout << "\n========================================\n";

        magazine.clear();
        for (int i = 0; i < slimeCount; ++i) magazine.push_back(Tile::Slime);
        for (int i = 0; i < waterCount; ++i) magazine.push_back(Tile::Water);
        std::shuffle(magazine.begin(), magazine.end(), rng);
    }

    void grantItems() {
        if (roundNum >= 3) {
            std::uniform_int_distribution<int> dist(0, 2);
            inventory.push_back(static_cast<Item>(dist(rng)));
            inventory.push_back(static_cast<Item>(dist(rng)));
            std::cout << ">> ITEM PHASE: 2 Items added <<\n";
        }
    }

    void start() {
        while (roundNum <= 10) {
            prepareRound();
            grantItems();

            int i = 0;
            while (i < magazine.size() && pHP > 0 && dHP > 0) {
                if (!isPlayerTurn && dealerCuffed) {
                    std::cout << "\n[DEALER] Handcuffed! Turn skipped.\n";
                    dealerCuffed = false;
                    isPlayerTurn = true;
                    continue;
                }

                bool extraTurn = (isPlayerTurn) ? playerTurn(i) : dealerTurn(i);
                i++;
                if (pHP <= 0 || dHP <= 0) break;
                if (!extraTurn) isPlayerTurn = !isPlayerTurn;
            }

            // End of Round: Winner Determination
            if (pHP > dHP) {
                std::cout << "\n*** YOU WIN ROUND " << roundNum << "! ***\n";
                pWins++;
            } else if (dHP > pHP) {
                std::cout << "\n*** DEALER WINS ROUND " << roundNum << "! ***\n";
                dWins++;
            } else {
                std::cout << "\n*** ROUND " << roundNum << " IS A DRAW! ***\n";
            }

            std::cout << "Current Standings: YOU " << pWins << " | DEALER " << dWins << "\n";
            roundNum++;
            numShells += 2;
        }

        std::cout << "\nFinal Result: " << (pWins > dWins ? "YOU ARE THE ULTIMATE CHAMPION!" : "THE DEALER OUTLASTED YOU.");
    }

    bool playerTurn(int chamber) {
        while (true) {
            std::cout << "\n[YOU] HP: " << pHP << " | [DEALER] HP: " << dHP << " | Choice: (1) Fire (2) Self (3) Items: ";
            int choice; std::cin >> choice;

            if (choice == 3) {
                if (inventory.empty()) { std::cout << "No items!\n"; continue; }
                std::cout << "Select item: ";
                for(int i=0; i<inventory.size(); ++i) std::cout << "(" << i+1 << ") " << getItemName(inventory[i]) << " ";
                int itemIdx; std::cin >> itemIdx;
                if (itemIdx < 1 || itemIdx > inventory.size()) continue;

                Item used = inventory[itemIdx - 1];
                inventory.erase(inventory.begin() + (itemIdx - 1));
                if (used == Item::MagnifyingGlass) std::cout << ">> PEEK: " << (magazine[chamber] == Tile::Slime ? "SLIME" : "WATER") << "\n";
                else if (used == Item::Soap) pHP++;
                else if (used == Item::Handcuffs) dealerCuffed = true;
                continue;
            }

            Tile shot = magazine[chamber];
            if (choice == 2) {
                if (shot == Tile::Slime) { pHP--; std::cout << "SPLAT! Slimed self.\n"; return false; }
                else { std::cout << "Splash! Water. GO AGAIN!\n"; return true; }
            } else {
                if (shot == Tile::Slime) { dHP--; std::cout << "SPLAT! Hit dealer!\n"; }
                else std::cout << "Splash! Missed dealer.\n";
                return false;
            }
        }
    }

    bool dealerTurn(int chamber) {
        int s = 0, w = 0;
        for (int j = chamber; j < magazine.size(); j++) {
            (magazine[j] == Tile::Slime) ? s++ : w++;
        }
        bool targetSelf = (w > s);
        std::cout << "\n[DEALER] shoots " << (targetSelf ? "themselves..." : "you...");

        if (magazine[chamber] == Tile::Slime) {
            (targetSelf) ? dHP-- : pHP--;
            std::cout << " SPLAT!\n";
            return false;
        } else {
            std::cout << " Splash! Water.\n";
            return targetSelf; // Dealer goes again if they shoot self with water
        }
    }
};

int main() {
    SlimeGunGame game;
    game.start();
    return 0;
}
