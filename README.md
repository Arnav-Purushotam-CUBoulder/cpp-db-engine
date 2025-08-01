# cpp-db-engine

A lightweight modular embedded database engine written in modern C++.
Main purpose of this project, was to learn basic database and C++ concepts


## Overview

cpp-db-engine is a high-performance key-value store designed for flexibility and efficiency. It supports multiple storage backends and provides simple data management capabilities.
It is the first phase, the second phase is making it distributed

## Features

- Key-value storage with string keys and values
- Multiple storage backends:
  - In-memory store (high performance)
  - File-based store (persistent)
  - Memory-cached file store (balanced)
- Bucket support for data organization
- Simple query capabilities

## Building

```bash
git clone <repository-url>
cd cpp-db-engine
git submodule update --init --recursive
cmake -B ./build
cmake --build ./build --config Release

## Basic Usage

# Create a database
./cpp-db-engine-cli -n mydb -c

# Store a value
./cpp-db-engine-cli -n mydb -s -k "key1" -v "value1"

# Retrieve a value
./cpp-db-engine-cli -n mydb -g -k "key1"


## Running Tests

cd build/cpp-db-engine-tests
./cpp-db-engine-tests


## License

Apache 2.0 License - see LICENSE file for details.
\n## Quickstart\n\n- cmake -B build\n- cmake --build build\n- ./build/new_db-tests/new_db-tests\n
\n## Running Tests\n\nRun new_db-tests from the build directory.\n
\n## License\n\nApache 2.0 - see LICENSE.\n
\n## Scripts\n\n- scripts/build.sh\n- scripts/test.sh\n- scripts/bench.sh\n
\n## Examples\n\nSee examples/ for sample programs.\n
\n## Features\n- Memory + File KV stores\n- Bucket queries\n- Simple hashing via HighwayHash\n
