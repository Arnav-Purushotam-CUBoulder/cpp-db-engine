#ifndef HASHES_H
#define HASHES_H

#include "types.h"
#include <string>
#include <memory>

namespace new_db {

// forward declarations
class HashedValue;
class EncodedValue;

class DefaultHash {
public:
  DefaultHash();
  DefaultHash(std::uint64_t s1,std::uint64_t s2,std::uint64_t s3,std::uint64_t s4);
  ~DefaultHash();

  std::size_t operator() (const HashedValue& s) const noexcept;
  std::size_t operator() (const EncodedValue& s) const noexcept;
  std::size_t operator() (const std::string& s) const noexcept;
  std::size_t operator() (const std::vector<std::byte>& bytes) const noexcept;
  std::size_t operator() (const char* data,std::size_t length) const noexcept;

  class Impl;
private:
  std::unique_ptr<Impl> mImpl;
};

}
#endif // HASHES_H
