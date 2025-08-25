#ifndef QUERY_H
#define QUERY_H

#include "types.h"

#include <string>
#include <memory>
#include <unordered_set>

namespace new_db {

// Tagging class for now
class Query {
public:
  Query() = default;
  virtual ~Query() = default;
private:
};

class IQueryResult {
public:
  IQueryResult() = default;
  virtual ~IQueryResult() = default;

  virtual const KeySet& recordKeys() = 0;
};

// MARK: Query Implementation Types


// default empty query matches all data
class EmptyQuery : public Query {
public:
  EmptyQuery() = default;
  virtual ~EmptyQuery() = default;
};

// Parent bucket query
class BucketQuery : public Query {
public:
  BucketQuery(std::string& bucket);
  virtual ~BucketQuery();

  virtual std::string bucket() const;
private:
  class Impl;
  std::unique_ptr<Impl> mImpl;
};

}
#endif // QUERY_H
