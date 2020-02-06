#include <fstream>
#include <cassert>
#include <iostream>

template<class Data>
Data interpret(char* buffer, int buffer_elements) {
    assert(sizeof(Data) == (buffer_elements) && "Invalid data sizes");
    
    Data return_data {0};
    for (int index {0}; index<buffer_elements; ++index) {
        return_data |= (static_cast<unsigned char>(*(buffer+index)) << ((buffer_elements-index-1) * 8)); 
    }

    return return_data;
}

int main() {
    
    char buffer[4];
    std::ifstream file ("train-labels-idx1-ubyte");
    file.seekg(4);
    file.read(buffer, 4);

    std::cout << file.tellg()<< '\n';
    return 0;
}
