
void KuzyNN::Layer::z_calculate(KuzyMatrix::Matrix<double>& x_vector) {
    KuzyMatrix::Matrix<double> y_vector {b_vector.get_shape()};
    for (int index{0}; index<b_vector.get_shape()[0]; ++index) {
        y_vector.index<double>(index) = ((w_matrix.index<KuzyMatrix::Matrix<double>>(index) * x_vector).sum() + b_vector.index<double>(index));
    }
    x_vector.replace(y_vector);
}

KuzyNN::Layer::Layer(const KuzyNN::activation::Activation& func, const int& layerSize_prev, const int& layerSize_this, const KuzyNN::initializer::Initializer& weightInit, const teacher::Teacher& teacher, const float& dropout) : b_vector {{layerSize_this}}, b_teacher {teacher.bind(b_vector)}, w_matrix {{layerSize_this, layerSize_prev}}, w_teacher {teacher.bind(w_matrix)}, z_vector {{layerSize_this}}, x_vector {{layerSize_prev}}, y_vector {{layerSize_this}}, f{func}, dropout_chance {dropout}{
    weightInit.initialize(b_vector);
    weightInit.initialize(w_matrix);
    
    delete &weightInit;
}

KuzyNN::Layer::~Layer() {
    delete &f;
    delete &b_teacher;
    delete &w_teacher;
}

void KuzyNN::Layer::forward(KuzyMatrix::Matrix<double>& x_vector) {
    assert(x_vector.get_shape()[0] == w_matrix.get_shape()[1] && "Invalid input shape for Z calculation!");
    this->x_vector = x_vector;
    z_calculate(x_vector);
    this->z_vector = x_vector;
    f.forward(x_vector);
    
    x_vector.multiply(KuzyNN::regularization::Dropout(b_vector.get_shape()[0], dropout_chance));
    this->y_vector = x_vector;

    forward_direction=true;
}

void KuzyNN::Layer::backward(KuzyMatrix::Matrix<double>& errorWoutput_vector) {
    assert(forward_direction && "Forward propogate first!");

    KuzyMatrix::Matrix<double> z_vector {this->z_vector};

    f.backward(z_vector);
    // Error with respect to z
    z_vector.multiply(errorWoutput_vector);

    KuzyMatrix::Matrix<double> errorWoutput_new_vector {{w_matrix.get_shape()[1]}};
    KuzyMatrix::Matrix<double> buffer_y_vector {{w_matrix.get_shape()[0]}};
    for (int index_x{0}; index_x<w_matrix.get_shape()[1]; ++index_x) {
        for (int index_y{0}; index_y<w_matrix.get_shape()[0]; ++index_y) {
            buffer_y_vector.index<double>(index_y) = w_matrix.index<double>({index_y, index_x});
        }
        errorWoutput_new_vector.index<double>(index_x) = (buffer_y_vector * z_vector).sum();
    }
    errorWoutput_vector.replace(errorWoutput_new_vector);

    // Update bias
    b_teacher.update(z_vector);
    // Update weights
    KuzyMatrix::Matrix<double> wWerror_matrix {w_matrix.get_shape()};
    KuzyMatrix::Matrix<double> buffer_x_vector {{w_matrix.get_shape()[1]}};
    for (int index{0}; index<w_matrix.get_shape()[0]; ++index) {
        buffer_x_vector.fill(z_vector.index<double>(index));
        wWerror_matrix.index<KuzyMatrix::Matrix<double>>(index) = x_vector * buffer_x_vector;
    }
    w_teacher.update(wWerror_matrix);
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

KuzyNN::OutputLayer::OutputLayer(const KuzyNN::activation::Activation& func, const int& layerSize_prev, const int& layerSize_this, const KuzyNN::initializer::Initializer& initializer, const KuzyNN::cost::Cost& cost, const teacher::Teacher& teacher) : Layer(func, layerSize_prev, layerSize_this, initializer, teacher), cost {cost} {};


KuzyNN::OutputLayer::~OutputLayer() {
    delete &cost;
}

void KuzyNN::OutputLayer::forward(KuzyMatrix::Matrix<double>& x_vector) {
    assert(x_vector.get_shape()[0] == w_matrix.get_shape()[1] && "Invalid input shape for Z calculation!");
    this->x_vector = x_vector;
    z_calculate(x_vector);
    this->z_vector = x_vector;
    f.forward(x_vector);
    
    this->y_vector = x_vector;
    forward_direction=true;
}

void KuzyNN::OutputLayer::backward(KuzyMatrix::Matrix<double>& predictions_vector) {
    // Error with respect to z 
    predictions_vector = cost.error(y_vector, predictions_vector);
    KuzyNN::Layer::backward(predictions_vector);
}

double KuzyNN::OutputLayer::get_error(const KuzyMatrix::Matrix<double>& predictions_vector) const {
    return cost.predict(y_vector, predictions_vector).sum()/(b_vector.get_shape()[0]);
}
