#!/usr/bin/env bash

set -x
set -e

source $(dirname $0)/env.sh

echo -n "Setting up git... "
set +x
git config --global user.name $GIT_NAME
git config --global user.email $GIT_EMAIL
git config --global credential.helper "store --file=$GIT_CREDENTIALS"
echo "https://${GH_TOKEN}:@github.com" > $GIT_CREDENTIALS
set -x
echo "done"

echo -n "Cloning ivy_repo... "
git clone --quiet --branch=gh-pages https://github.com/opencash/ivy_repo.git ${IVY_REPO_DIR}
echo "done"

echo -n "Downloading and extracting gcc-4.8.1-for-linux64.tar.bz2... "
mkdir -p $TOOLCHAINS_DIR
(
    cd $TOOLCHAINS_DIR
    TOOLCHAIN=gcc-4.8.1-for-linux64
    curl -O https://dl.dropboxusercontent.com/u/8225764/opencash-build-support/${TOOLCHAIN}.tar.bz2
    tar xjf ${TOOLCHAIN}.tar.bz2
    ln -s $TOOLCHAINS_DIR/${TOOLCHAIN} /usr/local
)
echo "done"

echo -n "Installing Android toolchain... "
(
    cd $TOOLCHAINS_DIR
    TOOLCHAIN=arm-linux-androideabi-gcc-4.8-android-14
    curl -O https://dl.dropboxusercontent.com/u/8225764/opencash-build-support/${TOOLCHAIN}.tar.bz2
    tar xjf ${TOOLCHAIN}.tar.bz2
)
echo "done"
