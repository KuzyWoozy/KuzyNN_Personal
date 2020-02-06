#include <iostream>
#include <cstdint>
#include <string>


int main() {
    std::int_fast16_t numberOfNames{};
    std::cout << "How many names? ";
    std::cin >> numberOfNames;

    std::string *arr = new std::string[numberOfNames];
    for (std::int_fast16_t y{0}; y<numberOfNames; y++) {
        std::cout << "Name: ";
        std::cin >> *(arr+y);
    }

    for (std::int_fast16_t y{0}; y<numberOfNames; y++) {
        std::cout << arr[y] << '\n';
    }

    delete[] arr;
    arr = 0;
    return 0;
}
