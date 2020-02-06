#include <iostream>

int binarySearchRecursion(int* array2search, int length, int value2find) {
    static int max_c {length-1};
    static int min_c {0};

    static int max{length};
    static int min{0};

    int centreIndex {(min+((max-min)/2))};
    int centre {*(array2search+centreIndex)};

    if (centre == value2find) {
        return centreIndex;
    }
    else if (centreIndex == max_c || centreIndex == min_c) {
        std::cout << centreIndex << '\n';
        return -1;
    }
    else if (value2find < centre) {
        max = centreIndex;
    }
    else if (value2find > centre) {
        min = centreIndex;
    }
    return binarySearchRecursion(array2search, length, value2find);
}


int binarySearch(int* array2search, int length, int value2find) {

    const int max_c {length-1};
    const int min_c {0};

    int max {length};
    int min {0};

    while (true) { 
        int centreIndex {(min+((max-min)/2))};
        int centre {*(array2search+centreIndex)};
        
        
        if (centre == value2find) {
            return centreIndex;
        }
        else if (centreIndex == max_c || centreIndex == min_c) {
            return -1;
        }
        else if (value2find < centre) {
            max = centreIndex;
        }
        else if (value2find > centre) {
            min = centreIndex;
        }
    }

}


int main() {

    int array2search[10] {1,2,3,4,5,6,7,8,9,10};
    int index {binarySearchRecursion(array2search, 10, 10)};


    if (index != -1) {
        std::cout << "Value exists! It's index is " << index << '\n';
    }

    else {
        std::cout << "Value does not exist!" << '\n';
    }


    return 0;
}
