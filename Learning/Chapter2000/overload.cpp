#include <iostream>

class Boss {

    public:
        int p{0};
        Boss(int x) {
            p = x;
        }
        Boss* operator++();

};


Boss* Boss::operator++() {
    --((*this).p);
    return this;
}


int main() {

    Boss y {2};
    Boss* z = ++y;
    std::cout << (*z).p << '\n';

    return 0;
}
