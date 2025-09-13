cmake_minimum_required(VERSION 3.12)

add_executable(new_db-tests
	dbmanagement-tests.cpp
	hashing-tests.cpp
	keyvalue-tests.cpp
	keyvalue-bug-tests.cpp
	performance-tests.cpp
	query-tests.cpp
	datatypes-tests.cpp
)

include_directories(${new_db_SOURCE_DIR})

# This assume highwayhash is a sub-module of this repo..
include_directories(${new_db_SOURCE_DIR}/highwayhash)
# if you have built highwayhash as a peer repo, use this line
#include_directories(${new_db_SOURCE_DIR}/../highwayhash)

target_link_libraries(new_db-tests PRIVATE new_db)

target_compile_features(new_db-tests PRIVATE cxx_std_17)
