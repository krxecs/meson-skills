#include "shared_library/shared_api.h"

#include <cstdlib>
#include <iostream>

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "usage: cpp-consumer <left> <right>\n";
    return 2;
  }

  const int left = std::atoi(argv[1]);
  const int right = std::atoi(argv[2]);
  const int result = shared_library_add(left, right);
  std::cout << result << '\n';
  return result == 42 ? 0 : 1;
}
