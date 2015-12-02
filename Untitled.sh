
BASENAME=arm-mod-linux-gnueabihf

export PATH=/opt/mod-toolchain/usr/bin/:$PATH

export AR=$BASENAME-gcc
export CC=$BASENAME-gcc
export CPP=$BASENAME-cpp
export CXX=$BASENAME-g++
export LD=$BASENAME-ld
export STRIP=$BASENAME-strip

unset CPPFLAGS
export CFLAGS="-mcpu=cortex-a7 -mtune=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard -ffast-math -fomit-frame-pointer -funroll-loops -funsafe-loop-optimizations"
export CXXFLAGS="-mcpu=cortex-a7 -mtune=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard -ffast-math -fomit-frame-pointer -funroll-loops -funsafe-loop-optimizations"
export LDFLAGS="-Wl,-O1 -Wl,--as-needed -Wl,--strip-all -Wl,--no-undefined"

unset BASENAME
