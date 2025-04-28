# ---------------------------------------------------------------------------- #
#                                                                              #
# LICENSE NOTICE.                                                              #
#                                                                              #
#     LICENSES: GPL-3.0                                                        #
#                                                                              #
#     IMPORTANT: THIS IS FREE SOFTWARE WITHOUT ANY WARRANTY. THE USER IS FREE  #
#                TO MODIFY AND REDISTRIBUTE THIS SOFTWARE UNDER THE TERMS OF   #
#                THE LICENSE LISTED ABOVE PUBLISHED BY THE FREE SOFTWARE       #
#                FOUNDATION. THE PUBLISHER, SIMON EUCHNER, IS NOT RESPONSIBLE  #
#                FOR ANY NEGATIVE EFFECTS THIS SOFTWARE MAY CAUSE.             #
#                                                                              #
# ---------------------------------------------------------------------------- #
#                                                                              #
# Makefile for the library *llist.so* by Simon Euchner.                        #
#                                                                              #
# ---------------------------------------------------------------------------- #


### Directoties
SRC=../src.d/
OBJ=../obj.d/
LIB=./
TST=../tst.d/

### Compiler and linker
OL=1
CMPLE=${CC} -O${OL} -fPIC
LINK=${CC} -O${OL} -lm -shared

### Run
all: ${LIB}libllist.so
	@echo "Building library"

### Link
${LIB}libllist.so: ${OBJ}llist.o
	${LINK} -fPIC -shared ${OBJ}llist.o -o ${LIB}libllist.so -lm

### Compile

# llist.c
${OBJ}llist.o: ${SRC}llist.c
	${CMPLE} -c ${SRC}llist.c -o ${OBJ}llist.o

### Cleanup
clean:
	rm ${LIB}*.so
.PHONY: clean
