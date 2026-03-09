// CSC 134
// M3T1 
// Taylor
// 2/23/2025
// DND door choice


#include <iostream>
using namespace std;
void do_choise_stay();
void do_choise_leave();
void do_choise_3();
void do_choise_4();

int main() {
    string choise;
    cout << "You enter the haunted ballroom." << endl;
    cout << "There is a long table with 8 chairs on each side of the table." << endl;
    cout << "The hall has two doors one on each side and a hallway leading out directly ahead of you on the oposite side of the table." << endl;
    cout << "will you [stay] or [leave]?" << endl;

    cout << ">";
    cin >> choise;

    if ("stay" == choise){
        do_choise_stay();
    }
    else if ("leave" == choise){
        do_choise_leave();
    }
    else {
        cout << "choose to stay or leave looking around is staying." << endl;
    }
    cout << "You get to watch." << endl;
    return 0; 

}

// function Definitions go here
void do_choise_stay() {
    cout << "You stay" << endl; 
}

void do_choise_leave() {
    cout << "You leave" << endl; 
}