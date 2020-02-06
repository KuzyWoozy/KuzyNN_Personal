#include <iostream>

class Point3D {
    private:
        int m_x;
        int m_y;
        int m_z;

    public:
        void print() {
            std::cout << '<' << m_x << ',' << m_y << ',' << m_z << '>' << '\n';
        }

        void setValues(int x, int y, int z) {
            m_x = x;
            m_y = y;
            m_z = z;
        }

        bool isEqual(Point3D o) {
            return ((o.m_x == m_x) && (o.m_y == m_y) && (o.m_z == m_z));
        }
};


int main() {
   
    Point3D x, y, z;
    x.setValues(10,20,30);
    y.setValues(10,20,30);
    z.setValues(20,30,40);
    
    std::cout << x.isEqual(z) << '\n';
    

    return 0;
}
