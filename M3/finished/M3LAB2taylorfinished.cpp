// CSC 134
// M3LAB2
// Taylor
// 3/7/2025
// grade


#include <iostream>
using namespace std;


int main() {

    // Variables
    double grade;
    cout << "Enter the numerical grade (0-100): ";
    cin >> grade;

    cout << "Letter grade: ";

    if (grade >= 90 && grade <= 100) {
        cout << "A" << endl;
    } 
    else if (grade >= 80 && grade < 90) {
        cout << "B" << endl;
    } 
    else if (grade >= 70 && grade < 80) {
        cout << "C" << endl;
    } 
    else if (grade >= 60 && grade < 70) {
        cout << "D" << endl;
    } 
    else if (grade >= 0 && grade < 60) {
        cout << "F" << endl;
    } 
    else{
        cout << "Invalid Input (Grade must be between 0 and 100)" << endl;
    }
    cout <<endl;
    cout <<endl;
    cout <<endl;
    return 0;
}








