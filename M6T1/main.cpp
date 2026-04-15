// CSC 134
// M6T1 - Loops and Arrays
// James Taylor
// 4/13/2026

#include <iostream>
#include <string> // Added for string support
using namespace std;

// Function Declarations - Names must match definitions below
void part1();
void part2_scaled();

int main() {
    // Call the two methods to compare logic
    part1();
    part2_scaled();

    return 0;
}

// Part 1: Running total without arrays
void part1() {
    const int DAYS = 5;
    int cars_today, total_cars = 0;

    cout << "\n--- Part 1: No Arrays ---" << endl;
    for (int i = 0; i < DAYS; i++) {
        cout << "Enter cars for day " << i + 1 << ": ";
        cin >> cars_today;
        total_cars += cars_today;
    }

    double average = (double)total_cars / DAYS;
    cout << "Total Cars: " << total_cars << endl;
    cout << "Average per day: " << average << endl;
}

// Part 2: Data persistence with arrays and ASCII graph
void part2_scaled() {
    const int DAYS = 5;
    string days[] = {"Mon", "Tue", "Wed", "Thu", "Fri"};
    int cars[DAYS];
    const int SCALE = 10; // 1 asterisk = 10 cars
    int total_cars = 0;

    cout << "\n--- Part 2: With Arrays & Graph ---" << endl;
    // Input Loop
    for (int i = 0; i < DAYS; i++) {
        cout << "Cars for " << days[i] << ": ";
        cin >> cars[i];
        total_cars += cars[i];
    }

    // Results summary
    double average = (double)total_cars / DAYS;
    cout << "\nTotal: " << total_cars << " | Avg: " << average << endl;

    // ASCII Graph with Scaling
    cout << "\n--- Traffic Graph (Scale: 1 * = " << SCALE << " cars) ---" << endl;
    for (int i = 0; i < DAYS; i++) {
        cout << days[i] << " | ";

        // Calculate how many stars to print
        int num_stars = cars[i] / SCALE;

        for (int j = 0; j < num_stars; j++) {
            cout << "*";
        }

        // Show the actual number at the end for clarity
        cout << " (" << cars[i] << ")" << endl;
    }
}
