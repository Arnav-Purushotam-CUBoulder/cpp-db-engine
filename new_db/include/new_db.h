#ifndef GROUNDUPDB_H
#define GROUNDUPDB_H

#include <string>

// WARNING: This should ONLY include Client API files
// i.e. NOT anything within include/extensions!

#include "database.h"
#include "hashes.h"
#include "is_container.h"
#include "query.h"
#include "types.h"

namespace new_db {

class GroundUpDB {
 public:
  GroundUpDB();

  static std::unique_ptr<IDatabase> createEmptyDB(std::string& dbname);
  static std::unique_ptr<IDatabase> createEmptyDB(
      std::string& dbname, std::unique_ptr<KeyValueStore>& kvStore);
  static std::unique_ptr<IDatabase> createEmptyDB(
      std::string& dbname, std::unique_ptr<KeyValueStore>& kvStore,
      std::unique_ptr<KeyValueStore>& idxStore);
  static std::unique_ptr<IDatabase> loadDB(std::string& dbname);
};

}  // namespace new_db

#endif  // GROUNDUPDB_H
