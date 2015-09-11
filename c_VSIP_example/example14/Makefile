## Created RJudd

## Top Level of library distribution
RDIR=../..
## C compiler
CC=cc
INCLUDEDIR=-I$(RDIR)/include
LIBDIR=-L$(RDIR)/lib
LIBS= -lvsip -lm
OPTIONS=-O2

example: example14.c
	$(CC) -o example14 example14.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS) 

clean:
	rm -f example14 example14.exe
