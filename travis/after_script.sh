#!/usr/bin/env bash

set -x
set -e

source $(dirname $0)/env.sh

echo -n "Deleting git credentials... "
rm -f $GIT_CREDENTIALS
echo "done"
