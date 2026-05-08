#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

#ifdef _WIN32
#include <windows.h> // Required for UTF-8 support in Windows Console
#endif

using namespace std;

/**
 * @class Restaurant
 * @brief Represents a dining establishment with star rating logic.
 */
class Restaurant {
private:
    string name;
    double rating;

public:
    /**
     * @brief Constructor for a new Restaurant object.
     * @param n Restaurant Name
     * @param r Rating (0.0 - 5.0)
     */
    Restaurant(string n, double r) : name(n), rating(r) {}

    // --- Accessors ---
    string getName() const { return name; }
    double getRating() const { return rating; }

    /**
     * @brief Renders the rating visually using UTF-8 stars.
     */
    void display() const {
        cout << left << setw(20) << name << " | ";

        int fullStars = static_cast<int>(rating);
        bool hasHalfStar = (rating - fullStars) >= 0.5;

        // Print full stars
        for (int i = 0; i < fullStars; i++) cout << "⭐";
        // Print half star if applicable
        if (hasHalfStar) cout << "✨";

        cout << " (" << fixed << setprecision(1) << rating << "/5.0)" << endl;
    }
};


/**
 * @brief Comparator to sort restaurants from highest to lowest rating.
 */
bool compareByRating(const Restaurant& a, const Restaurant& b) {
    return a.getRating() > b.getRating();
}

/**
 * @brief Utility to clear the input buffer.
 */
void clearBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Force UTF-8 for emoji support
#endif

    vector<Restaurant> registry;
    string inputName;
    double inputRating;
    char choice;

    cout << "===============================================" << endl;
    cout << "       THE CULINARY CRITIC SYSTEM v2.0         " << endl;
    cout << "       Author: James Taylor                    " << endl;
    cout << "===============================================" << endl << endl;

    do {
        cout << "Enter Restaurant Name: ";
        getline(cin >> ws, inputName);

        while (true) {
            cout << "Enter Star Rating (0.0 - 5.0): ";
            if (cin >> inputRating && inputRating >= 0.0 && inputRating <= 5.0) {
                break;
            } else {
                cout << "[Error] Please enter a decimal between 0.0 and 5.0." << endl;
                clearBuffer();
            }
        }

        // Add to our collection
        registry.emplace_back(inputName, inputRating);

        cout << "\nReview added. Add another? (y/n): ";
        cin >> choice;
        cout << endl;

    } while (tolower(choice) == 'y');


    // Sort reviews so the best restaurants appear first
    sort(registry.begin(), registry.end(), compareByRating);

    cout << "\n--- TOP RATED ESTABLISHMENTS ---" << endl;
    cout << left << setw(20) << "RESTAURANT" << " | " << "VISUAL RATING" << endl;
    cout << "-----------------------------------------------" << endl;

    for (const auto& rest : registry) {
        rest.display();
    }

    cout << "-----------------------------------------------" << endl;
    cout << "Total Reviews Processed: " << registry.size() << endl;

    return 0;
}
