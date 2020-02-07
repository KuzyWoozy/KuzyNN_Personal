#pragma once

#include <tuple>
#include <vector>
#include <random>
#include <cmath>
#include <cassert>
#include <iostream>

#include "KuzyMatrix.h"


namespace KuzyNN {

namespace activation {
class Activation {
    private:
        virtual double apply_forward(const double& z) const = 0;
        virtual double apply_backward(const double& z) const = 0;

    public:
        void forward(const KuzyMatrix::Matrix<double>& z_vector) const;
        void backward(const KuzyMatrix::Matrix<double>& z_vector) const;
        virtual Activation& clone() const = 0;
        virtual ~Activation() {};
};

class Relu : public Activation {
    private:
        double apply_forward(const double& z) const override;
        double apply_backward(const double& z) const override;
    public:
        Relu() {};
        Relu& clone() const override;
};

class LeakyRelu : public Activation {
    private:
        double leaky_num;
        double apply_forward(const double& z) const override;
        double apply_backward(const double& z) const override;
    
    public:
        LeakyRelu(const double& leaky_param);
        LeakyRelu& clone() const override;
};


class TanH : public Activation {
    private:
        double apply_forward(const double& z) const override;
        double apply_backward(const double& z) const override;
    public:
        TanH() {};
        TanH& clone() const override;
};

class Sigmoid : public Activation {
    private:
        double apply_forward(const double& z) const override;
        double apply_backward(const double& z) const override;
    public:
        Sigmoid() {};
        Sigmoid& clone() const override;
};

}

namespace initializer {

class Initializer {
    protected:
        int numberOfParam;

    public:
        Initializer() {};
        Initializer(const int& numberOfParam) : numberOfParam {numberOfParam} {};
        virtual void initialize(const KuzyMatrix::Matrix<double>& mat2init) const = 0;
        virtual Initializer& init(const int& numberOfParam) const = 0;
        virtual ~Initializer() {};
};

class Normal : public Initializer {
    public:
        Normal() {};
        Normal(const int& numberOfParam) : Initializer {numberOfParam} {};
 
        void initialize(const KuzyMatrix::Matrix<double>& mat2init) const override;
        Normal& init(const int& numberOfParam) const;
};

}

namespace cost {

class Cost {
    protected:
        virtual double apply_forward(const double& output, const double& predict) const = 0;
        virtual double apply_backward(const double& output, const double& predict) const = 0;
    public:
        KuzyMatrix::Matrix<double> predict(const KuzyMatrix::Matrix<double>& output_vector, const KuzyMatrix::Matrix<double>& prediction_vector) const;
        KuzyMatrix::Matrix<double> error(const KuzyMatrix::Matrix<double>& output_vector, const KuzyMatrix::Matrix<double>& prediction_vector) const;

        virtual Cost& clone() const = 0;
        virtual ~Cost() {};

};

class MSE : public Cost {
    private:
        double apply_forward(const double& output, const double& predict) const override;
        double apply_backward(const double& output, const double& predict) const override;
    public:
        MSE& clone() const override;
};

}

namespace teacher {

class Teacher {
    protected:
        const float& stepValue;

    public:
        Teacher(const float& stepValue);
        virtual void update(const KuzyMatrix::Matrix<double>& paramWerror) const = 0;
        virtual Teacher& bind(const KuzyMatrix::Matrix<double>& mat2teach) const = 0;
        virtual ~Teacher() {};


};

class SGD : public Teacher {
    private:
        const KuzyMatrix::Matrix<double>* param {0};
        const KuzyMatrix::Matrix<double> buffer;
        SGD(const float& stepValue, const KuzyMatrix::Matrix<double>& mat2teach);

    public:
        SGD(const float& stepValue);
        void update(const KuzyMatrix::Matrix<double>& paramWerror) const override;
        SGD& bind(const KuzyMatrix::Matrix<double>& mat2teach) const override;
};

class Momentum : public Teacher {
    private: 
        const float& momentum_friction;
        
        const KuzyMatrix::Matrix<double>* param {0};

        const KuzyMatrix::Matrix<double> buffer_step;
        const KuzyMatrix::Matrix<double> buffer_momentum;
        const KuzyMatrix::Matrix<double> buffer_prev;

        Momentum(const float& stepValue, const float& momentum_friction, const KuzyMatrix::Matrix<double>& mat2teach);

    public:
        Momentum(const float& stepValue, const float& momentum_friction);

        void update(const KuzyMatrix::Matrix<double>& paramWerror) const override;

        Momentum& bind(const KuzyMatrix::Matrix<double>& mat2teach) const override;
};

}

namespace regularization {

KuzyMatrix::Matrix<double> Dropout(const int& layerSize, const float& dropout_chance);

}

class Layer {
    protected:
        // Learnable Params;
        const KuzyMatrix::Matrix<double> b_vector;
        const teacher::Teacher& b_teacher;
        const KuzyMatrix::Matrix<double> w_matrix;
        const teacher::Teacher& w_teacher;

        const KuzyMatrix::Matrix<double> z_vector;
        const KuzyMatrix::Matrix<double> x_vector;
        const KuzyMatrix::Matrix<double> y_vector;

        const KuzyMatrix::Matrix<double> error_w_x;
        const KuzyMatrix::Matrix<double> error_w_b;
        const KuzyMatrix::Matrix<double> error_w_w;
        const KuzyMatrix::Matrix<double> error_w_z;
        const KuzyMatrix::Matrix<double> error_w_y;
 
        const activation::Activation& f;
        const float dropout_chance;
        // true == forward, false == backwards
        bool forward_direction {false};
        
        void z_calculate(KuzyMatrix::Matrix<double>& x_vector);

    public:
 
        Layer(const activation::Activation& f, const int& layerSize_prev, const int& layerSize_this, const initializer::Initializer& init, const teacher::Teacher& teacher, const float& dropout=1);

        virtual ~Layer();

        virtual void forward(KuzyMatrix::Matrix<double>& x_vector);
        virtual void backward(KuzyMatrix::Matrix<double>& errorWoutput);

        void print() const;
        void debug_print() const;

        KuzyMatrix::Matrix<double> get_b() const;
        KuzyMatrix::Matrix<double> get_z() const;
        KuzyMatrix::Matrix<double> get_x() const;
        KuzyMatrix::Matrix<double> get_y() const;

        KuzyMatrix::Matrix<double> get_w() const;

};


class OutputLayer : public Layer {
    private:
        const cost::Cost& cost;

    public:
        OutputLayer(const activation::Activation& f, const int& layerSize_prev, const int& layerSize_this, const initializer::Initializer& init, const cost::Cost& cost, const teacher::Teacher& teacher);
        ~OutputLayer() override; 

        void forward(KuzyMatrix::Matrix<double>& x_vector) override;
        // Will handle the cost func too!
        void backward(KuzyMatrix::Matrix<double>& expected_vector) override;
        
        double get_error(const KuzyMatrix::Matrix<double>& prediction) const;
};


class Network {
    private:
        // Keep track of the layer composition
        const int numberOfHiddenLayers;
        Layer** layers;

        void forward(KuzyMatrix::Matrix<double> input_vector);
        void backward(KuzyMatrix::Matrix<double> predictions_vector);

        double get_error(const KuzyMatrix::Matrix<double>& prediction_matrix) const;

    public:
        Network(int numberOfInputs, const std::vector<std::tuple<int, const activation::Activation&>>& design, const cost::Cost& cost, const initializer::Initializer& init, const teacher::Teacher& teacher, const float& dropout=1);
        ~Network();

        void train(const KuzyMatrix::Matrix<double>& inputs_matrix, const KuzyMatrix::Matrix<double>& predictions_matrix);
        double predict(const KuzyMatrix::Matrix<double>& inputs_matrix, const KuzyMatrix::Matrix<double>& predictions_matrix);

        void print() const;
        void debug_print() const;

        template<int X>
        KuzyMatrix::Matrix<double> hot_encode(const KuzyMatrix::Matrix<double>& mat2encode) const;

};


}

#include "Activation.hpp"
#include "Initializer.hpp"
#include "Layer.hpp"
#include "Cost.hpp"
#include "Teacher.hpp"
#include "Random.hpp"
#include "Regularization.hpp"
#include "Network.hpp"
#include "Config.hpp"
