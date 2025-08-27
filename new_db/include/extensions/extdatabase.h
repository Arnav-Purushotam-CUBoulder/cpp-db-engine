#ifndef EXTDATABASE_H
#define EXTDATABASE_H

#include "../database.h"

#include <functional>

namespace new_dbext {

using namespace new_db;


// Ephemeral
class MemoryKeyValueStore : public KeyValueStore {
public:
  MemoryKeyValueStore();
  MemoryKeyValueStore(std::unique_ptr<KeyValueStore>& toCache);
  ~MemoryKeyValueStore();

  // Key-Value user functions
  void                            setKeyValue(const HashedValue& key,EncodedValue&& value);
  EncodedValue                    getKeyValue(const HashedValue& key);
  void                            setKeyValue(const HashedValue& key,const Set& value);
  Set                             getKeyValueSet(const HashedValue& key);

  // Key-value management functions
  void                            loadKeysInto(std::function<void(const HashedValue& key,EncodedValue value)> callback);
  void                            clear();

private:
  class Impl;
  std::unique_ptr<Impl> mImpl;
};

class FileKeyValueStore : public KeyValueStore {
public:
  FileKeyValueStore(std::string fullpath);
  ~FileKeyValueStore();

  // Key-Value use cases
  void                            setKeyValue(const HashedValue& key,EncodedValue&& value);
  EncodedValue                    getKeyValue(const HashedValue& key);
  void                            setKeyValue(const HashedValue& key,const Set& value);
  Set                             getKeyValueSet(const HashedValue& key);

  void                            loadKeysInto(std::function<void(const HashedValue& key,EncodedValue value)> callback);
  void                            clear();

private:
  class Impl;
  std::unique_ptr<Impl> mImpl;
};

class EmbeddedDatabase : public IDatabase {
public:
  EmbeddedDatabase(std::string dbname, std::string fullpath);
  EmbeddedDatabase(std::string dbname, std::string fullpath,
                   std::unique_ptr<KeyValueStore>& kvStore);
  EmbeddedDatabase(std::string dbname, std::string fullpath,
                   std::unique_ptr<KeyValueStore>& kvStore,
                   std::unique_ptr<KeyValueStore>& idxStore);
  ~EmbeddedDatabase();

  std::string                                 getDirectory(void);

  // Key-Value use cases
  void                                        setKeyValue(const HashedValue& key,EncodedValue&& value);
  void                                        setKeyValue(const HashedValue& key,EncodedValue&& value,const std::string& bucket);
  EncodedValue                                getKeyValue(const HashedValue& key);
  void                                        setKeyValue(const HashedValue& key,const Set& value);
  void                                        setKeyValue(const HashedValue& key,const Set& value,const std::string& bucket);
  Set                                         getKeyValueSet(const HashedValue& key);

  // Query records functions
  std::unique_ptr<IQueryResult>                query(Query& query) const;
  std::unique_ptr<IQueryResult>                query(BucketQuery& query) const = 0;

  // management functions
  static  const std::unique_ptr<IDatabase>    createEmpty(std::string dbname);
  static  const std::unique_ptr<IDatabase>    createEmpty(std::string dbname,std::unique_ptr<KeyValueStore>& kvStore);
  static  const std::unique_ptr<IDatabase>    createEmpty(std::string dbname,std::unique_ptr<KeyValueStore>& kvStore,std::unique_ptr<KeyValueStore>& idxStore);
  static  const std::unique_ptr<IDatabase>    load(std::string dbname);
  void                        destroy();

  class Impl;

private:
  std::unique_ptr<Impl> mImpl;
};

}

#endif // EXTDATABASE_H
