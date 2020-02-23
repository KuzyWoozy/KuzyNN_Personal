
IDX::IDX(const std::string& filePath) : Reader(filePath) { 
    // Magic Number
    file.seekg(2);
    file.read(buffer, 2);
    dims = interpret<int>(buffer+1, 1);
    delete[] buffer;

    // Sizes of each dim, and matrix creation
    buffer = new char[4];
   

    shape = std::vector<int> (dims);
    
    file.read(buffer, 4);
    elements = interpret<int>(buffer, 4);
    
    for (int index {1}; index<dims; ++index) {
        file.read(buffer, 4);
        shape[index] = interpret<int>(buffer, 4);
    }
    
}  

KuzyMatrix::Matrix<double> IDX::read(const int& numberOfElements) {
    
    shape[0] = numberOfElements;
    KuzyMatrix::Matrix<double> mat (shape);
    const std::vector<double*>& mat_elements = mat.flatten_pointers();

    for (int index{0}; index<mat.get_elements(); ++index) {
        file.read(buffer, sizeof(unsigned char));
        (*mat_elements[index]) = static_cast<double>(interpret<unsigned char>(buffer, sizeof(unsigned char)));
    }

    return mat;
}

IDX::~IDX() {
    delete[] buffer;
}
