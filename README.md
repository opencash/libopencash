[![Build Status](https://travis-ci.org/opencash/libopencash.png?branch=master)](https://travis-ci.org/opencash/libopencash)

#### EARLY STAGE

Please note that `libopencash` (and more broadly, OpenCash) is in a very early stage of development. The current focus lies on getting infrastructure set up and cross-platform issues sorted out. The actual functionality is still very limited.

_This project is not usable yet!_

# What is `libopencash`?

`libopencash` is the core of OpenCash, a free open-source accounting software. It is a cross-platform library, written in C++.

# Build instructions

Run `./build.sh` to build libopencash on your native platform and execute
the tests. If all tests pass it will build libopencash for all available
cross-compilation platforms on your system.

To cross-compile to a particular platform, follow the instructions below.

## Your native platform

Make sure the GCC or Clang tools are available in your `PATH`. No further
adjustments needed.

## osx-x86_64

OSX compilation has only been tested on a Mac. No cross-compilation to OSX has
been attempted yet. On OSX the build is configured to use libc++ as the standard
library, not libstdc++. From Mavericks onwards libc++ is the default so it seems
to be the more future-proof choice.

Make sure the developer commandline tools are installed and available in your
`PATH`. No further adjustments needed.

## linux-amd64

If you are compiling on a linux-amd64 system make sure GCC (version >= 4.7) or
Clang is in your `PATH`.

If you are cross-compiling to linux-amd64 you must add a GCC cross-compilation
toolchain to you `PATH`. The tools should be prefixed with `x86_64-pc-linux-`
(`x86_64-pc-linux-g++`, `x86_64-pc-linux-ar`, etc).

You can download a cross-compilation toolchain osx --> linux-amd64 here:
[gcc-4.8.1-for-linux64.tar.bz2](http://crossgcc.rts-software.org/download/gcc-4.8.1-for-linux32-linux64/gcc-4.8.1-for-linux64.tar.bz2),
thanks to [Pierre
Molinaro](http://crossgcc.rts-software.org/doku.php?id=compiling_for_linux).
Extract the archive and add the `bin/` directory to your `PATH`.

## android-arm

Make sure you include a standalone Android NDK toolchain in your `PATH`. The
tools should be prefixed with `arm-linux-androideabi-`
(`arm-linux-androideabi-g++`, `arm-linux-androideabi-ar`, etc). The toolchain
should be based on GCC (version >= 4.7).

You can download a cross-compilation toolchain osx --> android-arm here:
[arm-linux-androideabi-gcc-4.8-android-14.tar.bz2](https://dl.dropboxusercontent.com/u/8225764/opencash-build-support/arm-linux-androideabi-gcc-4.8-android-14.tar.bz2).
Extract the archive and add the `bin/` directory to your `PATH`. The toolchain
contains GCC 4.8 and targets API level 14 (Android 4.0). Created using the
Android NDK tools with:

```
./build/tools/make-standalone-toolchain.sh \
--platform=android-14 \
--toolchain=arm-linux-androideabi-4.8 \
--install-dir=$HOME/tmp/ndk/arm-linux-androideabi-gcc-4.8-android-14
```

## License

[GNU General Public License v2 (GPL-2.0)](http://www.tldrlegal.com/license/GPL2)

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Submit a Pull Request

[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/opencash/libopencash/trend.png)](https://bitdeli.com/free "Bitdeli Badge")
