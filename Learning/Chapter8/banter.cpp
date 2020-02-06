#include <iostream>

class die {
    private:
        static int m_x;
    public:
        die() {
        }
        
        void set(int x) {
            m_x = x;
        }

        void print() {
            std::cout << m_x << '\n';
        }

        ~die() {
            std::cout << "Annihilation!" << '\n';
        }

};

int die::m_x = 10;


int main() {
    
    die x {};
    die y {};
    y.set(30);
    x.print();
    

    return 0;
}
