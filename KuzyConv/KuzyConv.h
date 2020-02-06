#pragma once
#include "KuzyArray.h"

namespace KuzyConv {
    
    class Layer {
        public:
            virtual void process(KuzyArray::Vector<KuzyArray::Matrix<double>>&) = 0;   
    };

    class Conv : public Layer {
        private:
            KuzyArray::Vector<KuzyArray::Matrix<double>> kernels;
            void applyConv(KuzyArray::Matrix<double>& matrix2convolve, const KuzyArray::Matrix<double>& kernel);
        public:
            Conv(KuzyArray::Vector<KuzyArray::Matrix<double>> kernels);
            void process(KuzyArray::Vector<KuzyArray::Matrix<double>>&) override;
    };

    class poolMax222 : public Layer {
        private:
            void pool(KuzyArray::Matrix<double>& mat2pool);
        public:
            poolMax222();
            void process(KuzyArray::Vector<KuzyArray::Matrix<double>>&) override;
    };
    
    class AFunc : public Layer {
        private:
            double (*activationFunc)(double);
            void activate(KuzyArray::Matrix<double>& mat2activate);
        public:
            AFunc(double (*activateFunc)(double));
            void process(KuzyArray::Vector<KuzyArray::Matrix<double>>&) override;   
    };
    

    void pad(KuzyArray::Matrix<double>& mat2pad, const int startY, const int startX, const int lengthY_new, const int lengthX_new);

}

#include "KuzyConv.hpp"
