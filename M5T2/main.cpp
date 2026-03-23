#include <iostream>
#include "headers.h"
// CSC 134
// M5T2
// James Taylor
// 3/23/2026

using namespace std;

int main()
{
    cout << "Number\tSquare" << endl;
     int count = 1;

    while (count <= 10) {
        int first = count;
        int second = square(first);
        cout << endl;
        print_table_line(first,second);
        count ++;

        }
    return 0;
}

