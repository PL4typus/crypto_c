#
##

CC	=	gcc 
CFLAGS	=  	-Wall
CFLAGS  += 	-DDEBUG -D_GNU_SOURCE
CFLAGS  += 	-g

PREFIX ?= 	${DESTDIR}/usr
LIBDIR	=	${PREFIX}/lib
INCDIR	=	${PREFIX}/include 
LIBS    =       -lm

CIBLES	=	test

all: $(CIBLES)

clean: 
	$(RM) -f core *.o $(CIBLES) *~


test: test.o crypt.o 
	$(CC) $(CFLAGS) -o $@ test.o crypt.o $(LIBS)

test.o: test.c
		$(CC) $(CFLAGS) -c test.c crypt.h

crypt.o: crypt.c
		$(CC) $(CFLAGS) -c crypt.c

run: clean test
		./test test.txt
