# bcFORTH
### bytecode-based FORTH in GNU Forth

https://groups.google.com/forum/#!topic/comp.lang.forth/eYiPcW8uPRY

This is a meta way to write bytecode-based FORTH
written in gforth (as most known portable system) without any external tools.

Use this manual to start with gforth:
* https://www.complang.tuwien.ac.at/forth/gforth/Docs-html/index.html

## Windows build requirements

- **gforth** 0.7.0
  * https://www.complang.tuwien.ac.at/forth/gforth/gforth-0.7.0.exe

### optionals: for developer

- **MinGW** (x32 or x64): GNU gcc make
  * https://osdn.net/projects/mingw/releases/
- **git**
  * https://git-scm.com/
- **(g)Vim**
  * https://www.vim.org/download.php

## Install (Windows/MinGW)

```
$ git clone -o gh -b dev https://github.com/ponyatov/nuFORTH.git
$ cd nuFORTH/gforth
$ mingw32-make
```

