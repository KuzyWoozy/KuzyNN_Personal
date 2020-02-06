

KuzyNN::Network::Network(int previousNeurones, const std::vector<std::tuple<int, const activation::Activation&>>& design, const KuzyNN::cost::Cost& cost, const KuzyNN::initializer::Initializer& init, const KuzyNN::teacher::Teacher& teacher, const float& dropout): numberOfHiddenLayers {static_cast<int>(design.size())-1}, layers (new KuzyNN::Layer*[numberOfHiddenLayers+1])  {
    
    for (int layer_num {0}; layer_num<numberOfHiddenLayers; ++layer_num) { 
        *(layers+layer_num) = new Layer(std::get<1>(design[layer_num]).clone(), previousNeurones, std::get<0>(design[layer_num]), init.init((previousNeurones*std::get<0>(design[layer_num]))+std::get<0>(design[layer_num])), teacher, dropout);
        previousNeurones = std::get<0>(design[layer_num]);
    }

    *(layers+numberOfHiddenLayers) = new OutputLayer(std::get<1>(design[numberOfHiddenLayers]).clone(), previousNeurones, std::get<0>(design[numberOfHiddenLayers]), init.init((previousNeurones*std::get<0>(design[numberOfHiddenLayers]))+std::get<0>(design[numberOfHiddenLayers])), cost.clone(), teacher);

}

KuzyNN::Network::~Network() {
    delete[] layers;
}

void KuzyNN::Network::forward(KuzyMatrix::Matrix<double> input_vector) {
    for (int layer_num {0}; layer_num<=numberOfHiddenLayers; ++layer_num) { 
        (*(layers+layer_num))->forward(input_vector);    
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
        KuzyNN::Network::forward(mat);
        KuzyNN::Network::backward(predictions_matrix.index<KuzyMatrix::Matrix<double>>(prediction_track));
    }
}

double KuzyNN::Network::predict(const KuzyMatrix::Matrix<double>& inputs_matrix, const KuzyMatrix::Matrix<double>& predictions_matrix) {
    double error {0};
    for (int index {0}; index<predictions_matrix.get_shape()[0]; ++index) {
        KuzyMatrix::Matrix<double> mat = inputs_matrix.index<KuzyMatrix::Matrix<double>>(index);
        mat.flatten();
        KuzyNN::Network::forward(mat);
        error += KuzyNN::Network::get_error(predictions_matrix.index<KuzyMatrix::Matrix<double>>(index));
    }
    return error/(predictions_matrix.get_shape()[0]);
}

void KuzyNN::Network::print() const {
    for (int layer_num{0}; layer_num<=numberOfHiddenLayers; ++layer_num) {
        std::cout << "Layer: " << layer_num << '\n';
        (*(layers+layer_num))->print();
    }
}

double KuzyNN::Network::get_error(const KuzyMatrix::Matrix<double>& prediction_vector) const {
    return (*dynamic_cast<KuzyNN::OutputLayer*>(*(layers+numberOfHiddenLayers))).get_error(prediction_vector);
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
