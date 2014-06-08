bbclib
======

An experimental clib. Code is taken from some of my (very) old applications. 


debug_printf
------------

This _printf_ was done to get formatted output on RS232, from embedded software. 
I try to get a nice version which does not use too much memory and which is safe to use.

Usage is very similar to _printf_ with limitations. 

- %s : to print a string (all modifiers are ignored).
- %c : to print a char (all modifiers are ignored).
- %[0][_n_][l]d : to print integers (_cf._ (1)) in decimal. Modifiers are :
    - [0] fill with 0 or spaces (default),
    - [_n_] length of filling, must be at most 32 (_cf._ (2)),
    - [l] long integer (_cf._ (1)).
- %[0][_n_][l]x : to print integers in hexadecimal. Modifiers are as above.
- %[0][_n_][l]b : to print integers in binary. Modifiers are as above.

Notes:

- (1) Integers are 16 bits wide and long integers are 32 bits wide.
- (2) No control is done about field length.
