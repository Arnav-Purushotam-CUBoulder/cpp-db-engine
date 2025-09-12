#!/usr/bin/env bash
set -euo pipefail
./build/new_db-tests/new_db-tests "[!hide][performance]"
