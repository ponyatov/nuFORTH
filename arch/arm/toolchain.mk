
CPU		= arm926ej-s
HW		= none
ARCH	= arm
TARGET	= $(ARCH)-$(HW)-eabi

CFG_CPU += --with-cpu=$(CPU)

-include ../toolchain.mk

