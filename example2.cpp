#include <iostream>

#include "armadillo"

#include <fstream>
#include <ostream>

#include "boost/format.hpp"

using namespace arma;
using namespace std;

int main(int argc, char **argv) {
  for (int rule = 110; rule < 111; ++rule) {
    irowvec A(1000);
    A.fill(0);
    A(500) = 1;

    A(750) = 1;
    A(10) = 1;
    A(50) = 1;
    A(100) = 1;
    A(750) = 1;
    A(800) = 1;
    A(850) = 1;
    irowvec kern;
    kern << 1 << 2 << 4;
    for (int iters = 0; iters < 100; ++iters) {
      std::cout << "Rule is " << rule << " iterator=" << iters << std::endl;
      std::ostringstream fn;
      fn << "rule" << boost::format("%03d") % rule << "/" << boost::format("%03d") % iters << ".pgm";
      std::ofstream ostr(fn.str(), std::ios::binary);
      ostr << "P2\n";
      ostr << "1000 1000\n";
      ostr << "1\n";
      for (int i = 0; i < 1000; ++i) {
        (1 - A).raw_print(ostr);
        A = conv(A, kern, "same");
        A = A.transform([=](auto val) { return ((rule >> val) & 1); });
      }
      ostr.flush();
      ostr.close();
    };
  }
};
