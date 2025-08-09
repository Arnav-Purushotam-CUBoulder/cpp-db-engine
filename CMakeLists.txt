
# Top-level CMake for new_db
cmake_minimum_required(VERSION 3.12)

project(new_db VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(GNUInstallDirs)

add_subdirectory(new_db)
add_subdirectory(new_db-tests)
