
ifeq ($(OS),Windows_NT)
	HEXDUMP = od -t x1
else
	HEXDUMP = hexdump -C
endif

FORTH.bc: bcFORTH.fs Makefile
	gforth $< && echo ; echo ; $(HEXDUMP) $@

.PHONY: clean
clean:
	rm -rf *~ .*~ *.bc

