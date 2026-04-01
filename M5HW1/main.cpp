#include <iostream>
#include <iomanip> // Helpful for decimal math
#include <cmath>   // Helpful for volume/geometry calculations
using namespace std;

// --- QUESTION 1: AVERAGE RAINFALL ---
void question1() {
    cout << "Running question 1: Average rainfall\n";
    string month1, month2, month3;
    double rain1, rain2, rain3;

    // Input for Month 1
    cout << "Enter month: ";
    cin >> month1;
    cout << "Enter rainfall for " << month1 << ": ";
    cin >> rain1;

    // Input for Month 2
    cout << "Enter month: ";
    cin >> month2;
    cout << "Enter rainfall for " << month2 << ": ";
    cin >> rain2;

    // Input for Month 3
    cout << "Enter month: ";
    cin >> month3;
    cout << "Enter rainfall for " << month3 << ": ";
    cin >> rain3;

    // Calculate the average
    double average = (rain1 + rain2 + rain3) / 3.0;

    // Display result rounded to 2 decimal places
    cout << fixed << setprecision(2);
    cout << "The average rainfall for " << month1 << ", " << month2
         << ", and " << month3 << " is " << average << " inches." << endl;
}


// --- QUESTION 2: VOLUME OF A CUBE ---
void question2() {
    cout << "Running question 2: Volume of a cube\n";
    double width, length, height;

    // Get dimensions from the user
    cout << "Enter the width of the block: ";
    cin >> width;
    cout << "Enter the length of the block: ";
    cin >> length;
    cout << "Enter the height of the block: ";
    cin >> height;

    // Input Validation: Check if any side is zero or negative
    if (width <= 0 || length <= 0 || height <= 0) {
        cout << "Error: No side can be zero or less. Please try again." << endl;
    } else {
        // Calculate and display volume
        double volume = width * length * height;
        cout << "The volume of the block is: " << volume << " cubic units." << endl;
    }
}


// --- QUESTION 3: ROMAN NUMERAL CHANGE ---
void question3() {
    cout << "Running question 3: Roman numeral change\n";
    int number;

    // Get input from user
    cout << "Enter a number (1-10) to convert to Roman: ";
    cin >> number;

    // Switch statement to handle the conversion
    switch (number) {
        case 1:  cout << "Roman numeral: I" << endl; break;
        case 2:  cout << "Roman numeral: II" << endl; break;
        case 3:  cout << "Roman numeral: III" << endl; break;
        case 4:  cout << "Roman numeral: IV" << endl; break;
        case 5:  cout << "Roman numeral: V" << endl; break;
        case 6:  cout << "Roman numeral: VI" << endl; break;
        case 7:  cout << "Roman numeral: VII" << endl; break;
        case 8:  cout << "Roman numeral: VIII" << endl; break;
        case 9:  cout << "Roman numeral: IX" << endl; break;
        case 10: cout << "Roman numeral: X" << endl; break;
        default:
            cout << "Error: Enter a number specifically between 1 and 10." << endl;
    }
}


// --- QUESTION 4: GEOMETRY CALCULATOR ---
void question4() {
    int selection = 0;

    // The loop keeps the user here until they choose 4
    while (selection != 4) {
        cout << "\nGeometry Calculator\n"
             << "1. Calculate the Area of a Circle\n"
             << "2. Calculate the Area of a Rectangle\n"
             << "3. Calculate the Area of a Triangle\n"
             << "4. Quit\n"
             << "Enter your choice (1-4): ";
        cin >> selection;

        if (selection == 1) {
            double radius;
            cout << "Enter the radius: ";
            cin >> radius;
            if (radius < 0) cout << "Error: Radius cannot be negative.\n";
            else cout << "Area: " << 3.14159 * pow(radius, 2) << endl;
        }
        else if (selection == 2) {
            double length, width;
            cout << "Enter length: "; cin >> length;
            cout << "Enter width: "; cin >> width;
            if (length < 0 || width < 0) cout << "Error: Dimensions cannot be negative.\n";
            else cout << "Area: " << length * width << endl;
        }
        else if (selection == 3) {
            double base, height;
            cout << "Enter base: "; cin >> base;
            cout << "Enter height: "; cin >> height;
            if (base < 0 || height < 0) cout << "Error: Dimensions cannot be negative.\n";
            else cout << "Area: " << base * height * 0.5 << endl;
        }
        else if (selection == 4) {
            cout << "Returning to Main Menu...\n";
        }
        else {
            cout << "Error: Invalid selection. Please enter 1-4.\n";
        }
    }
}



// --- QUESTION 5: DISTANCE TRAVELED ---
void question5() {
    cout << "Running question 5: Distance traveled\n";
    double speed;
    int hours;

    cout << "What is the speed of the vehicle in mph? ";
    cin >> speed;
    if (speed < 0) {
        cout << "Error: Speed cannot be a negative number." << endl;
        return; // Exit function if invalid
    }

    cout << "How many hours has it traveled? ";
    cin >> hours;
    if (hours < 1) {
        cout << "Error: Time traveled must be at least 1 hour." << endl;
        return; // Exit function if invalid
    }


    cout << "\nHour   Distance Traveled" << endl;
    cout << "--------------------------------" << endl;


    for (int i = 1; i <= hours; i++) {
        double distance = speed * i;
        // setw(4) and left/right help align the columns neatly
        cout << left << setw(6) << i << distance << endl;
    }
}


int main() {
    int choice;

    do {
        cout << "\n--- CHOOSE A PROGRAM TO RUN ---" << endl;
        cout << "1. Average rainfall." << endl;
        cout << "2. Volume of a cube." << endl;
        cout << "3. Roman numeral change." << endl;
        cout << "4. Geometry Calculator" << endl;
        cout << "5. Distance traveled" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1: question1(); break;
            case 2: question2(); break;
            case 3: question3(); break;
            case 4: question4(); break;
            case 5: question5(); break;
            case 0: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}

