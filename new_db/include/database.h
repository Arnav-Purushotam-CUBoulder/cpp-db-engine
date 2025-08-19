#ifndef DATABASE_H
#define DATABASE_H

#include "query.h"
#include "types.h"

#include <string>
#include <functional>

namespace new_db {

class Store {
public:
  Store() = default;
  virtual ~Store() = default;
};

class KeyValueStore : public Store {
public:
  KeyValueStore() = default;
  virtual ~KeyValueStore() = default;

  // Key-Value user functions
  virtual void                            setKeyValue(const HashedValue& key,EncodedValue&& value) = 0;
  //virtual void                            setKeyValue(const HashedKey& key,std::string value, std::string bucket) = 0;
  virtual EncodedValue                    getKeyValue(const HashedValue& key) = 0;
  virtual void                            setKeyValue(const HashedValue& key,const Set& value) = 0;
  virtual Set                             getKeyValueSet(const HashedValue& key) = 0;

  // Key-value management functions
  virtual void                            loadKeysInto(std::function<void(const HashedValue& key,EncodedValue value)> callback) = 0;
  virtual void                            clear() = 0;
};

using QueryResult = std::unique_ptr<IQueryResult>;

class IDatabase
{
public:
  IDatabase() = default;
  virtual ~IDatabase() = default;
  virtual std::string                     getDirectory(void) = 0;

  // Key-Value use cases
  virtual void                            setKeyValue(const HashedValue& key,EncodedValue&& value) = 0;
  virtual void                            setKeyValue(const HashedValue& key,EncodedValue&& value,const std::string& bucket) = 0;
  virtual EncodedValue                    getKeyValue(const HashedValue& key) = 0;
  virtual void                            setKeyValue(const HashedValue& key,const Set& value) = 0;
  virtual void                            setKeyValue(const HashedValue& key,const Set& value,const std::string& bucket) = 0;
  virtual Set                             getKeyValueSet(const HashedValue& key) = 0;

  // Query records functions
  virtual QueryResult query(Query& query) const = 0;
  // TODO replace the below with just the generic polymorphic function
  virtual QueryResult query(BucketQuery& query) const = 0;

  // management functions
  static const std::unique_ptr<IDatabase>       createEmpty(std::string dbname);
  static const std::unique_ptr<IDatabase>       createEmpty(std::string dbname,std::unique_ptr<KeyValueStore>& kvStore);
  static const std::unique_ptr<IDatabase>       createEmpty(std::string dbname,std::unique_ptr<KeyValueStore>& kvStore,std::unique_ptr<KeyValueStore>& idxStore);
  static const std::unique_ptr<IDatabase>       load(std::string dbname);
  virtual void                                  destroy() = 0;

};

}

#endif // DATABASE_H
