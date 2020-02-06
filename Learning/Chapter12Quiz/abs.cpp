#include <iostream>

std::ostream& operator<<(std::ostream& stream, const Shape& out) {
    
}

class Shape {
    public:
        virtual std::ostream& print(std::ostream&) = 0;
        friend std::ostream& operator<<(std::ostream& stream, const Shape& out) {
            return out.print(stream);
        };
        virtual ~Shape();
};


class Point final{
    private:
        int m_x = 0;
        int m_y = 0;
        int m_z = 0;
 
    public:
        Point(int x, int y, int z): m_x(x), m_y(y), m_z(z) {}
 
        std::ostream& operator<<(std::ostream &out, const Point &p) {
            out << "Point(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ")";
            return out;
        }
};


class Circle final: public Shape {
    private:
        int radius;
        Point centre;
    public:
        Circle(Point centre, int radius) {
            (*this).centre = centre;
            (*this).radius = radius;
        }
        virtual std::ostream& print(std::ostream& out) override {
            out << centre << "radius: " << radius;
            return out;
        }

};
/*
class Triangle final: Shape {
    private:
        Point edge1;
        Point edge2;
        Point edge3;
    public:
        Triangle(const Point edge1, const Point edge2, const Point edge3) {
            (*this).edge1 = edge1;
            (*this).edge2 = edge2;
            (*this).edge3 = edge3;
        }
};
*/
int main()
{
    Circle c(Point(1, 2, 3), 7);
    std::cout << c << '\n';

    //Triangle t(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9));
    //std::cout << t << '\n';

    return 0;
}
