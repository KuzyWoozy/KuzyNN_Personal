#include <iostream>
#include <fstream>

int main() {

    std::ifstream file ("banter.txt", std::ifstream::binary);
    char binary[1]; 
    file.seekg(1);
    file.read(binary, 1);

    std::cout << *binary << '\n';
    file.close(); 
    return 0;
}
