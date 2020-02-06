#include <iostream>

int main() {
    int x{100};
    void *point {&x};
    
    char *pointerInt {static_cast<char*>(point)};
    std::cout << *pointerInt << '\n';

    return 0;
}
