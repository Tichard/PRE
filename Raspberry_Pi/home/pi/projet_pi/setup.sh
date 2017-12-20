#! /bin/sh

export TOOLCHAIN=/local/sdk_elec/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf
export TARGET=arm-linux-gnueabihf
export PROJ=$PWD
export SRC=$PROJ/src
export ROOTFS=$TOOLCHAIN/arm-linux-gnueabihf/libc
export PATH=$TOOLCHAIN/bin:/usr/sbin:$PATH

export http_proxy=proxy.enib.fr:3128
export https_proxy=proxy.enib.fr:3128
export ftp_proxy=proxy.enib.fr:3128
