\ https://groups.google.com/forum/#!topic/comp.lang.forth/eYiPcW8uPRY

VOCABULARY TC	\ target compiler vocabulary

\ words			\ will print main system vocabulary

ONLY FORTH ALSO TC DEFINITIONS	\ configure vocabulary search order/compiling

words

0x1000 constant Msz	\ main memory size

Msz .
words

bye

