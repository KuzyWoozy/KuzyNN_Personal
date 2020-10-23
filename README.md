

# Kuzy's C++ NN

## Summary:
Please see test.cpp for example of setting up the NN.
Settings for test.cpp be adjusted via KuzyNN/Config.hpp

A toy project which focuses on implementing feed-forward neural networks without any external depencies in C++. Matrices are implemented iterativively and thus scale well for large dimensions. 

NN is implemeneted using the custom matrices and is trained on mnist by default, parameters such as step value, size and shape of the network is modifiable via the source code.

Implemented an IDX reader to process the mnist data as specified here: http://yann.lecun.com/exdb/mnist/
Reader class provides an abstract base, which can be extended to provide custom formats.


## Installation:
  1. Download the project .zip and extract
  2. Check out the Makefile and the instructions below

## Make guide:
  make compile
    Compiles the test.cpp with the KuzyNN library

  make run
    Runs the test.cpp executable with the KuzyNN library (Outputs current error)

  make clean
    Cleans directory of any non-essential files


## Examples:
    Usage of matrices:
      KuzyMatrix::Matrix<double> x ({3, 4});
      KuzyMatrix::Matrix<double> y ({4,3});
    
      x.fill(3);
      y.fill(4);

      x.flatten();
      y.flatten();
    
      (x + y).print();


      



  
