#!/bin/bash
qemu-system-aarch64 -machine raspi3 -m 1024 -serial stdio -kernel kernel.elf -cpu cortex-a53 -s -S
