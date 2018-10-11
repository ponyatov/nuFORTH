
# i486dx is minimal for x86 target, old i386sx not supported many time ago
CPU		= i486
HW		= pc
ARCH	= x86
TARGET	= $(CPU)-elf

CFG_CPU += --with-cpu=$(CPU)

-include ../toolchain.mk

