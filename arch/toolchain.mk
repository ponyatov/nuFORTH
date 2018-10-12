
# shared makefile, this vars must be defined:

#CPU	= i386
#ARCH	= x86
#TARGET	= $(CPU)-elf

# versions

BINUTILS_VER	= 2.29.1
GCC_VER			= 7.3.0
GDB_VER			= 7.11.1

# packages

BINUTILS		= binutils-$(BINUTILS_VER)
GCC				= gcc-$(GCC_VER)
GDB				= gdb-$(GDB_VER)

# source archives

BINUTILS_GZ		= $(BINUTILS).tar.xz
GCC_GZ			= $(GCC).tar.xz
GDB_GZ			= $(GDB).tar.xz

# directories

CWD		= $(CURDIR)
GZ		= $(HOME)/gz
TMP		= $(HOME)/tmp
SRC		= $(TMP)/src
SYS		= $(CWD)/sysroot
CROSS	= $(CWD)/cross

# make directories

dirs:
	mkdir -p $(GZ) $(TMP) $(SRC) $(SYS) $(CROSS)

# configure

XPATH			= PATH=$(CROSS)/bin:$(PATH)

CFG_ALL 		= --disable-nls --prefix=$(CROSS)

BINUTILS_CFG	= --with-sysroot=$(SYS) --with-native-system-header-dir=/include  \
				  --enable-lto --target=$(TARGET) $(CFG_CPU)

GCC_CFG			= $(BINUTILS_CFG) --enable-languages="c" \
					--disable-shared --disable-threads \
					--without-headers --with-newlib \
					--disable-bootstrap 

GDB_CFG			= $(BINUTILS_CFG)

# build cross compiler (local)

binutils: $(SRC)/$(BINUTILS)/configure
	rm -rf $(TMP)/binutils ; mkdir $(TMP)/binutils ; cd $(TMP)/binutils ;\
		$(XPATH) $< $(CFG_ALL) $(BINUTILS_CFG) &&\
			$(MAKE) -j4 && $(MAKE) install

gcc: $(SRC)/$(GCC)/configure
	rm -rf $(TMP)/gcc ; mkdir $(TMP)/gcc ; cd $(TMP)/gcc ;\
		$(XPATH) $< $(CFG_ALL) $(GCC_CFG) &&\
			$(MAKE) -j4 all-gcc && $(MAKE) install-gcc &&\
			$(MAKE) -j4 all-target-libgcc && $(MAKE) install-target-libgcc

gdb: $(SRC)/$(GDB)/configure
	rm -rf $(TMP)/gdb ; mkdir $(TMP)/gdb ; cd $(TMP)/gdb ;\
		$(XPATH) $< $(CFG_ALL) $(GDB_CFG) &&\
			$(MAKE) -j4 && $(MAKE) install

# unpack source code

$(SRC)/$(BINUTILS)/configure: $(GZ)/binutils/$(BINUTILS_GZ)
	cd $(SRC) ; xzcat $< | tar x && touch $@
$(SRC)/$(GCC)/configure: $(GZ)/gcc/$(GCC_GZ)
	cd $(SRC) ; xzcat $< | tar x && touch $@
$(SRC)/$(GDB)/configure: $(GZ)/gdb/$(GDB_GZ)
	cd $(SRC) ; xzcat $< | tar x && touch $@

