/**
 * @file Trial_Minigame.cpp
 * @brief The Final Boss Trial. Logic recognizes Spells, Talents, and Items.
 */

#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
#include <vector>
#include <conio.h>
#include "shared_data.h"

using namespace std;

int getMod(int stat) { return (stat >= 10) ? (stat - 10) / 2 : (stat - 11) / 2; }

void play(Character& pc) {
    int bossHP = 120, bxs[5], rem = 0; bool avl[5];
    system("color 0A"); // Cosmic Green Terminal
    system("cls");
    cout << "======================================================================" << endl;
    cout << " [ THE SANCTUM OF THE KING'S ASCENSION ]" << endl;
    cout << "THE AMALGAMATION: 'The King is gone. I am... the Successor.'" << endl;
    cout << "'Let us see if your will is as fluid as mine, or as rigid as stone.'" << endl;
    system("pause");

    while (bossHP > 0 && pc.hp > 0) {
        if (rem < 2) {
            bxs[0]=1; bxs[1]=1; bxs[2]=0; bxs[3]=0; bxs[4]=0;
            for(int i=0; i<5; i++){ swap(bxs[i], bxs[rand()%5]); avl[i]=true; }
            rem = 5;
            cout << "\nTHE AMALGAMATION: 'Let us prepare a new round of chance...'" << endl;
            system("pause");
        }
        system("cls");
        cout << " THE KING'S SPIRIT HP: [" << bossHP << "/120] | " << pc.name << " HP: [" << pc.hp << "/" << pc.maxHp << "]\nBOXES: ";
        for(int i=0; i<5; i++) cout << (avl[i] ? "[ "+to_string(i+1)+" ] " : "[ X ] ");

        cout << "\nChoice (1-5): ";
        int p; cin >> p; p--; if(p<0||p>4||!avl[p]) continue; avl[p]=false; rem--;
        int b; do { b = rand()%5; } while (!avl[b]); avl[b]=false; rem--;

        bool pSlime = (bxs[p] == 1);
        bool bSlime = (bxs[b] == 1);

        cout << "\nYOU OPEN: " << (pSlime ? "LIVE SLIME!" : "EMPTY") << endl;
        cout << "KING OPENS: " << (bSlime ? "LIVE SLIME!" : "EMPTY") << endl;

        if (pSlime && !bSlime) { cout << "Your slime lunges! Direct Strike."; bossHP -= 30; }
        else if (!pSlime && bSlime) { cout << "The Boss's slime strikes you!"; pc.hp -= 20; }
        else if (pSlime && bSlime) {
            cout << "--- SLIME CLASH ---\n";
            int pow = (rand()%20 + 1) + getMod(pc.baseStats[0]);
            for(auto& i : pc.inventory) {
                if(i=="Caustic Solvent") { pow += 10; cout << ">> [ITEM] +10 Solvent Power\n"; }
                if(i=="Magic Missile") { pow += 15; cout << ">> [SPELL] +15 Arcane Barrage\n"; }
                if(i=="Second Wind") { pc.hp += 15; if(pc.hp > pc.maxHp) pc.hp = pc.maxHp; cout << ">> [TALENT] Healed 15 HP\n"; }
                if(i=="Sneak Attack") { pow += 12; cout << ">> [TALENT] +12 Critical Strike\n"; }
                if(i=="Holy Smite") { pow += 18; cout << ">> [SPELL] +18 Divine Wrath\n"; }
            }
            if (pow >= (rand()%20 + 9)) { cout << "Your slime dominates the clash!"; bossHP -= 30; }
            else { cout << "You are overwhelmed by the King's will."; pc.hp -= 20; }
        } system("pause");
    }

    system("cls");
    if (pc.hp > 0) {
        cout << "VICTORY! The Amalgamation shatters into cosmic mist." << endl;
        cout << "You claim the [Slime Key]—the final seal of the Ascension." << endl;
        pc.inventory.push_back("Slime Key");
    }
    else {
        cout << "DEFEAT. Your spirit is consumed by the ooze." << endl;
        cout << "The Town Guard drags your broken form back to the Inn." << endl;
    }
    system("pause");
}

int main(int argc, char* argv[]) {
    srand(time(0)); Character pc; if (argc < 3 || !loadCitizen(pc, argv[1], argv[2])) return 1;
    play(pc); saveCitizen(pc); return 0;
}
