// CSC 134
// M3T1 
// James Taylor
// 3/7/2026
// Ask the user for the width and length of two rectangles
// Find the area

#include <iostream>
using namespace std;


int main() {

    // Variables
    double len1, wid1, len2, wid2; 
    double area1, area2;

    // Ask user for the length and width
    cout << "What's the length of the first rectangle? ";
    cin >> len1;
    cout << "What's the width of the first rectangle? ";
    cin >> wid1;
    cout << "What's the length of the second rectangle? ";
    cin >> len2;
    cout << "What's the width of the second rectangle? ";
    cin >> wid2;

    // Find the area
    area1 = len1 * wid1;
    area2 = len2 * wid2;
    double total_area = area1 + area2;

    // Print the area
    cout << "Area of first rectangle:        " << area1 << endl;
    cout << "Area of second rectangle:       " << area2 << endl;
    cout << "Total area of both rectangles:  " << total_area << endl;
    cout << endl;
    cout << endl;
    return 0;
}