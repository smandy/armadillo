#include <iostream>

#include "armadillo"

using namespace arma;
using namespace std;

int main(int argc, char **argv ) {
    irowvec A(50);
    A(25) = 1;

    irowvec kern;
    kern << 4 << 2 << 1;
    A.raw_print(std::cout);
    kern.raw_print(std::cout);
    //x2.raw_print(std::cout);

    for (int i = 0;i<30;++i) {
        A.raw_print(std::cout);
        A = conv(A, kern, "same");
        A = A.transform( [](auto val) { return (30 >> val) & 1; });
    }
    //x3.raw_print(std::cout);
};
