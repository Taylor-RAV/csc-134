
/**
 * @file Rectangle.h
 * @author James Taylor
 * @brief Gold Tier - Rectangle Class Specification and Implementation
 * Includes input validation to prevent zero or negative dimensions.
 * @date 2026-05-08
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>

class Rectangle {
private:
    double width;
    double length;

public:
    /**
     * @brief Default constructor initializing dimensions to 1.0.
     */
    Rectangle() {
        width = 1.0;
        length = 1.0;
    }

    /**
     * @brief Sets the rectangle width with validation.
     * @param w The width value to set.
     */
    void setWidth(double w) {
        if (w > 0) {
            width = w;
        } else {
            std::cout << "Invalid width. Defaulting to 1.0.\n";
            width = 1.0;
        }
    }

    /**
     * @brief Sets the rectangle length with validation.
     * @param l The length value to set.
     */
    void setLength(double l) {
        if (l > 0) {
            length = l;
        } else {
            std::cout << "Invalid length. Defaulting to 1.0.\n";
            length = 1.0;
        }
    }

    /**
     * @brief Gets the current width.
     * @return double The width.
     */
    double getWidth() const {
        return width;
    }

    /**
     * @brief Gets the current length.
     * @return double The length.
     */
    double getLength() const {
        return length;
    }

    /**
     * @brief Calculates the area of the rectangle.
     * @return double The area (width * length).
     */
    double getArea() const {
        return width * length;
    }
};

#endif
