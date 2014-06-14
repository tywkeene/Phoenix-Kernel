#!/bin/bash
objcopy --only-keep-debug phoenix-kernel kernel-syms
qemu -s -S -m 128M -kernel phoenix-kernel &
gdb
