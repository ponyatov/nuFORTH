.PHONY: hello
hello: hello.elf
	xterm -e qemu-system-arm -M versatilepb -m 1M -nographic -kernel $< -s -S &
	sleep 1
	ddd --command=hello.gdb $< &

toolchain: dirs libs0 binutils gcc0

CPU		= arm926ej-s
HW		= none
ARCH	= arm
TARGET	= $(ARCH)-$(HW)-eabi

CFG_CPU += --with-cpu=$(CPU)

-include ../toolchain.mk

CFLAGS += -mcpu=$(CPU)

CFLAGS += -g2 -O0

TRG	= $(CROSS)/bin/$(TARGET)
TRG = $(TARGET)
CFLAGS += -nostdlib

CC = $(TRG)-gcc
AS = $(TRG)-as
LD = $(TRG)-ld
OD = $(TRG)-objdump

CFLAGS += -I$(CROSS)/lib/gcc/$(TARGET)/$(GCC_VER)/include

hello.elf: hello_s.o hello_c.o
	$(CC) $(CFLAGS) -T hello.ld -o $@ $^ && $(OD) -x -d $@ > $@.dis

hello_c.o: hello.c Makefile
	$(CC) $(CFLAGS) -c -o $@ $<
hello_s.o: hello.S Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

