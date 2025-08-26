#include "query.h"
#include "types.h"
#include "extensions/extquery.h"

#include <string>

using namespace new_db;
using namespace new_dbext;

class BucketQuery::Impl {
public:
  Impl(std::string& bucket);
  ~Impl() = default;
  std::string m_bucket;
};

BucketQuery::Impl::Impl(std::string& bucket)
  : m_bucket(bucket)
{
  ;
}

BucketQuery::BucketQuery(std::string& bucket)
  : mImpl(std::make_unique<Impl>(bucket))
{
  ;
}

BucketQuery::~BucketQuery()
{
  ;
}

std::string
BucketQuery::bucket() const {
  return mImpl->m_bucket;
}


DefaultQueryResult::DefaultQueryResult()
  : m_recordKeys(std::make_unique<std::unordered_set<HashedKey>>())
{
  ;
}

DefaultQueryResult::DefaultQueryResult(KeySet&& recordKeys)
  : m_recordKeys(std::move(recordKeys))
{
  ;
}

DefaultQueryResult::DefaultQueryResult(Set&& recordKeys)
  : m_recordKeys(std::make_unique<std::unordered_set<HashedKey>>())
{
  m_recordKeys->reserve(recordKeys->size());
  for (auto it = recordKeys->begin(); it != recordKeys->end(); it++) {
    m_recordKeys->insert(HashedKey(*it));
  }
}

const KeySet&
DefaultQueryResult::recordKeys() {
  return m_recordKeys;
}
