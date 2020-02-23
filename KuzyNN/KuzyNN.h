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
    public:
        virtual void forward(const KuzyMatrix::Matrix<double>& z_vector) const = 0;
        virtual void backward(const KuzyMatrix::Matrix<double>& z_vector) const = 0;
        virtual Activation& clone() const = 0;
        virtual ~Activation() {};
};

class Relu : public Activation {
    public:
        void forward(const  KuzyMatrix::Matrix<double>& z_vector) const override;
        void backward(const KuzyMatrix::Matrix<double>& z_vector) const override;

        Relu() {};
        Relu& clone() const override;
};

class LeakyRelu : public Activation {
    private:
        double leaky_num;
            
    public:
        void forward(const KuzyMatrix::Matrix<double>& z_vector) const override;
        void backward(const KuzyMatrix::Matrix<double>& z_vector) const override;

        LeakyRelu(const double& leaky_param);
        LeakyRelu& clone() const override;
};


class TanH : public Activation {
    public:
        void forward(const KuzyMatrix::Matrix<double>& z_vector) const override;
        void backward(const KuzyMatrix::Matrix<double>& z_vector) const override;
        
        TanH() {};
        TanH& clone() const override;
};

class Sigmoid : public Activation {
    public:
        void forward(const KuzyMatrix::Matrix<double>& z_vector) const override;
        void backward(const KuzyMatrix::Matrix<double>& z_vector) const override;

        Sigmoid() {};
        Sigmoid& clone() const override;
};

class Softmax : public Activation {
    public:
        void forward(const KuzyMatrix::Matrix<double>& z_vector) const override;
        void backward(const KuzyMatrix::Matrix<double>& z_vector) const override;

        Softmax() {};
        Softmax& clone() const override;

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
        Normal& init(const int& numberOfParam) const override;
};

class Uniform : public Initializer {
    public:
        Uniform() {}
        void initialize(const KuzyMatrix::Matrix<double>& mat2initialize) const override;
        Uniform& init(const int& numberOfParam) const override;
};

class Static : public Initializer {
    public:
        Static() {};
        Static(const int& numberOfParam) : Initializer(numberOfParam) {};
        void initialize(const KuzyMatrix::Matrix<double>& mat2initialize) const override;
        Static& init(const int& numberOfParam) const override;
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

class Log: public Cost {
    private:
        double apply_forward(const double& output, const double& predict) const override;
        double apply_backward(const double& output, const double& predict) const override;
    public:
        Log& clone() const override;
};

}

namespace teacher {

class Teacher {
    protected:
        const double& stepValue;

    public:
        Teacher(const double& stepValue);
        virtual void update(const KuzyMatrix::Matrix<double>& paramWerror) const = 0;
        virtual Teacher& bind(const KuzyMatrix::Matrix<double>& mat2teach) const = 0;
        virtual ~Teacher() {};


};

class SGD : public Teacher {
    private:
        const KuzyMatrix::Matrix<double>* param;
        const KuzyMatrix::Matrix<double> buffer;
        SGD(const double& stepValue, const KuzyMatrix::Matrix<double>& mat2teach);

    public:
        SGD(const double& stepValue);
        void update(const KuzyMatrix::Matrix<double>& paramWerror) const override;
        SGD& bind(const KuzyMatrix::Matrix<double>& mat2teach) const override;
};

class Momentum : public Teacher {
    private: 
        const double& momentum;

        const KuzyMatrix::Matrix<double>* param;
        const KuzyMatrix::Matrix<double> buffer_prev;

        Momentum(const double& stepValue, const double& momentum_friction, const KuzyMatrix::Matrix<double>& mat2teach);

    public:
        Momentum(const double& stepValue, const double& momentum_friction);

        void update(const KuzyMatrix::Matrix<double>& paramWerror) const override;

        Momentum& bind(const KuzyMatrix::Matrix<double>& mat2teach) const override;
};

}

namespace regularization {

KuzyMatrix::Matrix<double> Dropout(const int& layerSize, const float& dropout_chance, const bool& training);

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

        virtual void forward(KuzyMatrix::Matrix<double>& x_vector, const bool& training);
        virtual void backward(KuzyMatrix::Matrix<double>& errorWoutput);

        void print() const;
        void debug_print() const;

        KuzyMatrix::Matrix<double> get_b() const;
        KuzyMatrix::Matrix<double> get_z() const;
        KuzyMatrix::Matrix<double> get_x() const;
        KuzyMatrix::Matrix<double> get_y() const;
        KuzyMatrix::Matrix<double> get_w() const;
        KuzyMatrix::Matrix<double> get_error_w_z() const;
        KuzyMatrix::Matrix<double> get_error_w_y() const;

};


class OutputLayer : public Layer {
    private:
        const cost::Cost& cost;

    public:
        OutputLayer(const activation::Activation& f, const int& layerSize_prev, const int& layerSize_this, const initializer::Initializer& init, const cost::Cost& cost, const teacher::Teacher& teacher);
        ~OutputLayer() override; 

        void forward(KuzyMatrix::Matrix<double>& x_vector, const bool& training) override;
        // Will handle the cost func too!
        void backward(KuzyMatrix::Matrix<double>& expected_vector) override;
        
        KuzyMatrix::Matrix<double> get_error(const KuzyMatrix::Matrix<double>& prediction) const;
        double get_avgError(const KuzyMatrix::Matrix<double>& prediction) const;
};


class Network {
    private:
        // Keep track of the layer composition
        const int numberOfHiddenLayers;
        Layer** layers;


        void forward(KuzyMatrix::Matrix<double> input_vector, const bool& training);
      
        void backward(KuzyMatrix::Matrix<double> predictions_vector);

        

    public:
        Network(int numberOfInputs, const std::vector<std::tuple<int, const activation::Activation&>>& design, const cost::Cost& cost, const initializer::Initializer& init, const teacher::Teacher& teacher, const float& dropout=1);
        ~Network();

        double get_error(const KuzyMatrix::Matrix<double>& input_vector, const KuzyMatrix::Matrix<double>& prediction_vector);

        void train(const KuzyMatrix::Matrix<double>& inputs_matrix, const KuzyMatrix::Matrix<double>& predictions_matrix);
        double predict(const KuzyMatrix::Matrix<double>& inputs_matrix, const KuzyMatrix::Matrix<double>& predictions_matrix);

        void print() const;
        void debug_print() const;
        void derivitive_print() const;

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
