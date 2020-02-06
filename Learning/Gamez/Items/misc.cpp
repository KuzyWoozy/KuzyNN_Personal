#include <iostream>

int* initPlayer(int arrows, int torches, int healthPots){
    static int items[] {arrows, torches, healthPots};
    return items;
}
void printItems(int* items) {
    for (int count{0}; count < 3; count++) {
        std::cout << *(items+count) << '\n';
    }
}
