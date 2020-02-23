#include <cassert>
#include <string>
#include <iostream>


template<class T>
void KuzyArray::Matrix<T>::rebuild(const int& length_yNew, const int& length_xNew, KuzyArray::Vector<T>* container_new) {
    length_y = length_yNew;
    length_x = length_xNew;
    delete[] container;
    container = container_new;
}

template<class T>
KuzyArray::Matrix<T>::Matrix() {
    this->length_y = 0;
    this->length_x = 0;
    container = 0;
};

template<class T>
KuzyArray::Matrix<T>::Matrix(const int& length_y, const int& length_x) {
    assert((length_y>0) && (length_x>0) && "Matrix shape below zero! [invalid shape specified]");
    this->length_y = length_y;
    this->length_x = length_x;
    
    container = new KuzyArray::Vector<T>[length_y];
    for (int index{0}; index<length_y; ++index) { 
        (*this)[index] = KuzyArray::Vector<T>{length_x};      
    }
}

template<class T>
KuzyArray::Matrix<T>::Matrix(const KuzyArray::Matrix<T>& mat2copy) {
    length_y = mat2copy.length_y;
    length_x = mat2copy.length_x;

    container = new KuzyArray::Vector<T>[length_y];
    for (int index{0}; index<length_y; ++index) {
        (*this)[index] = mat2copy[index];
    }
}

template<class T>
KuzyArray::Matrix<T>::Matrix(const Vector<T>& vector2expand, const int& length_yNew, const int& length_xNew) {
    assert(((vector2expand.getLength() == length_yNew) || (vector2expand.getLength() == length_xNew)) && "Neither cols or rows match! [no matching shape]");

    length_y = length_yNew;
    length_x = length_xNew;
    container = new Vector<T>[length_yNew]; 

    if (vector2expand.getLength() == length_yNew) {
        for (int index{0}; index<length_yNew; ++index) {
            Vector<T> vector_new {length_xNew};
            vector_new.fill(vector2expand[index]);
            (*this)[index] = vector_new;
        }
    }
    else if (vector2expand.getLength() == length_xNew) {
        for (int index{0}; index<length_yNew; ++index) {
            (*this)[index] = Vector<T> {vector2expand};
        }
    }
}


template<class T>
KuzyArray::Matrix<T>::~Matrix() { 
    delete[] container;
}

template<class T>
KuzyArray::Vector<T>& KuzyArray::Matrix<T>::operator[](int index) const {
    assert((index<length_y) && ((index+length_y)>=0) && "Insert specified out of bounds");
    return *(container+(index>=0 ? index: (index+length_y))); 
}

template<class T>
bool KuzyArray::Matrix<T>::operator==(const KuzyArray::Matrix<T>& mat2compare) const {
    if ((length_y!=mat2compare.length_y) || (length_x!=mat2compare.length_x)) {
        return false;
    }
    for (int index{0}; index<length_y; ++index) {
        if (!((*this)[index]==mat2compare[index])) {
            return false;
        }
    }
    return true;
}

template<class T>
void KuzyArray::Matrix<T>::operator=(const KuzyArray::Matrix<T>& mat2assign) {
    
    KuzyArray::Vector<T>* container_new = new KuzyArray::Vector<T>[mat2assign.getLengthY()];
    
    for (int index{0}; index<mat2assign.getLengthY(); ++index) {
        *(container_new+index) = mat2assign[index];
    }

    rebuild(mat2assign.getLengthY(), mat2assign.getLengthX(), container_new);
}

template<class T>
void KuzyArray::Matrix<T>::negative() const {
    for (int index{0}; index<length_y; ++index) {
        (*this)[index].negative();
    }
}

template<class T>
int KuzyArray::Matrix<T>::getLengthY() const {
    return length_y;
} 

template<class T>
int KuzyArray::Matrix<T>::getLengthX() const {
    return length_x;
}

template<class T>
T& KuzyArray::Matrix<T>::iter() const {
    static int index_y {0};
    static int index_x {0};

    if (index_x==length_x) {
        index_x = 0;
        ++index_y;
    }

    ++index_x;
    
    index_y = (index_y==length_y) ? 0 : index_y;
    
    return (*this)[index_y].iter();
}


template<class T>
void KuzyArray::Matrix<T>::print() const {
    for (int index{0}; index<length_y; ++index) {
        (*this)[index].print();
    }
}

template<class T>
KuzyArray::Matrix<T> KuzyArray::Matrix<T>::cut(const int& start_y, const int& end_y, const int& start_x, const int& end_x) {
    assert(
    (start_y<end_y) && (start_x<end_x)
    && (start_y>=0 && end_y<length_y) && (start_x>=0 && end_x<length_x)
    && "Matrix cutting error [insert painful screaming]");

    int matrix_cut_lengthY {end_y-start_y+1};
    int matrix_cut_lengthX {end_x-start_x+1};

    KuzyArray::Matrix<T> matrix_cut {matrix_cut_lengthY, matrix_cut_lengthX};

    for (int index{0}; index<matrix_cut_lengthY; ++index) {
         matrix_cut[index] = (*this)[index+start_y].cut(start_x, end_x);
    }
    
    return matrix_cut;
}

template<class T>
KuzyArray::Vector<T> KuzyArray::Matrix<T>::flatten() {
    int vector_length {length_y * length_x};
    KuzyArray::Vector<int> vector2return {vector_length};    
    
    for (int index{0}; index<vector_length; ++index) {
        vector2return[index] = (*this).iter();
    }

    return vector2return;
}


template<class T>
void KuzyArray::Matrix<T>::reshape(const int& length_yNew, const int& length_xNew) {
    assert(((length_yNew * length_xNew) == (length_x * length_y)) && (length_yNew>0) && (length_xNew>0) && "Reshape arg error");
    
    Vector<T>* container_new = new Vector<T>[length_yNew];

    for (int index_y{0}; index_y<length_yNew; ++index_y) {
        Vector<T> vector_new {length_xNew};
        for (int index_x{0}; index_x<length_xNew; ++index_x) {
            vector_new[index_x] = iter();
        }
        *(container_new+index_y) = vector_new;
    }

    rebuild(length_yNew, length_xNew, container_new);
}

template<class T>
void KuzyArray::Matrix<T>::transpose() {
    Vector<T>* container_new = new Vector<T>[length_x];
    for (int index_y{0}; index_y<length_x; ++index_y) {
        Vector<T> vector_new {length_y};
        for (int index_x{0}; index_x<length_y; ++index_x) {
            vector_new[index_x] = (*this)[index_x][index_y];
        }
        *(container_new+index_y) = vector_new;
    }
    rebuild(length_x, length_y, container_new);
}


template<class T>
void KuzyArray::Matrix<T>::fill(const T& value) const {
    for (int index{0}; index<length_y; ++index) {
        (*this)[index].fill(value);
    }
}

template<class T>
void KuzyArray::Matrix<T>::clip(const T& clip_value) const {
    for (int index{0}; index<length_y; ++index) {
        (*this)[index].clip(clip_value);
    }
}

template<class T>
T KuzyArray::Matrix<T>::sum() const {
    T sum {0};
    for (int index{0}; index<length_y; ++index) {
        sum+=(*this)[index].sum();
    }
    return sum;
}

template<class T>
T KuzyArray::Matrix<T>::max() const {
    T biggest {0};
    T num;
    for (int index{0}; index<length_y; ++index) {
        num = (*this)[index].max();
        if (num>biggest) {
            biggest = num;
        }
    }
    return biggest;
}

template<class T>
KuzyArray::Matrix<T> KuzyArray::Matrix<T>::operator+(const KuzyArray::Matrix<T>& mat2add) const {
    assert((length_y==mat2add.length_y) && (length_x==mat2add.length_x) && "Matrix row or col mismatch [invalid shape]");

    KuzyArray::Matrix<T> new_mat {*this};
    for (int index{0}; index<length_y; ++index) {
        new_mat[index].add(mat2add[index]);
    }
    return new_mat;
}

template<class T>
KuzyArray::Matrix<T> KuzyArray::Matrix<T>::operator-(const KuzyArray::Matrix<T>& mat2subtract) const {
    assert((length_y==mat2subtract.length_y) && (length_x==mat2subtract.length_x) && "Matrix row or col mismatch [invalid shape]");

    KuzyArray::Matrix<T> new_mat {*this};
    for (int index{0}; index<length_y; ++index) {
        new_mat[index].subtract(mat2subtract[index]);
    }
    return new_mat;
}

template<class T>
KuzyArray::Matrix<T> KuzyArray::Matrix<T>::operator*(const KuzyArray::Matrix<T>& mat2multiply) const {
    assert((length_y==mat2multiply.length_y) && (length_x==mat2multiply.length_x) && "Matrix row or col mismatch [invalid shape]");

    KuzyArray::Matrix<T> new_mat {*this};
    for (int index{0}; index<length_y; ++index) {
        new_mat[index].multiply(mat2multiply[index]);
    }
    return new_mat;
}

template<class T>
KuzyArray::Matrix<T> KuzyArray::Matrix<T>::operator/(const KuzyArray::Matrix<T>& mat2divide) const {
    assert((length_y==mat2divide.length_y) && (length_x==mat2divide.length_x) && "Matrix row or col mismatch [invalid shape]");

    KuzyArray::Matrix<T> new_mat {*this};
    for (int index{0}; index<length_y; ++index) {
        new_mat[index].divide(mat2divide[index]);
    }
    return new_mat;
}


template<class T>
void KuzyArray::Matrix<T>::add(const Matrix<T>& mat2add) const {
    assert((length_y==mat2add.length_y) && (length_x==mat2add.length_x) && "Matrix row or col mismatch [invalid shape]");
    for (int index{0}; index<length_y; ++index) {
        (*this)[index].add(mat2add[index]);
    }
}

template<class T>
void KuzyArray::Matrix<T>::subtract(const Matrix<T>& mat2subtract) const {
    assert((length_y==mat2subtract.length_y) && (length_x==mat2subtract.length_x) && "Matrix row or col mismatch [invalid shape]");
    
    for (int index{0}; index<length_y; ++index) {
        (*this)[index].subtract(mat2subtract[index]);
    }
}

template<class T>
void KuzyArray::Matrix<T>::multiply(const Matrix<T>& mat2multiply) const {
    assert((length_y==mat2multiply.length_y) && (length_x==mat2multiply.length_x) && "Matrix row or col mismatch [invalid shape]");
    for (int index{0}; index<length_y; ++index) {
        (*this)[index].multiply(mat2multiply[index]);
    }
}

template<class T>
void KuzyArray::Matrix<T>::divide(const Matrix<T>& mat2divide) const {
    assert((length_y==mat2divide.length_y) && (length_x==mat2divide.length_x) && "Matrix row or col mismatch [invalid shape]");
    for (int index{0}; index<length_y; ++index) {
        (*this)[index].divide(mat2divide[index]);
    }
}


template<class T>
void KuzyArray::Matrix<T>::matmul(const Matrix<T>& mat2matmul) { 
    assert((length_x==mat2matmul.length_y) && "Matrix shape does not match with the matrix specified [invalid shape]");

    // Vector buffer
    Vector<T> vector_buffer {mat2matmul.length_x};

    Vector<T>* container_new = new Vector<T>[length_y];

    for (int index{0}; index<length_y; ++index) {
        Vector<T> vector_new {mat2matmul.length_x};
        for (int index_row{0}; index_row<mat2matmul.length_y; ++index_row) {
            vector_buffer.fill((*this)[index][index_row]); 
            vector_buffer.multiply(mat2matmul[index_row]);
            vector_new.add(vector_buffer);
        }
        *(container_new+index) = vector_new;
    }

    rebuild(length_y, mat2matmul.length_x, container_new);
}





