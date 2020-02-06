#include <iostream>
#include <string>

struct STUDENT {
    std::string name;
    int mark;
};

int main() {
    int studentCount;
    std::cout << "How many students? " << '\n';
    std::cin >> studentCount;
    
    STUDENT *studentsArray = new STUDENT [studentCount];
    for (int count{0}; count<studentCount; count++) {
        STUDENT x;
        std::cout << "Name: ";
        std::cin >> x.name;
        std::cout << "Grade: ";
        std::cin >> x.mark;
        *(studentsArray + count) = x;
    }
    
    for (int count{0}; count<studentCount; count++) {
        std::cout << studentsArray[count].name << studentsArray[count].mark <<'\n';
    }

    delete[] studentsArray;

    return 0;
}
