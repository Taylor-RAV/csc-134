#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
private:
    double width;
    double length;
public:
    void setWidth(double w) { width = w; }
    void setLength(double l) { length = l; }
    double getWidth() const { return width; }
    double getLength() const { return length; }
    double getArea() const { return width * length; }
};

#endif
