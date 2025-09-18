#include "catch.hpp"

#include "new_db/new_db.h"

#include <cstring>

TEST_CASE("keyvalue","[setKeyValue,getKeyValue]") {

  // Story:-
  //   [Who]   As a database user
  //   [What]  I need to store and retrieve a value with a simple name
  //   [Value] So I can persist data for later use
  SECTION("keyvalue-key") {
    std::string dbname("myemptydb");
    std::unique_ptr<new_db::IDatabase> db(new_db::GroundUpDB::createEmptyDB(dbname));

    // We know we have been successful when:-
    // 1. The retrieved value is the same as the stored value
    std::string key("simplestring");
    std::string val("Some highly valuable value");
    new_db::EncodedValue value(val);
    db->setKeyValue(key,std::move(value));
    new_db::EncodedValue ev1 = db->getKeyValue(key);
    REQUIRE(0 != val.length()); // ensure it hasn't had its contents moved
    REQUIRE(ev1.hasValue());
    REQUIRE(val.length() == ev1.length());
    char* ev1chars = new char[ev1.length() + 1];
    int pos = 0;
    for (auto& c : ev1.data()) {
      ev1chars[pos++] = (const char)c;
    }
    ev1chars[pos] = '\0';
    REQUIRE(0 == strcmp(val.c_str(),ev1chars));
    REQUIRE(0 != ev1.hash());
    REQUIRE(new_db::Type::CPP == ev1.type());
    REQUIRE(value == ev1);

    new_db::EncodedValue value2("Some highly valuable value number 2");
    db->setKeyValue(key,std::move(value2));
    REQUIRE(value2 == db->getKeyValue(key));

    db->destroy();
  }

  //   [Who]   As a database user
  //   [What]  I want to be able to logically segment my data
  //   [Value] To make storage, querying, and retrieval easier and quicker
  SECTION("Bucketed set and get") {
    std::string dbname("myemptydb");
    std::unique_ptr<new_db::IDatabase> db(new_db::GroundUpDB::createEmptyDB(dbname));

    // We know we have been successful when:-
    // 1. The retrieved value is the same as the stored value
    std::string key("simplestring");
    new_db::EncodedValue value("Some highly valuable value");
    std::string bucket("bucket 1");
    std::cout << "Setting key value with bucket" << std::endl;
    db->setKeyValue(key, std::move(value), bucket);
    std::cout << "Calling get key value" << std::endl;
    REQUIRE(value == db->getKeyValue(key));
    std::cout << "Destroying DB" << std::endl;

    // Note bucket query is in the query-tests.cpp file

    db->destroy();
  }


}

TEST_CASE("keyvalue-set","setKeyValue(std::string,std::unordered_set<std::string>),getKeyValueSet") {

  //   [Who]   As a database user
  //   [What]  I want to be able to store multiple values against a single key (i.e. a set or list)
  //   [Value] To fit the data model I need in my application
  SECTION("Basic List set and get") {
    std::string dbname("myemptydb");
    std::unique_ptr<new_db::IDatabase> db(new_db::GroundUpDB::createEmptyDB(dbname));

    // We know we have been successful when:-
    // 1. The retrieved value is the same as the stored value
    std::string key("simplestring");
    new_db::EncodedValue v1("Some highly valuable value");
    new_db::EncodedValue v2("Some highly valuable value 2");
    new_db::EncodedValue v3("Some highly valuable value 3");
    new_db::Set set = std::make_unique<std::unordered_set<new_db::EncodedValue>>();
    set->insert(v1);
    set->insert(v2);
    set->insert(v3);
    db->setKeyValue(key,set);
    auto result = db->getKeyValueSet(key);
    REQUIRE(result.get()->size() == 3);
    REQUIRE(result.get()->find(v1) != result.get()->end());
    REQUIRE(result.get()->find(v2) != result.get()->end());
    REQUIRE(result.get()->find(v3) != result.get()->end());

    db->destroy();
  }
}
