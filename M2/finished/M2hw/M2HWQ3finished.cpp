// CSC 134 
// M1LAB 
// James Taylor
// 01_26_26
#include <iostream> 
using namespace std; 

int main() { 
    //Declare all variables
    string meal_name = "Burger Combo";
    int numPizzas, slicesPerPizza, numVisitors;
    int totalSlices, slicesPerPerson, slicesLeftover;


    cout << "How many pizzas did you order? ";
    cin >> numPizzas;

    cout << "How many slices are in each pizza? ";
    cin >> slicesPerPizza;

    cout << "How many visitors are coming? ";
    cin >> numVisitors;

    // calculate
   totalSlices = numPizzas * slicesPerPizza;
   slicesPerPerson = totalSlices / numVisitors;
   slicesLeftover = totalSlices % numVisitors;

    // print ticket
    cout << "\n--- Pizza Results ---" << endl;
    cout << "Total slices made:    " << totalSlices << endl;
    cout << "Slices per person:    " << slicesPerPerson << endl;
    cout << "Leftover pieces:      " << slicesLeftover << endl;
    cout << "Have a great Day!"<< endl;
    cout << endl;
    cout << endl;

    return 0;
}