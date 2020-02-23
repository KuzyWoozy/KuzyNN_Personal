
KuzyNN::Network::Network(int previousNeurones, const std::vector<std::tuple<int, const activation::Activation&>>& design, const KuzyNN::cost::Cost& cost, const KuzyNN::initializer::Initializer& init, const KuzyNN::teacher::Teacher& teacher, const float& dropout): numberOfHiddenLayers {static_cast<int>(design.size())-1}, layers (new KuzyNN::Layer*[numberOfHiddenLayers+1])  {
    
    for (int layer_num {0}; layer_num<numberOfHiddenLayers; ++layer_num) { 
        *(layers+layer_num) = new Layer(std::get<1>(design[layer_num]).clone(), previousNeurones, std::get<0>(design[layer_num]), init.init(previousNeurones), teacher, dropout);
        previousNeurones = std::get<0>(design[layer_num]);
    }

    *(layers+numberOfHiddenLayers) = new OutputLayer(std::get<1>(design[numberOfHiddenLayers]).clone(), previousNeurones, std::get<0>(design[numberOfHiddenLayers]), init.init(previousNeurones), cost.clone(), teacher);

}

KuzyNN::Network::~Network() {
    for (int index{0}; index<=numberOfHiddenLayers; ++index) {
        delete *(layers+index);
    }
    delete[] layers;
}

void KuzyNN::Network::forward(KuzyMatrix::Matrix<double> input_vector, const bool& training) {
    for (int layer_num {0}; layer_num<=numberOfHiddenLayers; ++layer_num) { 
        (*(layers+layer_num))->forward(input_vector, training);    
    }
}

void KuzyNN::Network::backward(KuzyMatrix::Matrix<double> prediction_vector) {
    for (int layer_num {numberOfHiddenLayers}; layer_num>=0; --layer_num) {
        (*(layers+layer_num))->backward(prediction_vector);    
    }
}

void KuzyNN::Network::train(const KuzyMatrix::Matrix<double>& inputs_matrix, const KuzyMatrix::Matrix<double>& predictions_matrix) {
    for (int prediction_track {0}; prediction_track<predictions_matrix.get_shape()[0]; ++prediction_track) {
        KuzyMatrix::Matrix<double>& mat = inputs_matrix.index<KuzyMatrix::Matrix<double>>(prediction_track);
        mat.flatten();
        
        std::cout << get_error(mat, predictions_matrix.index<KuzyMatrix::Matrix<double>>(prediction_track)) << '\n'; 
        forward(mat, true);
        backward(predictions_matrix.index<KuzyMatrix::Matrix<double>>(prediction_track));
    }
}

double KuzyNN::Network::predict(const KuzyMatrix::Matrix<double>& inputs_matrix, const KuzyMatrix::Matrix<double>& predictions_matrix) {
    double correct {0};
    for (int index {0}; index<predictions_matrix.get_shape()[0]; ++index) {
        KuzyMatrix::Matrix<double> mat = inputs_matrix.index<KuzyMatrix::Matrix<double>>({index});
        mat.flatten();
        forward(mat, false);
        if ((*(layers+numberOfHiddenLayers))->get_y().max_index()[0] == predictions_matrix.index<double>({index})) { 
            correct += 1; 
        }
    }
    return correct/static_cast<double>(predictions_matrix.get_shape()[0]);
}

void KuzyNN::Network::print() const {
    for (int layer_num{0}; layer_num<=numberOfHiddenLayers; ++layer_num) {
        std::cout << "Layer: " << layer_num << '\n';
        (*(layers+layer_num))->print();
    }
}

void KuzyNN::Network::debug_print() const {
    for (int layer_num{0}; layer_num<=numberOfHiddenLayers; ++layer_num) {
        std::cout << "Layer:" << layer_num << '\n';
        (*(layers+layer_num))->debug_print();
    }
}

void KuzyNN::Network::derivitive_print() const {
    for (int layer_num{0}; layer_num<=numberOfHiddenLayers; ++layer_num) {
        std::cout << ((*(layers+layer_num))->get_error_w_y().sum())/(*(layers+layer_num))->get_error_w_y().get_shape()[0] << ' ';
    }
    std::cout << '\n';
}

double KuzyNN::Network::get_error(const KuzyMatrix::Matrix<double>& input_vector, const KuzyMatrix::Matrix<double>& prediction_vector) {
    forward(input_vector, false);

    int max_ind {prediction_vector.max_index()[0]};
    prediction_vector.fill(0);
    prediction_vector.index<double>({max_ind}) = 1;
    return (*dynamic_cast<KuzyNN::OutputLayer*>(*(layers+numberOfHiddenLayers))).get_avgError(prediction_vector);
}


template<int X>
KuzyMatrix::Matrix<double> KuzyNN::Network::hot_encode(const KuzyMatrix::Matrix<double>& mat2encode) const {     
    std::vector<int> new_shape = {mat2encode.get_shape()[0], static_cast<int>(X)};
    
    KuzyMatrix::Matrix<double> mat2return (new_shape);
   
    for (int index{0}; index<new_shape[0]; ++index) {
        mat2return.index<double>({index, static_cast<int>(mat2encode.index<double>(index))}) = 1.0;
    }
    
    return mat2return;
}
