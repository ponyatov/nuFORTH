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
AS = $(TRG)-as
LD = $(TRG)-ld

#CFLAGS += -nostdlib
CFLAGS += -I$(CROSS)/lib/gcc/$(TARGET)/$(GCC_VER)/include

hello.elf: hello_s.o hello_c.o
	$(CC) $(CFLAGS) -o $@ $^

hello_c.o: hello.c Makefile
	$(CC) $(CFLAGS) -c -o $@ $<
hello_s.o: hello.S Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

