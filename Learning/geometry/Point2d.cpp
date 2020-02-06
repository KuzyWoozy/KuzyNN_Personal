#include <iostream>
#include <cmath>
#include "Point2d.h"


// Constructor
Point2d::Point2d(int x, int y) {
    m_x = x;
    m_y = y;
}

void Point2d::Print() {
    std::cout << "Point2d(" << m_x << " , " << m_y << ")\n";
}

void Point2d::Dist(Point2d &point) {
    std::cout << "Distance: " << std::sqrt(std::pow((m_x - point.m_x), 2) + std::pow((m_y - point.m_y), 2)) << '\n';
}

