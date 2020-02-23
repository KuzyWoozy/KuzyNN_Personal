
void KuzyNN::Layer::z_calculate(KuzyMatrix::Matrix<double>& x_vector) {
    assert((w_matrix.get_shape()[1] == x_vector.get_shape()[0]) && "Weights and input do not match!");
    KuzyMatrix::Matrix<double> y_vector {b_vector.get_shape()};
    for (int index{0}; index<b_vector.get_shape()[0]; ++index) {
        y_vector.index<double>(index) = ((w_matrix.index<KuzyMatrix::Matrix<double>>(index) * x_vector).sum() + b_vector.index<double>(index));
    }
    x_vector.replace(y_vector);
}

KuzyNN::Layer::Layer(const KuzyNN::activation::Activation& func, const int& layerSize_prev, const int& layerSize_this, const KuzyNN::initializer::Initializer& weightInit, const teacher::Teacher& teacher, const float& dropout) : b_vector {{layerSize_this}}, b_teacher {teacher.bind(b_vector)}, w_matrix {{layerSize_this, layerSize_prev}}, w_teacher {teacher.bind(w_matrix)}, z_vector {{layerSize_this}}, x_vector {{layerSize_prev}}, y_vector {{layerSize_this}},error_w_x {{layerSize_prev}}, error_w_b {{layerSize_this}}, error_w_w {{layerSize_this, layerSize_prev}}, error_w_z {{layerSize_this}}, error_w_y {{layerSize_this}}, f{func}, dropout_chance {dropout}{
    weightInit.initialize(w_matrix);
    
    delete &weightInit;
}

KuzyNN::Layer::~Layer() {
    delete &f;
    delete &b_teacher;
    delete &w_teacher;
}

void KuzyNN::Layer::forward(KuzyMatrix::Matrix<double>& x_vector, const bool& training) {
    assert(x_vector.get_shape()[0] == w_matrix.get_shape()[1] && "Invalid input shape for Z calculation!");
    this->x_vector = x_vector;
    z_calculate(x_vector);
    this->z_vector = x_vector;
    f.forward(x_vector);
    x_vector.multiply(KuzyNN::regularization::Dropout(b_vector.get_shape()[0], dropout_chance, training));
    this->y_vector = x_vector;

    forward_direction=true;
}

void KuzyNN::Layer::backward(KuzyMatrix::Matrix<double>& errorWoutput_vector) {
    assert(forward_direction && "Forward propogate first!");
    
    error_w_y = errorWoutput_vector;

    KuzyMatrix::Matrix<double> z_vector {this->z_vector};
    f.backward(z_vector);
    
    // Error with respect to z
    error_w_z = z_vector * error_w_y;

    KuzyMatrix::Matrix<double> buffer_y_vector {{w_matrix.get_shape()[0]}};
    for (int index_x{0}; index_x<w_matrix.get_shape()[1]; ++index_x) {
        for (int index_y{0}; index_y<w_matrix.get_shape()[0]; ++index_y) {
            buffer_y_vector.index<double>(index_y) = w_matrix.index<double>({index_y, index_x});
        }
        error_w_x.index<double>(index_x) = (buffer_y_vector * error_w_z).sum();
    }
    errorWoutput_vector.replace(error_w_x);

    // Update bias
    error_w_b = error_w_z;
    b_teacher.update(error_w_b);
    // Update weights
    for (int index{0}; index<w_matrix.get_shape()[0]; ++index) {
        error_w_w.index<KuzyMatrix::Matrix<double>>(index) = x_vector * error_w_z.index<double>(index);
    }
    w_teacher.update(error_w_w);
    forward_direction=false;
}

void KuzyNN::Layer::print() const {
    std::cout << "Input:\n";
    x_vector.print();
    std::cout << "\nWeights:\n";
    w_matrix.print();
    std::cout << "\nBias:\n";
    b_vector.print();
    std::cout << "\nZ:\n";
    z_vector.print();
    std::cout << "\nOutput:\n";
    y_vector.print();
    std::cout << "--------------------\n";
}

void KuzyNN::Layer::debug_print() const { 
    std::cout << "error_w_weight\n"; 
    error_w_w.print();
    std::cout << "error_w_input\n";
    error_w_x.print();
    std::cout << "error_w_bias\n";
    error_w_b.print();
    std::cout << "error_w_z\n";
    error_w_z.print();
    std::cout << "error_w_output\n";
    error_w_y.print();
}


KuzyMatrix::Matrix<double> KuzyNN::Layer::get_b() const {
    return b_vector;
}

KuzyMatrix::Matrix<double> KuzyNN::Layer::get_x() const {
    return x_vector;
}

KuzyMatrix::Matrix<double> KuzyNN::Layer::get_w() const {
    return w_matrix;
}

KuzyMatrix::Matrix<double> KuzyNN::Layer::get_y() const {
    return y_vector;
}

KuzyMatrix::Matrix<double> KuzyNN::Layer::get_z() const {
    return z_vector;
}

KuzyMatrix::Matrix<double> KuzyNN::Layer::get_error_w_z() const {
    return error_w_z;
}

KuzyMatrix::Matrix<double> KuzyNN::Layer::get_error_w_y() const {
    return error_w_y;
}


KuzyNN::OutputLayer::OutputLayer(const KuzyNN::activation::Activation& func, const int& layerSize_prev, const int& layerSize_this, const KuzyNN::initializer::Initializer& initializer, const KuzyNN::cost::Cost& cost, const teacher::Teacher& teacher) : Layer(func, layerSize_prev, layerSize_this, initializer, teacher), cost {cost} {};


KuzyNN::OutputLayer::~OutputLayer() {
    delete &cost;
}

void KuzyNN::OutputLayer::forward(KuzyMatrix::Matrix<double>& x_vector, const bool& training) {
    assert(x_vector.get_shape()[0] == w_matrix.get_shape()[1] && "Invalid input shape for Z calculation!");
    this->x_vector = x_vector;
    z_calculate(x_vector);
    this->z_vector = x_vector;
    f.forward(x_vector);
    
    this->y_vector = x_vector;
    forward_direction=true;
}

void KuzyNN::OutputLayer::backward(KuzyMatrix::Matrix<double>& predictions_vector) {
    predictions_vector = cost.error(y_vector, predictions_vector);
    KuzyNN::Layer::backward(predictions_vector);
}


KuzyMatrix::Matrix<double> KuzyNN::OutputLayer::get_error(const KuzyMatrix::Matrix<double>& predictions_vector) const {
    return cost.predict(y_vector, predictions_vector);
}

double KuzyNN::OutputLayer::get_avgError(const KuzyMatrix::Matrix<double>& predictions_vector) const {
    return get_error(predictions_vector).sum()/get_error(predictions_vector).get_shape()[0];
}


