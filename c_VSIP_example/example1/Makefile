## Created RJudd
## SPAWARSYSCEN San Diego
## $Id: Makefile,v 2.0 2003/02/22 15:27:21 judd Exp $

## Top Level of library distribution
## RDIR=$(HOME)/local
RDIR=../..
## C compiler
CC=cc
INCLUDEDIR=-I$(RDIR)/include
LIBDIR=-L$(RDIR)/lib
LIBS= -lvsip -lm
OPTIONS=-O2

example: example1.c
	$(CC) -o example1 example1.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS) 

clean:
	rm -f example1 example1.exe
