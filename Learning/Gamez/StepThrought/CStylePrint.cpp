#include <iostream>

int main() {
    char z[] {"Hi my name is bob"};
    
    char *x = z;

    while (*x != '\0') {
        std::cout << *x << '\n';
        x++;
    }

    return 0;
}
