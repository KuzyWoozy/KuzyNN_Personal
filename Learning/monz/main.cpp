#include "monster.h"


int main() {
    char x[] {"rawr"};
    Monster mon {Monster::DRAGON, x, 100};

    mon.Roar();

}
