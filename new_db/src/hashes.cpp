#include "extensions/highwayhash.h"
#include "hashes.h"
#include "types.h"

namespace new_db {

class DefaultHash::Impl {
public:
  Impl() : m_hasher() {}
  Impl(std::uint64_t s1,std::uint64_t s2,std::uint64_t s3,std::uint64_t s4) : m_hasher(s1,s2,s3,s4) {}

  new_dbext::HighwayHash m_hasher;
};

DefaultHash::DefaultHash()
  : mImpl(std::make_unique<Impl>())
{
  ;
}

DefaultHash::DefaultHash(std::uint64_t s1,std::uint64_t s2,std::uint64_t s3,std::uint64_t s4)
  : mImpl(std::make_unique<Impl>(s1,s2,s3,s4))
{
  ;
}

DefaultHash::~DefaultHash()
{
  ;
}

std::size_t
DefaultHash::operator() (const std::string& s) const noexcept {
  return mImpl->m_hasher(s);
}

std::size_t
DefaultHash::operator() (const char* data,std::size_t length) const noexcept {
  return mImpl->m_hasher(data,length);
}

std::size_t
DefaultHash::operator() (const HashedValue& s) const noexcept {
  return mImpl->m_hasher(s);
}

std::size_t
DefaultHash::operator() (const EncodedValue& s) const noexcept {
  return mImpl->m_hasher(s);
}

std::size_t
DefaultHash::operator() (const std::vector<std::byte>& bytes) const noexcept {
  return mImpl->m_hasher(bytes);
}

} // end namespace
