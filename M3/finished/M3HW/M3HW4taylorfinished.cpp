// CSC 134
// M3HW1 - Silver
// James Taylor
// 3/09/2026

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    srand(time(0));

    int num1 = rand() % 10;
    int num2 = rand() % 10;
    int userAnswer;
    int correctAnswer = num1 + num2;

    cout << "What is " << num1 << " plus " << num2 << "?" << endl;
    cin >> userAnswer;

    if (userAnswer == correctAnswer) {
        cout << "Correct!" << endl;
    } else {
        cout << "Incorrect." << endl;
    }




    return 0;
}