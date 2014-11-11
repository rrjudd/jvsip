## Created RJudd
## SPAWARSYSCEN San Diego
## $Id: Makefile,v 2.0 2003/02/22 15:27:33 judd Exp $

## Top Level of library distribution
## RDIR=$(HOME)/local
RDIR=../..
## C compiler
CC=cc
INCLUDEDIR=-I$(RDIR)/include
LIBDIR=-L$(RDIR)/lib
LIBS=-lvsip -lm
OPTIONS=-O2

example: example17.c
	$(CC) -o example17 example17.c $(OPTIONS) $(INCLUDEDIR) $(LIBDIR) $(LIBS) 

clean:
	rm -f example17 example17.exe
