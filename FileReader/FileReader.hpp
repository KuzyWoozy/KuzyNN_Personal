
Reader::Reader(const std::string& filePath) : file (filePath) {}

template<class Data>
Data Reader::interpret(char* buffer, const int& buffer_elements) const {
    assert((static_cast<int>(sizeof(Data)) >= buffer_elements) && "incompatible byte sizes");
    
    Data return_data {0};
    for (int index {0}; index<buffer_elements; ++index) {
        return_data |= (static_cast<unsigned char>(*(buffer+index)) << ((buffer_elements-index-1) * 8)); 
    }
    return return_data;
}

Reader::~Reader() {
    file.close();
}

void Reader::reset() {
    file.seekg(0);
}

int Reader::unit_vectorSize() const {
    int size {1};
    for (int index{1}; index<static_cast<int>(shape.size()); ++index) {
         size *= shape[index];
    }
    return size;
}

int Reader::get_elements() const {
    return elements;
}

