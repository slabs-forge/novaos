#!/bin/bash
gdb-multiarch -ex 'target remote localhost:1234' kernel.elf
