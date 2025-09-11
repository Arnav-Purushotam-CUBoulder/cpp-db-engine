#!/usr/bin/env bash
set -euo pipefail
cmake -S . -B build
cmake --build build -j
ctest --test-dir build --output-on-failure || ./build/new_db-tests/new_db-tests
