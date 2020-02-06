#include <cassert>
#include "KuzyArray.h"


void KuzyConv::Conv::applyConv(KuzyArray::Matrix<double>& mat2conv, const KuzyArray::Matrix<double>& kernel2apply) {
    assert(
    (mat2conv.getLengthX()>=kernel2apply.getLengthY()) && (mat2conv.getLengthX()>=kernel2apply.getLengthX()) 
    && "Error when attempting to convolve a matrix! [Kernel specified bigger than the actual matrix to convolve]"
    );

    
    KuzyArray::Matrix<double> map {mat2conv.getLengthY() - kernel2apply.getLengthY() + 1, mat2conv.getLengthX() - kernel2apply.getLengthX() + 1};

    // Convolve
    for (int index_y {0}; index_y < map.getLengthY(); ++index_y) {
        for (int index_x {0}; index_x < map.getLengthX(); ++index_x) {
            KuzyArray::Matrix<double>  tempMat {mat2conv.cut(index_y, (index_y)+kernel2apply.getLengthY()-1, index_x, (index_x)+kernel2apply.getLengthX()-1)};
            
            tempMat.multiply(kernel2apply);
            map[index_y][index_x] = tempMat.sum();     
        }
    }
    
    mat2conv = map;  
    
}

KuzyConv::Conv::Conv(KuzyArray::Vector<KuzyArray::Matrix<double>> kernels) {
    this->kernels = kernels;
}

void KuzyConv::Conv::process(KuzyArray::Vector<KuzyArray::Matrix<double>>& mats2process) {

    KuzyArray::Vector<KuzyArray::Matrix<double>> mats_new {mats2process.getLength()*kernels.getLength()};

    for (int index_mat{0}; index_mat<mats2process.getLength(); ++index_mat) {
        for (int index_kernel {0}; index_kernel<kernels.getLength(); ++index_kernel) {
            applyConv(mats2process[index_mat], kernels[index_kernel]);
            mats_new[(index_mat*kernels.getLength())+index_kernel] = mats2process[index_mat];      
        }
    }

    mats2process = mats_new;
}

KuzyConv::poolMax222::poolMax222() {}

void KuzyConv::poolMax222::pool(KuzyArray::Matrix<double>& mat2pool) {
    
    if ( ((mat2pool.getLengthY() % 2) != 0) || ((mat2pool.getLengthX() % 2 != 0)) ) {
        KuzyConv::pad(mat2pool, 0, 0, mat2pool.getLengthY() + 1 , mat2pool.getLengthX() + 1 );
    };

    KuzyArray::Matrix<double> matPooled {mat2pool.getLengthY()/2, mat2pool.getLengthX()/2};

    for (int index_y {0}; index_y<matPooled.getLengthY(); ++index_y) {
        for (int index_x {0}; index_x<matPooled.getLengthX(); ++index_x) {
            matPooled[index_y][index_x] = mat2pool.cut(index_y*2, (index_y*2)+1, index_x*2, (index_x*2)+1).max();
        }
    }
    mat2pool = matPooled;
}

void KuzyConv::poolMax222::process(KuzyArray::Vector<KuzyArray::Matrix<double>>& arr2process) {
    
    KuzyArray::Vector<KuzyArray::Matrix<double>> arr_new {arr2process.getLength()};

    for (int index{0}; index<arr2process.getLength(); ++index) {
        (*this).pool(arr2process[index]);
        arr_new[index] = arr2process[index];
    }
    arr2process = arr_new;
}

KuzyConv::AFunc::AFunc(double (*activateFunc)(double)) {
    this->activationFunc = activateFunc;
}

void KuzyConv::AFunc::activate(KuzyArray::Matrix<double>& mat2activate) {
    for (int index_row{0}; index_row<mat2activate.getLengthY(); ++index_row) {
        for (int index_col{0}; index_col<mat2activate.getLengthX(); ++index_col) {
            mat2activate[index_row][index_col] = (*activationFunc)(mat2activate[index_row][index_col]);
        }
    }
}

void KuzyConv::AFunc::process(KuzyArray::Vector<KuzyArray::Matrix<double>>& vectorOfMatrices) {
   
    KuzyArray::Vector<KuzyArray::Matrix<double>> vectorOfMat_new {vectorOfMatrices.getLength()};

    for (int index{0}; index<vectorOfMatrices.getLength(); ++index) {
        (*this).activate(vectorOfMatrices[index]);
        vectorOfMat_new[index] = vectorOfMatrices[index];
    }

    vectorOfMatrices = vectorOfMat_new;
}


void KuzyConv::pad(KuzyArray::Matrix<double>& mat2pad, const int startY, const int startX, const int lengthY_new, const int lengthX_new) {
    assert(
        (((startY+mat2pad.getLengthY()-1) <= lengthY_new) && ((startX+mat2pad.getLengthX()-1) <= lengthX_new))
        && (startY >= 0 && startX >= 0)
        && "Padding error [super informative ik :3 ]"
    );
    
    KuzyArray::Matrix<double> newMat {lengthY_new, lengthX_new};
    for (int index_row{0}; index_row<mat2pad.getLengthY(); ++index_row) {
        for (int index_col{0}; index_col<mat2pad.getLengthX(); ++index_col) {
            newMat[startY+index_row][startX+index_col] = mat2pad[index_row][index_col];
        }
    }
    mat2pad = newMat;
}

