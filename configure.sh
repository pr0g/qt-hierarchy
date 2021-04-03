#!/bin/bash

cmake -B build -G Ninja \
-DCMAKE_PREFIX_PATH=/usr/local/opt/qt@5 \
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
-DCMAKE_BUILD_TYPE=Debug
