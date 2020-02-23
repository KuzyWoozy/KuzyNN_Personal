#include "KuzyMatrix.h"
#include <vector>

namespace KuzyConv {

    class Kernel {
        private:
            const int& stride;
            const std::vector<int>& size;
            const KuzyMatrix::Matrix<double> kernel_mat;
        public:
            Kernel(const int& stride, const std::vector<int>& size);
            void apply(const KuzyMatrix::Matrix<double>& x);
            void learn(const KuzyMatrix::Matrix<double>& x, const double& error_w_y) const;
             
    };

    class Layer {
        private:
            const Kernel& kernel;
            KuzyMatrix::Matrix<double> x_matrix;
        public:
            Layer(kernel);
            void forward(const KuzyMatrix::Matrix<double>& x_matrix);
            void backward(const KuzyMatrix::Matrix<double>& x_matrix, const KuzyMatrix::Matrix<double>& error_w_y);
            ~Layer();
    };

    class MaxPool {
        private:
            const std::vector<int>& size;
        public:
            void apply(const KuzyMatrix::Matrix<double>& x_matrix);
    };

    #include "Kernel.hpp"
    #include "Layer.hpp"
    #include "Pool.hpp" 
}
