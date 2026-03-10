// CSC 134
// M3HW1 - Silver
// James Taylor
// 3/09/2026

#include <iostream>
#include <string>
using namespace std;

int main() {
string response;

// Question 1
cout << "Question 1" << endl;
// Question 1 code goes here

cout << "Hello, I’m a C++ program! Do you like me?" << endl;
cout << "Please type yes or no. ";
getline (cin,response);
cout << endl;
cout << endl;

if (response == "yes") {
    cout << "That’s great! I sure hope we will get along." << endl;
    cout << endl;
    cout << endl;
}
else if (response == "no") {
    cout << "I hope to change that." << endl;
    cout << endl;
    cout << endl;
}

else {
    cout << "Well then we can figure it out together." << endl;
    cout << endl;
    cout << endl;
}
    return 0;
}