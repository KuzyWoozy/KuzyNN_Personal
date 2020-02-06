#include <iostream>

namespace Die {
    void Print(char* x) {
        int count{0};
        while (*(x + count) != '\0') {    
            std::cout << *(x + count++);
        }
        std::cout << '\n';
    }
}

