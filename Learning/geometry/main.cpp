#include "Point2d.h"


int main() {    
    Point2d x {};
    Point2d y {3, 4};

    x.Print();
    y.Print();

    x.Dist(y);

    return 0;
}
