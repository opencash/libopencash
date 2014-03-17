#!/usr/bin/env bash

set -x
set -e

source $(dirname $0)/env.sh

if [ "$TRAVIS_PULL_REQUEST" == "false" ]; then
    echo -n "Pushing changes to ivy_repo... "
    cd $IVY_REPO_DIR

    ./update-directory-index.sh
    git add -f .
    git commit -m "Travis-CI: $TRAVIS_REPO_SLUG@$TRAVIS_COMMIT (branch $TRAVIS_BRANCH, build #$TRAVIS_BUILD_NUMBER)"
    git push -fq origin gh-pages
    echo "done"
fi
