#include <initializer_list>
#include <iostream>

class print {
    public:
        print(const std::initializer_list<int> &arr) {
            for (int x : arr) {
                std::cout << x << '\n';
            }
        }
        void operator=(const std::initializer_list<int> &arr) {
            for (int x: arr) {
                std::cout << x << '\n';
            }
        }
    

};

void lul(const std::intializer_list<int> &arr) {
    for (x : arr) {
        std::cout << x << '\n';
    }
}

int main() {
    lul({1,2,3});
    return 0;
}
