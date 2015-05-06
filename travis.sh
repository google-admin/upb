#!/bin/bash

# Bare build: no dependencies installed, no JIT enabled.
bare_install() {
  :
}
bare_script() {
  make -j12 tests
  make test
}

# Bare JIT build: no dependencies installed, but JIT enabled.
barejit_install() {
  :
}
barejit_script() {
  make -j12 tests WITH_JIT=yes
  make test
}

# Build with Google protobuf support and tests (with JIT).
withprotobuf_install() {
  sudo apt-get update -qq
  sudo apt-get install protobuf-compiler libprotobuf-dev
}
withprotobuf_script() {
  make -j12 tests googlepbtests WITH_JIT=yes
  make test
}

# Build with strict warnings.
warnings_install() {
  :
}
warnings_script() {
  make -j12 default WITH_MAX_WARNINGS=yes
  make -j12 tests WITH_MAX_WARNINGS=yes
  make test
}

# A 32-bit build.  Can only test the core because any dependencies
# need to be available as 32-bit libs also, which gets hairy fast.
# Can't enable the JIT because it only supports x64.
core32_install() {
  sudo apt-get update -qq
  sudo apt-get install libc6-dev-i386 g++-multilib
}
core32_script() {
  make -j12 tests USER_CPPFLAGS=-m32
  make test
}

# A build of Lua and running of Lua tests.
lua_install() {
  sudo apt-get update -qq
  sudo apt-get install lua5.2 liblua5.2-dev
}
lua_script() {
  make -j12 testlua USER_CPPFLAGS=`pkg-config lua5.2 --cflags`
}

# A run that executes with coverage support and uploads to coveralls.io
coverage_install() {
  sudo apt-get update -qq
  sudo apt-get install protobuf-compiler libprotobuf-dev lua5.2 liblua5.2-dev
  sudo pip install cpp-coveralls
}
coverage_script() {
  make -j12 tests googlepbtests testlua WITH_JIT=yes \
      USER_CPPFLAGS="--coverage -O0 `pkg-config lua5.2 --cflags`"
  make test
}
coverage_after_success() {
  coveralls --exclude dynasm --exclude tests --exclude upb/bindings/linux --gcov-options '\-lp'
}

if [ "$1" == "after_success" ] && [ "$UPB_TRAVIS_BUILD" != "coverage" ]; then
  # after_success is only used for coverage.
  exit
fi

set -e
set -x
eval ${UPB_TRAVIS_BUILD}_${1}
