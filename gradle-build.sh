#!/usr/bin/env bash

set -x
set -e

[ "$TRAVIS_COMMIT" ] && source travis/env.sh

GRADLE_FLAGS=
[ "$TRAVIS_COMMIT" ] && GRADLE_FLAGS='--no-color -q'

echo "./gradlew test"
./gradlew $GRADLE_FLAGS test
echo "after:"
find build -type f

echo "./gradlew build"
./gradlew $GRADLE_FLAGS build
echo "after:"
find build -type f

echo "./gradlew buildNarAndroid-armDebugOpencashStaticLibrary"
./gradlew $GRADLE_FLAGS buildNarAndroid-armDebugOpencashStaticLibrary
echo "after:"
find build -type f

echo "./gradlew publish"
./gradlew $GRADLE_FLAGS publish
echo "after:"
find build -type f
