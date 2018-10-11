
# shared makefile, this vars must be defined:

#CPU	= i386
#ARCH	= x86
#TARGET	= $(CPU)-elf

# versions

BINUTILS_VER	= 2.29.1
GCC_VER			= 7.3.0
#6.4.0 error in libssp/libquad

# packages

BINUTILS		= binutils-$(BINUTILS_VER)
GCC				= gcc-$(GCC_VER)

# source archives

BINUTILS_GZ		= $(BINUTILS).tar.xz
GCC_GZ			= $(GCC).tar.xz

# directories

CWD		= $(CURDIR)
GZ		= $(HOME)/gz
TMP		= $(HOME)/tmp
SRC		= $(CWD)/src
SYS		= $(CWD)/sysroot
CROSS	= $(CWD)/cross

# configure

XPATH			= PATH=$(CROSS)/bin:$(PATH)

CFG_ALL 		= --disable-nls --prefix=$(CROSS)

BINUTILS_CFG	= --with-sysroot=$(SYS) --enable-lto --target=$(TARGET)

GCC_CFG			= $(BINUTILS_CFG) --without-headers --with-newlib --enable-languages="c"

# build cross compiler (local)

gcc: $(CROSS)/bin/$(TARGET)-gcc binutils
$(CROSS)/bin/$(TARGET)-gcc: $(SRC)/$(GCC)/configure
	rm -rf $(TMP)/gcc ; mkdir $(TMP)/gcc ; cd $(TMP)/gcc ;\
		$(XPATH) $< $(CFG_ALL) $(GCC_CFG) && $(MAKE) && $(MAKE) install

binutils: $(CROSS)/bin/$(TARGET)-ld
$(CROSS)/bin/i386-elf-ld: $(SRC)/$(BINUTILS)/configure
	rm -rf $(TMP)/binutils ; mkdir $(TMP)/binutils ; cd $(TMP)/binutils ;\
		$(XPATH) $< $(CFG_ALL) $(BINUTILS_CFG) && $(MAKE) && $(MAKE) install

# unpack source code

$(SRC)/$(BINUTILS)/configure: $(GZ)/binutils/$(BINUTILS_GZ)
	cd $(SRC) ; xzcat $< | tar x && touch $@
$(SRC)/$(GCC)/configure: $(GZ)/gcc/$(GCC_GZ)
	cd $(SRC) ; xzcat $< | tar x && touch $@

# make directories
dirs:
	mkdir -p $(GZ) $(TMP) $(SRC) $(SYS) $(CROSS)

