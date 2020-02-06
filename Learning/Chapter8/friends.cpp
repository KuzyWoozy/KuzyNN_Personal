#include <iostream>

class Friendly {
    private:
        int lol {10};
    public:
        void run() {
            std::cout << this << "Die Die Die!\n";
        }
        friend void print(Friendly &x);
};

void print(Friendly &x){
    std::cout<< x.lol << '\n';
}


int main() {
    Friendly x {};

    x.run();


    print(x);

    return 0;
}
