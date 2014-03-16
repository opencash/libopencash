#!/bin/bash

# This script is to be *sourced* by the other scripts to set up env variables

export IVY_REPO_DIR="$HOME/ivy_repo"
export TOOLCHAINS_DIR="$HOME/toolchains"
export PATH=$PATH:$TOOLCHAINS_DIR/gcc-4.8.1-for-linux64/bin:$TOOLCHAINS_DIR/arm-linux-androideabi-gcc-4.8-android-14/bin

GIT_CREDENTIALS="$HOME/.git_credentials"
