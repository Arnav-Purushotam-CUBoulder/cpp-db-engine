#include "catch.hpp"

#include "new_db/new_db.h"

TEST_CASE("Key","[Key]") {

  // Story:-
  //   [Who]   As a database user
  //   [What]  I need to use keys of different types
  //   [Value] To fit my application data model and make implementation of my programmes easier
  SECTION("StringKey") {
    new_db::Key<std::string> k1("somekey");
    new_db::Key<std::string> k2("somekey");
    new_db::Key<std::string> k3("someotherkey");

    // test raw representation
    REQUIRE(k1.value() == k2.value());
    REQUIRE(k1.value() != k3.value());
    REQUIRE(k2.value() != k3.value());

    // now test binary representation
    char buffer1[15]{'0'};
    char buffer2[15]{'0'};
    char buffer3[15]{'0'};
    k1.copy_to(buffer1);
    k2.copy_to(buffer2);
    k3.copy_to(buffer3);

    REQUIRE(0 == strcmp(buffer1,buffer2));
    REQUIRE(0 != strcmp(buffer1,buffer3));
    REQUIRE(0 != strcmp(buffer2,buffer3));
  }

}
