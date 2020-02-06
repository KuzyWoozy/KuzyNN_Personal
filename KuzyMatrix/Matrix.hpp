
template<class T>
template<class D>
void Matrix<T>::rebuild(std::vector<int> shape_new) {
    shape = shape_new;

    if (container) {
        delete static_cast<std::vector<D>*>(container);
    } 
    if (shape_new.size() == 1) {
        container = new std::vector<T>(shape[0], 0);
    }
    else {
        shape_new.erase(shape_new.begin());
        container = new std::vector<Matrix<T>>(shape[0], Matrix<T> {shape_new});
    }
}

template<class T>
Matrix<T>::Matrix(std::vector<int> shape) {
    this->shape = shape; 

    if (shape.size() == 1) {
        container = new std::vector<T>(shape[0], 0); 
    }
    else if (shape.size() > 1) {
        int vector_shape {shape[0]};
        shape.erase(shape.begin());
        container = new std::vector<Matrix<T>>(vector_shape, Matrix<T> {shape});
    }
}



template<class T>
Matrix<T>::Matrix(const Matrix<T>& mat2copy) {
    if (mat2copy.shape.size() == 1) {
        rebuild<T>(mat2copy.shape);
        for (int index{0}; index<mat2copy.shape[0]; ++index) {
            this->index<T>(index) = (*static_cast<std::vector<T>*>(mat2copy.container))[index];
        }
    }
    else {
        rebuild<Matrix<T>>(mat2copy.shape);
        for (int index{0}; index<mat2copy.shape[0]; ++index) {
            this->index<Matrix<T>>(index) = (*static_cast<std::vector<Matrix<T>>*>(mat2copy.container))[index]; 
        }
    }
}


template<class T>
Matrix<T>::~Matrix() {
    if (container) {
        if (shape.size() == 1) {
            delete static_cast<std::vector<T>*>(container);
        }
        else { 
            delete static_cast<std::vector<Matrix<T>>*>(container);
        }
        container = 0;
    }
}



template<class T>
void Matrix<T>::operator=(const Matrix<T>& mat2copy) const {
    assert((shape == mat2copy.shape) && "Assign matrix operation failed [incompatable matrix shapes]");

    if (mat2copy.shape.size() == 1) {
        for (int index{0}; index<shape[0]; ++index) {
            this->index<T>(index) = (*static_cast<std::vector<T>*>(mat2copy.container))[index];
        }
    }
    else { 
        for (int index{0}; index<shape[0]; ++index) {
            this->index<Matrix<T>>(index) = (*static_cast<std::vector<Matrix<T>>*>(mat2copy.container))[index]; 
        }
    }
}


template<class T>
bool Matrix<T>::operator==(const Matrix<T>& mat2compare) const {
    if (shape.size() == 1) {
        for (int index{0}; index<shape[0]; ++index) {
            if (!(this->index<T>(index) == mat2compare.index<T>(index))) {
                return false;
            }
        }
        return true;
    }
    else {
        for (int index {0}; index<shape[0]; ++index) {
            if (!(this->index<Matrix<T>>(index) == mat2compare.index<Matrix<T>>(index))) {
                return false;
            }
        }
    }
    return true;
}

template<class T>
void Matrix<T>::Matrix::replace(const Matrix<T>& mat2copy) {

    if (mat2copy.shape.size() == 1) {
        rebuild<T>(mat2copy.shape);
        for (int index{0}; index<mat2copy.shape[0]; ++index) {
            this->index<T>(index) = (*static_cast<std::vector<T>*>(mat2copy.container))[index];
        }
    }
    else {
        rebuild<Matrix<T>>(mat2copy.shape);
        for (int index{0}; index<mat2copy.shape[0]; ++index) {
            this->index<Matrix<T>>(index) = (*static_cast<std::vector<Matrix<T>>*>(mat2copy.container))[index]; 
        }
    }
}

template<class T>
template<class D>
D& Matrix<T>::index(int index) const {
    assert(index<shape[0] && "Matrix index specified out of range!");
    return (*static_cast<std::vector<D>*>(container))[index];
}


template<class T>
template<class D>
D& Matrix<T>::index(const std::vector<int>& index_vector) const {
    assert(shape.size() >= index_vector.size() && "Invalid index dimension!");

    const Matrix<T>* element = this;
    for (int index {0}; index<(static_cast<int>(index_vector.size())-1); ++index) {
        element = &((*element).index<Matrix<T>>(index_vector[index]));
    }
     
    return element->index<D>(index_vector[index_vector.size()-1]);
}

template<class T>
void Matrix<T>::fill(const T& value) const {
    
    if (shape.size() == 1) {
        for (int index {0}; index<shape[0]; ++index) {
           
            this->index<T>(index) = value;
        }
    }
    else {
        
        for (int index{0}; index<shape[0]; ++index) {
            this->index<Matrix<T>>(index).fill(value);
        }
    }
}

template<class T>
void Matrix<T>::clip(const T& value) const {
    if (shape.size() == 1) {
        for (int index{0}; index<shape[0]; ++index) {
            if (this->index<T>(index)>value) {
                this->index<T>(index) = value;
            }
            else if (this->index<T>(index)<-value) {
                this->index<T>(index) = -value;
            }
        }
    }
    else {
        for (int index {0}; index<shape[0]; ++index) {
            this->index<Matrix<T>>(index).clip(value);
        }
    }
}

template<class T>
void Matrix<T>::inverse() const {
    if (shape.size() == 1) {
        for (int index{0}; index<shape[0]; ++index) {
            this->index<T>(index) = -this->index<T>(index);
        }
    }
    else {
        for (int index {0}; index<shape[0]; ++index) {
            this->index<Matrix<T>>(index).inverse();
        }
    }
}


template<class T>
std::vector<int> Matrix<T>::get_shape() const {
    return shape;
}

template<class T>
int Matrix<T>::get_elements() const {
    int elements {1};
    for (int index{0}; index<static_cast<int>(shape.size()); ++index) {
        elements *= shape[index];
    }
    return elements;
}



template<class T>
T Matrix<T>::sum() const {
    if (shape.size() == 1) {
        T sum {0};
        for (int index {0}; index<shape[0]; ++index) {
            sum += this->index<T>(index);
        }
        return sum;
    }
    else {
        T sum {0};
        for (int index{0}; index<shape[0]; ++index) {
            sum += this->index<Matrix<T>>(index).sum();
        }
        return sum;
    }
}

template<class T>
T Matrix<T>::max() const {
    if (shape.size() == 1) {
        T max {0};
        for (int index {0}; index<shape[0]; ++index) {
            if (this->index<T>(index) > max) {
                max = this->index<T>(index);
            }
        }
        return max;
    }
    else {
        T max {0};
        T contender;
        for (int index{0}; index<shape[0]; ++index) {
            contender = this->index<Matrix<T>>(index).max(); 
            if (contender > max) {
                max = contender;
            }
        }
        return max;
    }
}








template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& mat2add) const {
    assert(shape == mat2add.shape && "Matrix shapes do not match!"); 

    if (shape.size() == 1) {
        Matrix<T> mat2return {shape};
        for (int index{0}; index<shape[0]; ++index) {
            mat2return.index<T>(index) = this->index<T>(index) + mat2add.index<T>(index);
        }
        return mat2return; 
    }
    else {
        Matrix<T> mat2return {shape};
        for (int index {0}; index<shape[0]; ++index) {
            mat2return.index<Matrix<T>>(index) = this->index<Matrix<T>>(index) + mat2add.index<Matrix<T>>(index);
        }
        return mat2return;
    } 
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& mat2subtract) const {
    assert(shape == mat2subtract.shape && "Matrix shapes do not match!"); 

    if (shape.size() == 1) {
        Matrix<T> mat2return {shape};
        for (int index{0}; index<shape[0]; ++index) {
            mat2return.index<T>(index) = this->index<T>(index) - mat2subtract.index<T>(index);
        }
        return mat2return; 
    }
    else {
        Matrix<T> mat2return {shape};
        for (int index {0}; index<shape[0]; ++index) {
            mat2return.index<Matrix<T>>(index) = this->index<Matrix<T>>(index) - mat2subtract.index<Matrix<T>>(index);
        }
        return mat2return;
    } 
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& mat2multiply) const {
    assert(shape == mat2multiply.shape && "Matrix shapes do not match!"); 

    if (shape.size() == 1) {
        Matrix<T> mat2return {shape};
        for (int index{0}; index<shape[0]; ++index) {
            mat2return.index<T>(index) = this->index<T>(index) * mat2multiply.index<T>(index);
        }
        return mat2return; 
    }
    else {
        Matrix<T> mat2return {shape};
        for (int index {0}; index<shape[0]; ++index) {
            mat2return.index<Matrix<T>>(index) = this->index<Matrix<T>>(index) * mat2multiply.index<Matrix<T>>(index);
        }
        return mat2return;
    } 
}

template<class T>
Matrix<T> Matrix<T>::operator/(const Matrix<T>& mat2divide) const {
    assert(shape == mat2divide.shape && "Matrix shapes do not match!"); 

    if (shape.size() == 1) {
        Matrix<T> mat2return {shape};
        for (int index{0}; index<shape[0]; ++index) {
            mat2return.index<T>(index) = this->index<T>(index) / mat2divide.index<T>(index);
        }
        return mat2return; 
    }
    else {
        Matrix<T> mat2return {shape};
        for (int index {0}; index<shape[0]; ++index) {
            mat2return.index<Matrix<T>>(index) = this->index<Matrix<T>>(index) / mat2divide.index<Matrix<T>>(index);
        }
        return mat2return;
    } 
}

template<class T>
void Matrix<T>::add(const Matrix<T>& mat2add) const {
    assert(shape == mat2add.shape && "Matrix shapes do not match!");

    if (shape.size() == 1) {
        for (int index{0}; index<shape[0]; ++index) {
            this->index<T>(index) += mat2add.index<T>(index);
        }
    }
    else {
        for (int index {0}; index<shape[0]; ++index) {
            this->index<Matrix<T>>(index).add(mat2add.index<Matrix<T>>(index)); 
        }
    }
}

template<class T>
void Matrix<T>::subtract(const Matrix<T>& mat2subtract) const {
    assert(shape == mat2subtract.shape && "Matrix shapes do not match!");

    if (shape.size() == 1) {
        for (int index{0}; index<shape[0]; ++index) {
            this->index<T>(index) -= mat2subtract.index<T>(index);
        }
    }
    else {
        for (int index {0}; index<shape[0]; ++index) {
            this->index<Matrix<T>>(index).subtract(mat2subtract.index<Matrix<T>>(index)); 
        }
    }
}

template<class T>
void Matrix<T>::multiply(const Matrix<T>& mat2multiply) const {
    assert(shape == mat2multiply.shape && "Matrix shapes do not match!");

    if (shape.size() == 1) {
        for (int index{0}; index<shape[0]; ++index) {
            this->index<T>(index) *= mat2multiply.index<T>(index);
        }
    }
    else {
        for (int index {0}; index<shape[0]; ++index) {
            this->index<Matrix<T>>(index).multiply(mat2multiply.index<Matrix<T>>(index)); 
        }
    }
}

template<class T>
void Matrix<T>::divide(const Matrix<T>& mat2divide) const {
    assert(shape == mat2divide.shape && "Matrix shapes do not match!");

    if (shape.size() == 1) {
        for (int index{0}; index<shape[0]; ++index) {
            this->index<T>(index) /= mat2divide.index<T>(index);
        }
    }
    else {
        for (int index {0}; index<shape[0]; ++index) {
            this->index<Matrix<T>>(index).divide(mat2divide.index<Matrix<T>>(index)); 
        }
    }
}

template<class T>
void Matrix<T>::operator+=(const T& value) const {
    if (shape.size() == 1) {
        for (int index{0}; index<shape[0]; ++index) {
            this->index<T>(index) += value;
        }
    }
    else {
        for (int index {0}; index<shape[0]; ++index) {
            this->index<Matrix<T>>(index) += value; 
        }
    }
}

template<class T>
void Matrix<T>::operator-=(const T& value) const {
    if (shape.size() == 1) {
        for (int index{0}; index<shape[0]; ++index) {
            this->index<T>(index) -= value;
        }
    }
    else {
        for (int index {0}; index<shape[0]; ++index) {
            this->index<Matrix<T>>(index) -= value; 
        }
    }
}

template<class T>
void Matrix<T>::operator*=(const T& value) const {
    if (shape.size() == 1) {
        for (int index{0}; index<shape[0]; ++index) {
            this->index<T>(index) *= value;
        }
    }
    else {
        for (int index {0}; index<shape[0]; ++index) {
            this->index<Matrix<T>>(index) *= value; 
        }
    }
}

template<class T>
void Matrix<T>::operator/=(const T& value) const {
    if (shape.size() == 1) {
        for (int index{0}; index<shape[0]; ++index) {
            this->index<T>(index) /= value;
        }
    }
    else {
        for (int index {0}; index<shape[0]; ++index) {
            this->index<Matrix<T>>(index) /= value; 
        }
    }
}



template<class T>
Matrix<T> Matrix<T>::operator+(const T& value) const {

    if (shape.size() == 1) {
        for (int index{0}; index<shape[0]; ++index) {
            this->index<T>(index) += value;
        }
    }
    else {
        for (int index {0}; index<shape[0]; ++index) {
            this->index<Matrix<T>>(index) += value; 
        }
    }
    return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const T& value) const {

    if (shape.size() == 1) {
        for (int index{0}; index<shape[0]; ++index) {
            this->index<T>(index) -= value;
        }
    }
    else {
        for (int index {0}; index<shape[0]; ++index) {
            this->index<Matrix<T>>(index) -= value; 
        }
    }
    return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const T& value) const {

    if (shape.size() == 1) {
        for (int index{0}; index<shape[0]; ++index) {
            this->index<T>(index) *= value;
        }
    }
    else {
        for (int index {0}; index<shape[0]; ++index) {
            this->index<Matrix<T>>(index) *= value; 
        }
    }
    return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator/(const T& value) const {

    if (shape.size() == 1) {
        for (int index{0}; index<shape[0]; ++index) {
            this->index<T>(index) /= value;
        }
    }
    else {
        for (int index {0}; index<shape[0]; ++index) {
            this->index<Matrix<T>>(index) /= value; 
        }
    }
    return *this;
}


template<class T>
std::vector<T*> Matrix<T>::flatten_pointers() const {
    if (shape.size() == 2) {
        std::vector<T*> vector_new (this->get_elements());
        int iter {0};
        for (int index_y {0}; index_y<shape[0]; ++index_y) {
            for (int index_x {0}; index_x<shape[1]; ++index_x) {     
                vector_new[iter++] = &(index<T>({index_y, index_x})); 
            }
        }
        return vector_new;
    }
    else if (shape.size() > 2) {
        std::vector<T*> vector_new (this->get_elements());
        for (int index_y{0}; index_y<shape[0]; ++index_y) {
            std::vector<T*> vector_flat {this->index<Matrix<T>>(index_y).flatten_pointers()};
            for (int index_x {0}; index_x < static_cast<int>(vector_flat.size()); ++index_x) {
                vector_new[(index_y*vector_flat.size())+index_x] = vector_flat[index_x];  
            }
        }
        return vector_new; 
    }
    else {
        std::vector<T*> vector_new (shape[0]);
        for (int index{0}; index<shape[0]; ++index) {
            vector_new[index] = &this->index<T>(index);
        }
        return vector_new;
    }
}

template<class T>
void Matrix<T>::flatten() {
    if (shape.size() == 2) {
        int elems {get_elements()};
        std::vector<T>* new_container = new std::vector<T>(elems, 0);
                 
        for (int index {0}; index<shape[0]; ++index) {
            Matrix<T>& mat2process = this->index<Matrix<T>>(index);
            for (int index_secondary {0}; index_secondary<mat2process.shape[0]; ++index_secondary) {
                (*new_container)[(index*mat2process.shape[0])+index_secondary] = mat2process.index<T>(index_secondary);
            }
        }
         
        this->shape = std::vector<int> {elems};
        delete static_cast<std::vector<Matrix<T>>*>(container);
        container = new_container;
        
    }
    else if (shape.size() > 2) {
        int elems {get_elements()};
        std::vector<T>* new_container = new std::vector<T>(elems, 0);
        for (int index{0}; index<shape[0]; ++index) {
            Matrix<T>& mat2process = this->index<Matrix<T>>(index);
            mat2process.flatten();

            for (int index_secondary {0}; index_secondary<mat2process.shape[0]; ++index_secondary) {
                (*new_container)[(index*mat2process.shape[0])+index_secondary] = mat2process.index<T>(index_secondary);
            }
        }
        this->shape = std::vector<int> {elems};
        delete static_cast<std::vector<Matrix<T>>*>(container);
        container = new_container;
    }
}

template<class T>
void Matrix<T>::print() const {
    int lastElement {shape[0]-1};
    if (shape.size() == 1) {
        std::cout << "[";
        for (int index{0}; index<lastElement; ++index) {
            std::cout << this->index<T>(index) << ", ";
        };
        std::cout << this->index<T>(lastElement);
        std::cout << "]\n";
    }
    else {
        for (int index {0}; index<shape[0]; ++index) {     
            this->index<Matrix<T>>(index).print();
        }
    }
}


