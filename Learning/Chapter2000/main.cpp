#include <iostream>

class Bob {
    
    public:
        int x {0};
        void Print() const {
            std::cout << x << '\n';
        }


};


int main() {
    Bob x {};
    x.Print();

};
