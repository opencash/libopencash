#!/usr/bin/env bash

set -x
set -e

[ "$TRAVIS_COMMIT" ] && source travis/env.sh

GRADLE_FLAGS=
[ "$TRAVIS_COMMIT" ] && GRADLE_FLAGS='--no-color -q'

./gradlew $GRADLE_FLAGS test build
