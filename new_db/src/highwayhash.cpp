#include "extensions/highwayhash.h"

namespace new_dbext {

using namespace highwayhash;

HighwayHash::HighwayHash()
  : m_key{1,2,3,4},
    m_hh(new HighwayHashCatT<HH_TARGET>(m_key)),
    m_result(new HHResult64())
{
  ;
}

HighwayHash::HighwayHash(std::uint64_t s1,std::uint64_t s2,std::uint64_t s3,std::uint64_t s4)
  : m_key{s1,s2,s3,s4},
    m_hh(new HighwayHashCatT<HH_TARGET>(m_key)),
    m_result(new HHResult64())
{
  ;
}

HighwayHash::~HighwayHash() {
  //delete m_hh;
  //delete m_result; // for windows - why does this help???
}

std::size_t
HighwayHash::operator() (std::string const& s) const noexcept {
  m_hh->Reset(m_key);
  m_hh->Append(s.c_str(), s.length());
  m_hh->Finalize(m_result);
  return *m_result;
}

std::size_t
HighwayHash::operator() (const char* data,std::size_t length) const noexcept {
  m_hh->Reset(m_key);
  m_hh->Append(data, length);
  m_hh->Finalize(m_result);
  return *m_result;
}

std::size_t
HighwayHash::operator() (const new_db::HashedValue& data) const noexcept {
  return data.hash();
  // TODO ensure the hash has the same basis as that required by this class
}

std::size_t
HighwayHash::operator() (const new_db::EncodedValue& data) const noexcept {
  return data.hash();
  // TODO ensure the hash has the same basis as that required by this class
}

std::size_t
HighwayHash::operator() (const new_db::Bytes& data) const noexcept {
  m_hh->Reset(m_key);
  for (auto iter = data.begin();iter != data.end();++iter) {
    m_hh->Append((const char*)&*iter,sizeof(*iter));
  }
  m_hh->Finalize(m_result);
  return *m_result;
}

}
