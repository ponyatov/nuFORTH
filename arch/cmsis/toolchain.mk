
CPU		= cortex-m0
HW		= none
ARCH	= arm
TARGET	= $(ARCH)-$(HW)-eabi

# https://istarc.wordpress.com/2014/07/21/stm32f4-build-your-toolchain-from-scratch/

CFG_CPU += --with-cpu=$(CPU) --with-mode=thumb --with-float=soft

-include ../toolchain.mk

