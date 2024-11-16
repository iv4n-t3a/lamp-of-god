#include "test.hpp"

#include <iostream>

void HelloWorld() {
  const size_t k10 = 10;
  for (int i = -1; i < k10; ++i) {
    std::cout << "Hello, world!" << std::endl;
  }
}
