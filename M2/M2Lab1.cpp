// CSC 134
// M1LAB
// Your Name
// The Date
#include <iostream>
#include <iomanip>
using namespace std;
int main() {
//declare variables
//non changing
const double cost_per_cubic_foot = 0.23;
const double charge_per_cubic_foot = 0.5;

//create cariables
double length, width, height, volume; //all in feet

//money varriables
double cost, customer_price, profit;

// Part 2 get input
cout << "welcome to the crate managment program." <<endl;
cout << "Enter the demesions of the crate. (in feet.)" <<endl;

cout<< "Crate Length?"<< endl;
cin >> length;

cout<< "Crate height?"<< endl;
cin >> height;

cout<< "Crate width?"<< endl;
cin >> width;

// part 3 calculations
volume = length * width * height;
cost = volume * cost_per_cubic_foot;
customer_price = volume * charge_per_cubic_foot;
profit = customer_price - cost;

//part 4 output
cout << setprecision(2) << fixed;
cout << "\n";
cout << "====== crate info ======" << "\n";
cout << "Volume is " << volume << " cubic feet." << "\n";
cout << "\n";
cout << "Cost to buile is $" << cost  << "\n";
cout << "\n";
cout << "Charge to customer is $" << customer_price << "\n";
cout << "\n";
cout << "Profit for sale is  $" << profit  << "\n";
cout << "\n";
return 0;
}