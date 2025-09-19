#include "catch.hpp"

#include "new_db/new_db.h"

TEST_CASE("kv-bugs","[setKeyValue,getKeyValue]") {

  // BUG-0000001
  // Bug: When using a memory store to front a file store, and loading
  //      keys at second launch time, the kv file name was improperly
  //      constructed.
  // libc++abi.dylib: terminating with uncaught exception of type
  //   std::length_error: basic_string
  // [1]    96973 abort      ./new_db-cli -n mydb -s -k first -v value1
  SECTION("loadKeysIntoMemoryStoreFromFileStore_kvFilename") {
    std::string dbname("myemptydb");
    std::string key("simplestring");
    new_db::EncodedValue value("Some highly valuable value");
    {
      std::unique_ptr<new_db::IDatabase> db(
            new_db::GroundUpDB::createEmptyDB(dbname));

      // We know we have been successful when:-
      // 1. The retrieved value is the same as the stored value
      db->setKeyValue(key,std::move(value));
      REQUIRE(value == db->getKeyValue(key));
    }

    std::unique_ptr<new_db::IDatabase> db(
          new_db::GroundUpDB::loadDB(dbname));
    new_db::EncodedValue value2("Some highly valuable value number 2");
    REQUIRE_NOTHROW(db->setKeyValue(key,std::move(value2))); // BLOWS UP
    REQUIRE(value2 == db->getKeyValue(key));

    db->destroy();
  }
}
