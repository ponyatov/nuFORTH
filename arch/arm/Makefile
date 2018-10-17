hello: hello.elf

toolchain: dirs libs0 binutils gcc0

CPU		= arm926ej-s
HW		= none
ARCH	= arm
TARGET	= $(ARCH)-$(HW)-eabi

CFG_CPU += --with-cpu=$(CPU)

-include ../toolchain.mk

TRG	= $(CROSS)/bin/$(TARGET)
CC = $(TRG)-gcc
AS = $(TRGT)-as
LD = $(TRGT)-ld

hello.elf: hello.c
	$(CC) -c -o $@ $<

