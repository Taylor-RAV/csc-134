/**
 * @file main.cpp
 * @author James Taylor
 * @brief Gold Tier - Driver program for the Rectangle class.
 * Demonstrates object instantiation, validation, and area output.
 * @date 2026-05-08
 */

#include <iostream>
#include <iomanip>
#include "Rectangle.h" // Including the class header

using namespace std;

int main() {
    Rectangle myRect; // Create an instance of the Rectangle class
    double rectWidth;
    double rectLength;

    cout << "--- Rectangle Area Calculator (Gold Tier) ---" << endl;
    cout << "Author: James Taylor" << endl << endl;

    // Get the rectangle's width
    cout << "Enter the rectangle's width: ";
    cin >> rectWidth;

    // Silver Requirement: Basic validation check before setting
    while (rectWidth <= 0) {
        cout << "Error: Width must be greater than zero. Try again: ";
        cin >> rectWidth;
    }
    myRect.setWidth(rectWidth);

    // Get the rectangle's length
    cout << "Enter the rectangle's length: ";
    cin >> rectLength;

    // Silver Requirement: Basic validation check before setting
    while (rectLength <= 0) {
        cout << "Error: Length must be greater than zero. Try again: ";
        cin >> rectLength;
    }
    myRect.setLength(rectLength);

    // Display the rectangle's data
    cout << fixed << setprecision(2);
    cout << "\nRectangle Details:" << endl;
    cout << "Width:  " << myRect.getWidth() << endl;
    cout << "Length: " << myRect.getLength() << endl;
    cout << "Area:   " << myRect.getArea() << " square units" << endl;

    return 0;
}
