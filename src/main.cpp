#include <fmt/format.h>

#include "harness/memory.hpp"

int main() {

  try {
    nyu::ContiguousMemory<4096, 1, uint32_t> mem;

    mem[0] = 15;

    mem[4096] = 32;

    fmt::print("Hello World! {}\n", mem[0]);
  } catch(const std::runtime_error& e) {
    fmt::print("Exception: {}\n", e.what());
  }
}
