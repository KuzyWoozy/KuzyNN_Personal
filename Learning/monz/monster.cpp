#include <iostream>
#include "monster.h"

Monster::Monster(Monster::Type type, char* roar, int health) {
    monsterType = type;
    (*this).roar = roar;
    (*this).health = health;
}

void Monster::Roar() const {
    std::cout << monsterType;
    std::cout << ' ';
    int acc{0};
    while (*(roar+acc)) {
        std::cout << *(roar + acc++);
    }
    std::cout << ' ';
    std::cout << health;
    std::cout << '\n';

}
