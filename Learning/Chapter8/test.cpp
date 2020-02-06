#include <iostream>

class Death{
    private:
        int x{20};

    public:
        Death() {
            std::cout << x << '\n';
        }

};


int main() {
    Death z {};
    return 0;
}
