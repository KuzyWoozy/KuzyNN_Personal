#include <iostream>
#include <string>


class Ball {
    private:
        std::string m_colour;
        double m_radius;

    public:
        Ball(double col) {
            m_colour = "black";
            m_radius = col;
        }
        Ball(const std::string& radz = "black", double rad=10) {
            m_colour = radz;
            m_radius = rad;
        }

        void Print() {
            std::cout << "Radius: " << m_radius << '\n' << "Colour: " << m_colour << '\n';
        }

};

int main() {
    Ball x {};
    Ball y {"yellow"};
    Ball z {20};

    x.Print();
    y.Print();
    z.Print();


}
