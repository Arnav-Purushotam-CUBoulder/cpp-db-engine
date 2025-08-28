#ifndef EXTQUERY_H
#define EXTQUERY_H

#include "../query.h"

namespace new_dbext {

using namespace new_db;

class DefaultQueryResult: public IQueryResult {
public:
  DefaultQueryResult();
  DefaultQueryResult(KeySet&& recordKeys);
  DefaultQueryResult(Set&& recordKeys);
  virtual ~DefaultQueryResult() = default;

  const KeySet& recordKeys();
private:
  KeySet m_recordKeys;
};

}

#endif // EXTQUERY_H
