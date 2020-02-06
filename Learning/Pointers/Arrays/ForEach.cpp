#include <iostream>

int main() {
    int x[] {1, 2, 3};

    for (int y{0}; y<3 ; y++) {
        std::cout << *(x+y) << '\n';
    }
    
    return 0;
}
