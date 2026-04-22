#include <iostream>
#include "Rectangle.h..h" // Links the header file
using namespace std;

int main() {
    Rectangle box;
    double rectWidth;
    double rectLength;

    // Get and validate rectangle width
    cout << "Enter the rectangle's width: ";
    cin >> rectWidth;
    while (rectWidth <= 0) {
        cout << "Invalid size! Width must be greater than zero: ";
        cin >> rectWidth;
    }

    // Get and validate rectangle length
    cout << "Enter the rectangle's length: ";
    cin >> rectLength;
    while (rectLength <= 0) {
        cout << "Invalid size! Length must be greater than zero: ";
        cin >> rectLength;
    }

    // Pass validated data to the object
    box.setWidth(rectWidth);
    box.setLength(rectLength);

    // Display the results
    cout << "\n--- Rectangle Results ---\n";
    cout << "Width:  " << box.getWidth() << endl;
    cout << "Length: " << box.getLength() << endl;
    cout << "Area:   " << box.getArea() << endl;

    return 0;
}
