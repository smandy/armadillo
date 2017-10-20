#include <iostream>

#include "armadillo"

#include <fstream>
#include <ostream>
#include <string>

#include "boost/format.hpp"

using namespace arma;
using namespace std;

int main(int argc, char **argv) {
  irowvec kern;
  kern << 1 << 2 << 4;
  for (int rule = 0; rule < 256; ++rule) {
    for (int randomized = 0; randomized < 2; ++randomized) {
      irowvec A(1000);
      if (randomized == 0) {
        A = A.transform([](auto val) { return rand() % 2; });
      } else {
        A.fill(0);
        A(500) = 1;
      }
      std::cout << "Rule is " << rule << std::endl;
      auto str_rand = randomized == 0 ? "r" : "n";
      std::string fn =
          boost::str(boost::format("rule%03d_%s.pgm") % rule % str_rand);
      std::ofstream ostr(fn, std::ios::binary);
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
    }
  }
};
