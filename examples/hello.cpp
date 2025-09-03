#include "new_db/new_db.h"
#include <iostream>
int main(){
  std::string name = std::string("hello-db");
  auto db = new_db::GroundUpDB::createEmptyDB(name);
  db->destroy();
  std::cout << "Created DB: " << name << "\n";
  return 0;
}
