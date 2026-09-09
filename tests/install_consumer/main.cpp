#include <qristal/core/circuit_builder.hpp>
#include <iostream>
#include "xacc.hpp"
int main(int argc, char** argv) {
  xacc::Initialize(argc, argv);
  qristal::CircuitBuilder circuit;
  circuit.H(0);
  const bool ok = circuit.get()->nInstructions() == 1;
  xacc::Finalize();
  if (!ok) return 1;
  std::cout << "PASS: installed Core C++ consumer" << std::endl;
}
