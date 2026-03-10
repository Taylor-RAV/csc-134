// CSC 134
// M3HW3 - gold
// James Taylor
// 3/09/2026

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
string response;

    cout << "Question 2" << endl;
// Question 2 code goes here 
    double meal_price;
    int order_type;
    double tip_amount = 0.00;
    double tax_rate = 0.08;
    double tip_rate = 0.15;

    cout << "Please enter the price of the meal: "<< endl;
    cin >> meal_price;

    cout << "Please enter 1 if the order is dine in, 2 if it is to go: ";
    cin >> order_type;

    if (order_type == 1) {
        tip_amount = meal_price * tip_rate;
    }
    double tax_amount = meal_price * tax_rate;
    double total = meal_price + tax_amount + tip_amount;
    cout << fixed << setprecision(2) << endl;
    cout << "---- Receipt ------" << endl;
    cout << "Meal Price: $" << meal_price << endl;
    cout << "Tax:        $" << tax_amount << endl;
    cout << "Total:        $" << tax_amount + meal_price << endl;
   

   







    return 0;
}