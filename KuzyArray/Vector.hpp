#include <string>
#include <iostream>
#include <cassert>


template<class T>
void KuzyArray::Vector<T>::rebuild(const int& length_new, T* container_new) {
    length = length_new;
    delete[] container;
    container = container_new;
}

template<class T>
KuzyArray::Vector<T>::Vector() {}

template<class T>
KuzyArray::Vector<T>::Vector(const int& length) {
    assert((length>0) && "Vector length below zero! [invalid shape specified]");
    this->length = length;
    container = new T[length] {0};
}

template<class T>
KuzyArray::Vector<T>::Vector(const KuzyArray::Vector<T>& vec2copy) {
    length = vec2copy.length;
    container = new T[length];
    for (int index{0}; index<length; ++index) {
        (*this)[index] = vec2copy[index];
    }
}

template<class T>
KuzyArray::Vector<T>::~Vector() {
    delete[] container;    
}

template<class T>
void KuzyArray::Vector<T>::operator=(const KuzyArray::Vector<T>& vec2copy) {
    T* container_new = new T[vec2copy.length];

    for (int index{0}; index<vec2copy.length; ++index) {
        *(container_new+index) = vec2copy[index];
    }
    rebuild(vec2copy.length, container_new);
}

template<class T>
T& KuzyArray::Vector<T>::operator[](int index) const {
    assert((index<length) && ((index+length)>=0) && "Index specified out of bounds");
    return *(container+(index>=0 ? index: (index+length)));
}

template<class T>
bool KuzyArray::Vector<T>::operator==(const KuzyArray::Vector<T>& vec2copy) const {
    if (length != vec2copy.length) {
        return false;
    }

    for (int index{0}; index<length; ++index) {
        if ((*this)[index] != vec2copy[index]) {
            return false;
        }
    }
    return true;
}

template<class T>
void KuzyArray::Vector<T>::negative() const {
    for (int index{0}; index<length; ++index) {
        (*this)[index] = -((*this)[index]);
    }
}

template<class T>
int KuzyArray::Vector<T>::getLength() const {
    return length;
}

template<class T>
T& KuzyArray::Vector<T>::iter() const {
    static int index {0};
    
    index = (index==length) ? 0 : index;

    return (*this)[index++];
}

template<class T>
void KuzyArray::Vector<T>::print() const {
    std::cout << '[';
    for (int index{0}; index<length; ++index) {
        std::cout << (*this)[index] << ',';
    }
    std::cout << "]\n";
}

template<class T>
KuzyArray::Vector<T> KuzyArray::Vector<T>::cut(const int& start, const int& end) {
    assert(
    (start<end)
    && (start >= 0 && end <= length)
    && "Vector cutting error [ouch!]");

    int vector_cut_length {end-start+1};
    KuzyArray::Vector<T> vector_cut {vector_cut_length};
    for (int index{0}; index<vector_cut_length; ++index) {
        vector_cut[index] = (*this)[index+start];
    }

    return vector_cut;
}

template<class T>
KuzyArray::Vector<T> KuzyArray::Vector<T>::slice(int index) {
    assert((index<length) && ((index+length)>=0) && "Index specified out of bounds");
    index = (index>=0) ? index : index+length;

    Vector<T> vector_return {length-index-1};
    T* container_new  = new T[index+1];
    
    for (int index_slice{0}; index_slice<=index; ++index_slice) {
        *(container_new+index_slice) = (*this)[index_slice];
    }

    for (int index_post{0}; index_post<(length-index-1); ++index_post) {
        vector_return[index_post] = (*this)[index+index_post+1];
    }

    rebuild(index+1, container_new);

    return vector_return;
}

template<class T>
void KuzyArray::Vector<T>::resize(const int& length_new) {
    assert((length_new>0) && "Vector length below zero! [invalid shape specified]");
    
    T* container_new = new T[length_new] {0};
    for (int index{0}; index<length; ++index) {
        *(container_new+index) = (*this)[index];
    }
    rebuild(length_new, container_new);
}

template<class T>
void KuzyArray::Vector<T>::append(const T& value) {
    T* container_new = new T[length+1];

    for (int index{0}; index<length; ++index) {
        *(container_new+index) = (*this)[index];
    }
    *(container_new+length) = value; 

    rebuild(++length, container_new);
}

template<class T>
void KuzyArray::Vector<T>::insert(int index, const T& value) {
    ++length;
    assert((index<length) && ((index+length)>=0) && "Index specified out of bounds");
    index = (index>=0) ? index : index+length;

    T* container_new = new T[length];
    
    for (int index_pre{0}; index_pre<index; ++index_pre) {
        *(container_new+index_pre) = (*this)[index_pre];
    }
    *(container_new+index) = value;
    for (int index_post{index}; index_post<(length-1); ++index_post) {
        *(container_new+index_post+1) = (*this)[index_post];
    }

    rebuild(length, container_new);
}


template<class T>
void KuzyArray::Vector<T>::remove(int index) {
    assert((index<length) && ((index+length)>=0) && "Index specified out of bounds");
    index = (index>=0) ? index : index+length;    
    
    T* container_new = new T[length-1];

    for (int index_pre{0}; index_pre<index; ++index_pre) {
        *(container_new+index_pre) = (*this)[index_pre];
    }
    for (int index_post{index}; index_post<(length-1); ++index_post) {
        *(container_new+index_post) = (*this)[index_post+1]; 
    }
    rebuild(--length, container_new);
}

template<class T>
T KuzyArray::Vector<T>::pop(int index) {
    assert((index<length) && ((index+length)>=0) && "Index specified out of bounds");

    index = (index>=0) ? index : index+length;    
    T returnValue {(*this)[index]};
    remove(index);
    return returnValue;
}

template<class T>
void KuzyArray::Vector<T>::fill(const T& value) const {
    for (int index{0}; index<length; ++index) {
        (*this)[index] = value;
    }
}

template<class T>
void KuzyArray::Vector<T>::clip(const T& clip_value) const {
    assert((clip_value > 0) && "Clip value needs to be a positive and greater than 0!");
    for (int index {0}; index<length; ++index) {
        if ((*this)[index]>clip_value) {
            (*this)[index] = clip_value;
        }
        else if ((*this)[index]<(-clip_value)) {
            (*this)[index] = -clip_value;
        }
    }
}

template<class T>
T KuzyArray::Vector<T>::sum() const {
    T sum {0};
    for (int index{0}; index<length; ++index) {
        sum += (*this)[index];
    }
    return sum;
}

template<class T>
T KuzyArray::Vector<T>::max() const {
    T biggest {0};
    T num;
    for (int index{0}; index<length; ++index) {
        num = (*this)[index];
        if (num>biggest) {
            biggest = num;
        }
    }
    return biggest;
}

template<class T>
KuzyArray::Vector<T> KuzyArray::Vector<T>::operator+(const KuzyArray::Vector<T>& vec2add) const {
    assert((length == vec2add.length) && "Shapes of vectors do not match!");

    KuzyArray::Vector<T> new_vec {*this};
    for (int index{0}; index<length; ++index) {
        new_vec[index] += vec2add[index];
    }
    return new_vec;
}

template<class T>
KuzyArray::Vector<T> KuzyArray::Vector<T>::operator-(const KuzyArray::Vector<T>& vec2subtract) const {
    assert((length == vec2subtract.length) && "Shapes of vectors do not match!");

    KuzyArray::Vector<T> new_vec {*this};
    for (int index{0}; index<length; ++index) {
        new_vec[index] -= vec2subtract[index];
    }
    return new_vec;
}

template<class T>
KuzyArray::Vector<T> KuzyArray::Vector<T>::operator*(const KuzyArray::Vector<T>& vec2multiply) const {
    assert((length == vec2multiply.length) && "Shapes of vectors do not match!");

    KuzyArray::Vector<T> new_vec {*this};
    for (int index{0}; index<length; ++index) {
        new_vec[index] *= vec2multiply[index];
    }
    return new_vec;
}

template<class T>
KuzyArray::Vector<T> KuzyArray::Vector<T>::operator/(const KuzyArray::Vector<T>& vec2divide) const {
    assert((length == vec2divide.length) && "Shapes of vectors do not match!");

    KuzyArray::Vector<T> new_vec {*this};
    for (int index{0}; index<length; ++index) {
        new_vec[index] /= vec2divide[index];
    }
    return new_vec;
}


template<class T>
void KuzyArray::Vector<T>::add(const KuzyArray::Vector<T>& vec2add) const {
    assert((length == vec2add.length) && "Shapes of vectors do not match!");
    for (int index{0}; index<length; ++index) {
        (*this)[index] += vec2add[index];
    }
}

template<class T>
void KuzyArray::Vector<T>::subtract(const KuzyArray::Vector<T>& vec2subtract) const {
    assert((length == vec2subtract.length) && "Shapes of vectors do not match!");
    for (int index{0}; index<length; ++index) {
        (*this)[index] -= vec2subtract[index];
    }
}

template<class T>
void KuzyArray::Vector<T>::multiply(const KuzyArray::Vector<T>& vec2multiply) const {
    assert((length == vec2multiply.length) && "Shapes of vectors do not match!");
    for (int index{0}; index<length; ++index) {
        (*this)[index] *= vec2multiply[index];
    }
}

template<class T>
void KuzyArray::Vector<T>::divide(const KuzyArray::Vector<T>& vec2divide) const {
    assert((length == vec2divide.length) && "Shapes of vectors do not match!");
    for (int index{0}; index<length; ++index) {
        (*this)[index] /= vec2divide[index];
    }
}








