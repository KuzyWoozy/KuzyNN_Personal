#include <iostream>

class A {
    public:
    virtual ~A() {
        std::cout << "A" << '\n';
    }

};

class B : A{
    public:
    virtual ~B() {
        std::cout << "B" << '\n';
    }
};


int main() {
    B* x = new B{};
    A b {x};
    delete &b;

    return 0;
}
