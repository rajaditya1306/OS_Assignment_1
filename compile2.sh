#!/bin/sh

mkdir ~/kernelbuild2
cd ~/kernelbuild2
wget https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.19.17.tar.xz
unxz linux-5.19.17.tar.xz
tar -xvf linux-5.19.17.tar
make mrproper
cd linux-5.19.17
wget --no-check-certificate 'https://docs.google.com/uc?export=download&id=1QsGoRe6QKuxlf4_L1Ddt6OHL7bM2rmXQ' -O .config
make -j$(nproc)