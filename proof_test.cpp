#include "KuzyNN.h"
#include "FileReader.h"

extern const std::string inputsFile_train;
extern const std::string predictionFile_train;


int main() {

    FileReader::IDX input_file (inputsFile_train);
    FileReader::IDX prediction_file (predictionFile_train);

    KuzyNN::Network net {input_file.unit_vectorSize(), std::vector< std::tuple<int, const KuzyNN::activation::Activation&> > {std::make_tuple(60, KuzyNN::activation::LeakyRelu(0.01)), std::make_tuple(60, KuzyNN::activation::LeakyRelu(0.01)), std::make_tuple(10, KuzyNN::activation::Softmax())}, KuzyNN::cost::Log (), KuzyNN::initializer::Normal (), KuzyNN::teacher::Momentum (0.001, 0.99), 0.5};
    
    KuzyMatrix::Matrix<double> x (input_file.read(1));
    KuzyMatrix::Matrix<double> y (net.hot_encode<10>(prediction_file.read(1)));

    for (int index{0}; index<100; ++index) {
        net.train(x, y); 
    }

    net.print();

    return 0;
}
