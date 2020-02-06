#include <iostream>

void death(int *arr) {
    for (int x: arr) {
        std::cout << x << '\n';
    }
}

int main() {
    int arr[] {1,2,3};
    std::cout << sizeof(arr) << '\n';
    death(arr);

    return 0;
}
