FORTH.bc: bcFORTH.fs Makefile
	gforth $< && echo ; od -t x1 -w 16 $@

.PHONY: clean
clean:
	rm -rf *~ .*~ *.bc

