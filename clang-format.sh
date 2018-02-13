#!/usr/bin/env bash

RELATIVE_CSGOPRS_SOURCE_PATH=`dirname ${BASH_SOURCE[@]}`
CSGOPRS_SOURCE_PATH=`readlink -f ${RELATIVE_CSGOPRS_SOURCE_PATH}`

clang-format -i -style=file \
    `find ${CSGOPRS_SOURCE_PATH}/src -type f -name '*.cc'` \
    `find ${CSGOPRS_SOURCE_PATH}/src -type f -name '*.h'`
