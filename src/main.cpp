#include <fmt/format.h>

#include "harness/memory.hpp"

int main() {

  try {
    nyu::ContiguousMemory<4096, 1, uint32_t, 0xDEADBEEF> mem;

    mem[0] = 15;


    fmt::print("Hello World! 0x{:X}\n", mem[1]);
  } catch(const std::runtime_error& e) {
    fmt::print("Exception: {}\n", e.what());
  }
}
