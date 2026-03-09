// CSC 134 
// M1LAB 
// James Taylor
// 3/8/26
#include <iostream> 
#include <iomanip>
#include <string>
using namespace std; 

int main() { 
    //Declare all variables
    string meal_name = "Burger Combo";
    int num_meals;
    double meal_price = 5.99;
    double tax_rate = .08;

    // get imput for calculations
    cout << "how many "<< meal_name << "'s would you like to order?"<< endl;
    cin >> num_meals;

    // calculate
    double sub_total = meal_price * num_meals;
    double tax_amount = sub_total * tax_rate;
    double total = sub_total + tax_amount;

    // print ticket
    cout << fixed << setprecision(2);
    cout << "---- Receipt------" << endl;
    cout << "Meals:      " << num_meals << endl;
    cout << "Subtotal:   $" << sub_total << endl;
    cout << "Tax:        $" << tax_amount << endl;
    cout << "Total:      $" << total << endl;
    cout << endl;
    cout << "Have a great Day!"<< endl;
    cout << endl;
    cout << endl;

    return 0;
}

