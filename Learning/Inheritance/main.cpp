#include <iostream>

class A {
    protected:
        int a;
    public:
        A(int x=0){
            a=x;
        };
        int getA() {
            return a;    
        }
};

class B: public A {
    private:
        int b;

    public:
        B(int x=-10, int y=30): b{x} {}
        int getB() {
            return b;
        }
};


int main () {

    B y {20, 50};
    
    std::cout << " " << y.getA() <<'\n';
    
    return 0;

}
