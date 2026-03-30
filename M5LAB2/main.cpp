// CSC 134
// James Taylor
// 03-30-26
// M5LAB2
// Fix it

#include <iostream>
using namespace std;

double getLength();
double getWidth();
double getArea(double length, double width);
void displayData(double length, double width, double area);

int main()
{
   double length, width, area;

   length = getLength();
   width = getWidth();
   area = getArea(length, width);
   displayData(length, width, area);

   return 0;
}


double getLength()
{
   double len;
   cout << "Enter the rectangle's length: ";
   cin >> len;
   return len;
}

double getWidth()
{
   double w;
   cout << "Enter the rectangle's width: ";
   cin >> w;
   return w;
}

double getArea(double length, double width)
{
   return length * width;
}

void displayData(double length, double width, double area)
{
   cout << "\nRectangle Data" << endl;
   cout << "--------------" << endl;
   cout << " Length :" << length << endl;
   cout << " Width  :" << width << endl;
   cout << " Area   :" << area << endl;
}

