#include <iostream>
#include <string>

class Person {
   
        
    public:
        int name;
        explicit Person(int name) {
            (*this).name = name;
        }

        Person(const Person&) = delete;

};

void change(Person x) {
    std::cout << x.name << '\n';
}

int main() {
    Person x{10};
    change(x);
    
    return 0;
}
