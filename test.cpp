#include <iostream>
#include <vector>
#include <tuple>

#include "KuzyNN.h"
#include "FileReader.h"

extern const int batchSize;
extern const std::string inputsFile_train;
extern const std::string predictionFile_train;
extern const std::string inputsFile_test;
extern const std::string predictionFile_test;

int main() {
    FileReader::IDX inputs_train (inputsFile_train);
    FileReader::IDX prediction_train (predictionFile_train);

    FileReader::IDX inputs_test (inputsFile_test);
    FileReader::IDX prediction_test (predictionFile_test);
    
    KuzyNN::Network net {inputs_train.unit_vectorSize(), std::vector< std::tuple<int, const KuzyNN::activation::Activation&> > {std::make_tuple(30, KuzyNN::activation::LeakyRelu(0.01)), std::make_tuple(30, KuzyNN::activation::LeakyRelu(0.01)), std::make_tuple(10, KuzyNN::activation::Softmax())}, KuzyNN::cost::Log(), KuzyNN::initializer::Normal(), KuzyNN::teacher::Momentum (0.01, 0.99), 1};
    for (int lay{0};lay<1;++lay) {
    std::cout << "epoch: " << lay << '\n';
    FileReader::IDX inputs_train (inputsFile_train);
    FileReader::IDX prediction_train (predictionFile_train);

    FileReader::IDX inputs_test (inputsFile_test);
    FileReader::IDX prediction_test (predictionFile_test);


    for (int index {0}; index<(inputs_train.get_elements()/batchSize); ++index) {  
        net.train(inputs_train.read(batchSize) / 255, net.hot_encode<10>(prediction_train.read(batchSize)));
    }
    net.train(inputs_train.read(inputs_train.get_elements()%batchSize) / 255, net.hot_encode<10>(prediction_train.read(prediction_train.get_elements()%batchSize)));
    }
    net.debug_print();
    net.print();
    
    std::cout << net.predict(inputs_test.read(inputs_test.get_elements()) / 255, prediction_test.read(prediction_test.get_elements())) << '\n';
    return 0;

}

