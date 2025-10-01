#include "catch.hpp"

#include "new_db/new_db.h"

TEST_CASE("encodedvalue","[types][encodedvalue]") {

  SECTION("string") {
    std::string str("some unique and amazing string");
    new_db::EncodedValue ev1(str);
    new_db::EncodedValue ev2(str);
    new_db::EncodedValue random(std::string(("asdasd asda sdasd ")));
    new_db::EncodedValue empty(new_db::Type::CPP,new_db::Bytes(),0,0);

    REQUIRE(0 != str.length()); // ensure it hasn't had its contents moved
    REQUIRE(ev1.hasValue());
    REQUIRE(ev2.hasValue());
    REQUIRE(str.length() == ev1.length());
    REQUIRE(str.length() == ev2.length());
    char ev1chars[ev1.length()];
    int pos = 0;
    for (auto& c : ev1.data()) {
      ev1chars[pos++] = (const char)c;
    }
    char ev2chars[ev2.length()];
    pos = 0;
    for (auto& c : ev2.data()) {
      ev2chars[pos++] = (const char)c;
    }
    REQUIRE(0 == strcmp(str.c_str(),ev1chars));
    REQUIRE(0 == strcmp(str.c_str(),ev2chars));
    REQUIRE(0 != ev1.hash());
    REQUIRE(0 != ev2.hash());
    REQUIRE(ev1.hash() == ev2.hash());
    REQUIRE(new_db::Type::CPP == ev1.type());
    REQUIRE(new_db::Type::CPP == ev2.type());

    // elements of == function
    REQUIRE(ev1.hasValue()==ev2.hasValue());
    REQUIRE(ev1.type()==ev2.type());
    REQUIRE(0==strcmp(ev1chars,ev2chars));
    // actual == function
    REQUIRE(ev1 == ev2);

    // check against random and empty
    REQUIRE(!(ev1 == random));
    REQUIRE(!(ev1 == empty));
    REQUIRE(!(ev2 == random));
    REQUIRE(!(ev2 == empty));
    REQUIRE(!(random == empty));
    // inequality
    REQUIRE(ev1 != random);
    REQUIRE(ev1 != empty);
    REQUIRE(ev2 != random);
    REQUIRE(ev2 != empty);
    REQUIRE(random != empty);

    REQUIRE(8 == sizeof(ev1.hash()));
    REQUIRE(8 == sizeof(ev2.hash()));
  }

  SECTION("containers","[containers]") {
    std::string str("some unique and amazing string"); // length 30
    std::string str2("another unique and amazing string"); // length 33
    new_db::EncodedValue ev1(str);
    new_db::EncodedValue ev2(str);
    new_db::EncodedValue random(std::string(("asdasd asda sdasd "))); // length 18
    new_db::EncodedValue empty(new_db::Type::CPP,new_db::Bytes(),0,0); // length 0

    new_db::Set set(std::make_unique<std::unordered_set<new_db::EncodedValue>>());
    set->insert(ev1);
    set->insert(ev2);
    set->insert(random);
    set->insert(empty);
    set->emplace(std::string(("asdasd asda sdasd ssssssss"))); // length 26
    set->emplace(std::string(("asdasd asda sdasd "))); // should not be duplicated
    set->emplace(str2);

    // but the below SIX will all return a match
    REQUIRE(set->end() != set->find(ev1));
    REQUIRE(set->end() != set->find(ev2));
    REQUIRE(set->end() != set->find(random));
    REQUIRE(set->end() != set->find(empty));
    REQUIRE(set->end() != set->find(new_db::EncodedValue(str2)));
    REQUIRE(set->end() != set->find(new_db::EncodedValue(std::string(("asdasd asda sdasd ")))));
    REQUIRE(set->end() != set->find(new_db::EncodedValue(std::string(("asdasd asda sdasd ssssssss")))));
    for (auto v = set->begin();v != set->end();v++) {
      std::cout << "  Found value with length: " << v->length() << ", hash: " << v->hash() << std::endl;
    }
    REQUIRE(set->size() == 5); // ev1 and ev2 cannot both be in here because EncodedValue::operator== will match them
  }
}
