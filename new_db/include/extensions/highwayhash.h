#ifndef HIGHWAYHASH_H
#define HIGHWAYHASH_H

#include <string>
#include "../types.h"
#include "highwayhash/highwayhash.h"

namespace new_dbext {

using namespace highwayhash;

class HighwayHash {
public:
  HighwayHash();
  HighwayHash(std::uint64_t s1,std::uint64_t s2,std::uint64_t s3,std::uint64_t s4);
  ~HighwayHash();

  std::size_t operator() (const new_db::HashedValue& s) const noexcept;
  std::size_t operator() (const new_db::EncodedValue& s) const noexcept;
  std::size_t operator() (const std::string& s) const noexcept;
  std::size_t operator() (const new_db::Bytes& bytes) const noexcept;
  std::size_t operator() (const char* data,std::size_t length) const noexcept;
private:
  HHKey m_key HH_ALIGNAS(64); // defining as const will delete copy ctor in Windows MSVCC feature-15
  HighwayHashCatT<HH_TARGET>* m_hh;
  HHResult64* m_result;
};

}

#endif // HIGHWAYHASH_H
