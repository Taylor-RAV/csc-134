// CSC 134 
// M2T1 
// James Taylor 
// 3/6/2026 
#include <iostream> 
#include <iomanip>
#include <string>
using namespace std; 
int main() { 
string name;    
double apples; 

double pricePerApple; 

double totalprice;
// price per apple 

// calculate the total price of the apples 
cout << "please enter your name?"<< endl;
cin >> name;
cout << "How many apples do you have?"<< endl;
cin >> apples;
cout << "How much do they cost?"<< endl;
cin >> pricePerApple;
totalprice = apples * pricePerApple;
cout << "Welcome to " << name; 
cout << "’s apple orchard." << endl; 
cout << "We have " << apples;
cout << " apples in stock." << endl;
cout << "Apples are currently $";
cout << pricePerApple <<" each." << endl;
cout << endl;
cout << "To buy all apples it would cost $";
cout << fixed << setprecision(2) << totalprice << " total."<< endl;
cout << endl;
return 0;
}
