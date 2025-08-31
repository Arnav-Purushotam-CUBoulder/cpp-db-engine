#include "new_db.h"
#include "extensions/extdatabase.h"

using namespace new_db;
using namespace new_dbext;

GroundUpDB::GroundUpDB()
{
}

std::unique_ptr<IDatabase> GroundUpDB::createEmptyDB(std::string &dbname) {
  return EmbeddedDatabase::createEmpty(dbname);
}

std::unique_ptr<IDatabase> GroundUpDB::createEmptyDB(std::string &dbname,std::unique_ptr<KeyValueStore>& kvStore) {
  return EmbeddedDatabase::createEmpty(dbname,kvStore);
}

std::unique_ptr<IDatabase> GroundUpDB::createEmptyDB(std::string &dbname,std::unique_ptr<KeyValueStore>& kvStore,std::unique_ptr<KeyValueStore>& idxStore) {
  return EmbeddedDatabase::createEmpty(dbname,kvStore,idxStore);
}

std::unique_ptr<IDatabase> GroundUpDB::loadDB(std::string &dbname) {
  return EmbeddedDatabase::load(dbname);
}
