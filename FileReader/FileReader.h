#include <fstream>
#include <string>
#include <cassert>

#include "KuzyMatrix.h"

namespace FileReader {

    class Reader {
        protected:
            std::ifstream file;
         
            int dims;
            int elements;
            std::vector<int> shape;

            template<class Data>
            Data interpret(char* buffer, const int& buffer_elements) const;
        
        public:
            Reader(const std::string& path);
            virtual ~Reader();
   
            virtual KuzyMatrix::Matrix<double> read(const int& numberOfElements) = 0;
            void reset();

            int unit_vectorSize() const;
            int get_elements() const;
            
    };


    class IDX : public Reader {
        private:
            char* buffer = new char[2];

        public:
            IDX(const std::string& filePath);
            ~IDX();
            KuzyMatrix::Matrix<double> read(const int& numberOfElements) override;
    
    };

    #include "IDX.hpp"
    #include "FileReader.hpp"
}

