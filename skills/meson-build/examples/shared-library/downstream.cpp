#include <shared_library/shared_api.h>

int main() {
  return shared_library_add(19, 23) == 42 ? 0 : 1;
}
