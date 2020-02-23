#pragma once

#include <iostream>
#include <vector>
#include <cassert>

namespace KuzyMatrix {
    template<class T>
    class Matrix {
        private:
            std::vector<int> shape {0};
            void* container {0};

            template<class D>
            void rebuild(std::vector<int> shape_new);

        public:
            // Constructors and Destructors
            Matrix() {};
            Matrix(std::vector<int> shape);
            Matrix(const Matrix<T>&);
            ~Matrix();
           
            // Comparsion and assignment
            void operator=(const Matrix<T>&) const;
            bool operator==(const Matrix<T>&) const;
            void replace(const Matrix<T>&);

            // Indexing
            template<class D>
            D& index(int index) const;
            template<class D>
            D& index(const std::vector<int>&) const;

            // Container operations
            void fill(const T& value) const;
            void clip(const T& value) const;
            void inverse() const;

            // Getters
            std::vector<int> get_shape() const;
            int get_elements() const;


            // Math
            T sum() const;
            T max() const;
            std::vector<int> max_index() const;
            Matrix<T> operator+(const Matrix<T>& mat2add) const;
            Matrix<T> operator-(const Matrix<T>& mat2subtract) const;
            Matrix<T> operator*(const Matrix<T>& mat2multiply) const;
            Matrix<T> operator/(const Matrix<T>& mat2divide) const;
            void add(const Matrix<T>& mat2add) const;
            void subtract(const Matrix<T>& mat2add) const;
            void multiply(const Matrix<T>& mat2add) const;
            void divide(const Matrix<T>& mat2add) const;
            void operator+=(const T& value) const;
            void operator-=(const T& value) const;
            void operator*=(const T& value) const;
            void operator/=(const T& value) const;
            Matrix<T> operator+(const T& value) const;
            Matrix<T> operator-(const T& value) const;
            Matrix<T> operator*(const T& value) const;
            Matrix<T> operator/(const T& value) const;


            // Special
            std::vector<T*> flatten_pointers() const;
            void flatten();
            void print() const;
            
           
            };


#include "Matrix.hpp"
}

