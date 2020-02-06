#include <iostream>

template<typename T>
T max(T x, T y) {
    return x > y ? x: y;
}

// Overriding the template function
template<typename T>
T min(T x, T y) {
    return x < y ? x: y;
}


int main() {
    try {
    std::cout << min(10,12) << '\n';
    std::cout << max(10,12) << '\n';
    throw -1;
    }
    catch (int x) {
        std::cout << "An error ahs occured u fucking idiot\n";
    }
    return 0;
}
