---
name: Bug report
about: Help us squash the roaches.
title: "[BINUTILS] [GDB] Choose ONE!"
labels: ''
assignees: ''

---

Feel free to remove any of the fields below if they are irrelevant to your issue reporting. But please don't be lazy even if you think they are remotely related.

# Setup
**environment**
```
The system on which you installed binutils/GDB.

Host/native architecture:   <x86/arc/etc>
OS type:                    <Linux/Windows>
Version:                    <the_version>
Other libraries of interest: <libc 2.9/etc>
```

**software configuration**
```
binutils:  <version/tag/commit>
gcc:       <version/tag/commit>
gdb:       <version/tag/commit>
newlib:    <version/tag/commit>
toolchain: <version/tag/commit>
glibc:     <version/tag/commit>
uclibc-ng: <version/tag/commit>, <clone url>
linux:     <version/tag/commit>, <clone url>

# only if you used buildroot
buildroot: <version/tag/commit>
```

**toolchain build**
```
If you have built the toolchain yourself describe here the steps you did. Example:

SRC=/path/to/source      # where all the binutils, gcc, etc. are located
BLD=/path/to/build
INS=/path/to/install

DEBUG_FLAGS="-Og -g3 -fvar-tracking-assignments"
build-all.sh --source-dir    ${SRC}           \
             --build-dir     ${BLD}           \
             --install-dir   ${INS}           \
             --release-name  "2019.09-rc1"    \
             --cpu           archs            \
             --no-multilib                    \
             --uclibc                         \
             --target-cflags "${DEBUG_FLAGS}" \
             --jobs          $(nproc)         \
             --no-pdf                         \
             --no-auto-checkout               \
             --no-auto-pull                   \
             --no-external-download           \
             --no-strip                       \
             --native-gdb                     \
             --system-expat                   \
             --no-elf32-strip-target-libs     \
             --no-native                      \
             --no-optsize-newlib              \
             --no-optsize-libstdc++
```

**building rootfs with buildroot**
Provide the `.config` file and mention the changes that need to be adapted. Example:
This is based on `snps_archs38_hsdk_defconfig`. You need to adapt:
```
BR2_DEFCONFIG="/path/to/source/buildroot/configs/snps_archs38_hsdk_defconfig"
BR2_TOOLCHAIN_EXTERNAL_PATH="/path/to/install"
```
```
# adapt config.buildroot.hsdk.uclibc and save it as ".config"
make BR2_JLEVEL=$(nproc)
```

**building linux image**
Provide the `.config` file and mention the changes that need to be adapted. Example:
This is almost the same as `hsdk_defconfig`, with a few changes to use the rootfs from buildroot. You only need to update:
```
CONFIG_INITRAMFS_SOURCE="/path/to/build/buildroot-hsdk/images/rootfs.cpio"
```
```
export COMPROOT=${INS}
export DEJAGNU=${SRC}/toolchain/site.exp
export COMPSRC=${SRC}
export LD_LIBRARY_PATH=${INS}/lib:${LD_LIBRARY_PATH}
export PATH=${INS}/bin:${PATH}

export ARCH=arc
export CROSS_COMPILE=arc-linux-

# adapt config.linux.hsdk and save as ".config"
make -j $(nproc)
make uImage
```

# Bug
## Description
A clear and concise description of what the bug is.

## Reproducing steps
Ideally a minimized test test with a makefile, but fear not if you cannot do that.

## Screenshot/Movies
![gdbserver_is_fine](https://user-images.githubusercontent.com/16524902/68779118-64f40080-0634-11ea-9c41-97ae0cb63b29.gif)

## Expected behavior
Something like: I want it to scratch my back, gently!

# Any additional notes/files
Do you have more to say/upload?
