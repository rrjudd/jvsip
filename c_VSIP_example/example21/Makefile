## Created RJudd

## Top Level of JVSIP distribution
RDIR=../..
## C compiler
CC=cc
INCLUDEDIR=-I$(RDIR)/include
LIBDIR=-L$(RDIR)/lib
LIBS= -lvsip -lm
OPTIONS=-O2

example:example21.c
	$(CC) -o example21 example21.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS) 

clean:
	rm -f example21 example21.exe gram_output
