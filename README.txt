o ---------------------------------------------------------------------------- o
| Linked lists for the C programming language by Simon Euchner                 |
o ---------------------------------------------------------------------------- o


LICENSE NOTICE.

    LICENSES: GPL-3.0

    IMPORTANT: THIS IS FREE SOFTWARE WITHOUT ANY WARRANTY. THE USER IS IF FREE
               TO MODIFY AND REDISTRIBUTE THIS SOFTWARE UNDER THE TERMS OF THE
               LICENSE LISTED ABOVE PUBLISHED BY THE FREE SOFTWARE FOUNDATION.
               THE PUBLISHER, SIMON EUCHNER, IS NOT RESPONSIBLE FOR ANY NEGATIVE
               EFFECTS THIS SOFTWARE MAY CAUSE.

Description.

    This is a simple C library for linked lists. There is only a single source
    file, *src.d/llist.c*. In this file all functions listed in *inc.d/llist.h*
    are implemented. To use the library include the header *inc.d/llist.h* in
    youre C file and compile with the object code *obj.d/llist.o*. In the header
    you can set the data type for the lists. To use different data types at
    once, just use copy the library, set the data types and rename the functions
    in this libraray such that they do not clash with the functions for the
    other data type. Documentation is given in the comments above the function
    implementations in *src.d/llist.c*. Alternatively, to compiling with the
    object file manually, you can also linke against the library *llist.so*.


Notes.

    I have mostly avoided recursion, because for very long (with 'long' being
    defined by the stack size) lists the overhead introduced by the function
    calls fills up the stack.


Installation.

    Only the files *obj.d/llist.o* and *inc.d/llist.h* are needed. The header is
    laready provided and the object code is generated with the *Makefile*. The
    makefile also builds and runs a text program, located in *tst.d*. To clean
    up run *make clean*. The tests also showcase how the library is used.
