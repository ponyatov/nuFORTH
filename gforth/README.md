# bcFORTH
## bytecode-based FORTH in GNU Forth
### This is a meta way to write bytecode-based FORTH

https://groups.google.com/forum/#!topic/comp.lang.forth/eYiPcW8uPRY

It is a byte-code based FORTH
- written in gforth (as the most known portable system) and
- runs inside it without any external tools.

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

# to run without any build tools

- download
  * https://github.com/ponyatov/nuFORTH/blob/dev/gforth/bcFORTH.fs
- run it
```
$ gforth bcFORTH.fs
```

## Reference FORTH specially designed for tiny embedded

Supports 
* `.32bit`
* reduced `.16bit`
* experimental `.8bit` for IoT/sensor clouds

