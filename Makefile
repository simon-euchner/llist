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
# Makefile for the library *llist* by Simon Euchner.                           #
#                                                                              #
# ---------------------------------------------------------------------------- #


### Directoties
SRC=./src.d/
OBJ=./obj.d/
BIN=./bin.d/
TST=./tst.d/

### Compiler and linker
OL=1
LIB=-lm
CMPLE=${CC} -O${OL}
LINK=${CC} -O${OL} ${LIB}

### Run
all: ${BIN}test.out
	@echo "Compiling library"
	@echo "Running test program"
	${BIN}test.out

### Link
${BIN}test.out: ${OBJ}test.o ${OBJ}llist.o
	${LINK} ${OBJ}llist.o ${OBJ}test.o -o ${BIN}test.out

### Compile

# test.c
${OBJ}test.o: ${TST}test.c
	${CMPLE} -c ${TST}test.c -o ${OBJ}test.o

# llist.c
${OBJ}llist.o: ${SRC}llist.c
	${CMPLE} -c ${SRC}llist.c -o ${OBJ}llist.o

### Cleanup
clean:
	rm ${OBJ}*.o
	rm ${BIN}*.out
.PHONY: clean
