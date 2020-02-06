#include <iostream>

double max(double x, double y) {
    return x > y? x:y;
}

void swap(int& x, int& y) {
    int z = x;
    x = y;
    y = z;
}


enum class Banter {
die,
fuck
};

enum class Death {
fuc
};

#include <array>


void PrintArray(std::array<int, 2> x) {
    for (int y{0}; y<x.size() ; y++) {
        std::cout << x[y] << '\n';
    }
}

int add(int x, int y) {
    return x + y;
}

double add(double x, double y) {
    return x * y;
}

#include <vector>

int main(int banter, char** banterZ) {
    
    std::vector<int> x {1,2,3};
    std::cout << x.capacity() << '\n';

    
    x.push_back(10);

    std::cout << x.size() << " " << x.capacity() << '\n';

    x.pop_back();

    std::cout << x.size() << " " << x.capacity() << '\n';

    x = {1,2,3,4,5,6,7,8,9,10};
    
    std::cout << x.size() << " " << x.capacity() << '\n';

    return 0;
}
