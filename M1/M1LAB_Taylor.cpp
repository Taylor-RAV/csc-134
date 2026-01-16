// CSC 134 
// M1LAB 
// Your Name 
// The Date 
#include <iostream> 
using namespace std; 
int main() { 
// This program will simulate an apple orchard. 
// The owner’s name 
string name = "James"; 
// number of apples owned 
int apples = 100;
// price per apple 
double pricePerApple = 0.25; 
// calculate the total price of the apples 
double totalprice = apples * pricePerApple;
// print all the information about the orchard 
cout << "Welcome to " << name; 
cout << "’s apple orchard." << endl; 
cout << "We have " << apples;
cout << " apples in stock." << endl;
cout << "Apples are currently $";
cout << pricePerApple <<" each." << endl;
cout << endl;
cout << "To buy all apples it would cost $";
cout << totalprice <<" total." << endl;
 cout << endl;
}