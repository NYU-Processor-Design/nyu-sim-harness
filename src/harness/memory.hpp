#ifndef NYU_SIM_HARNESS_MEMORY_HPP
#define NYU_SIM_HARNESS_MEMORY_HPP

#include <algorithm>
#include <array>
#include <cstddef>
#include <exception>
#include <format>
#include <unordered_map>
#include <utility>

namespace nyu {

template <size_t PgSize, size_t NumPg, typename Word> class ContiguousMemory {
  using Page = std::array<Word, PgSize>;

public:
  Word& operator[](size_t address) {
    const auto& [pgNum, offset] {numOffset(address)};
    return getPage(pgNum)[offset];
  }

  void write(Word* src, size_t count, size_t dst) {
    auto& [pgNum, offset] {numOffset(dst)};

    size_t writeSize {PgSize - offset};
    std::copy_n(src, writeSize, getPage(pgNum).data() + offset);
    src += writeSize;
    count -= writeSize;

    while(count) {
      writeSize = count > PgSize ? PgSize : count;
      std::copy_n(src, writeSize, getPage(++pgNum).data());
      src += writeSize;
      count -= writeSize;
    }
  }

  void read(size_t src, size_t count, Word* dst) {
    auto& [pgNum, offset] {numOffset(src)};

    size_t readSize {PgSize - offset};
    std::copy_n(getPage(pgNum).data() + offset, readSize, dst);
    dst += readSize;
    count -= readSize;

    while(count) {
      readSize = count > PgSize ? PgSize : count;
      std::copy_n(getPage(++pgNum).data(), readSize, dst);
      dst += readSize;
      count -= readSize;
    }
  }

private:
  std::unordered_map<size_t, Page> mem;

  std::pair<size_t, size_t> numOffset(size_t address) {
    size_t pgNum {address / PgSize};
    size_t offset {address % PgSize};
    return {pgNum, offset};
  }

  Page& getPage(size_t pgNum) {
    if(pgNum >= NumPg)
      throw std::runtime_error {std::format("Page Fault: {}", pgNum)};

    if(auto it {mem.find(pgNum)}; it != mem.end())
      return it->second;

    mem[pgNum] = {};
    return mem[pgNum];
  }
};

} // namespace nyu

#endif // NYU_SIM_HARNESS_MEMORY_HPP
