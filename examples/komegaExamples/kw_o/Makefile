MAKE=make
CFLAGS=-O3
DFLAGS=
LIBS= -lvsip -lm
CC=clang

HEADERS = kw.h ts.h
SOURCE = param.m kw.m ts.m beamformer_ex.m

all:beamformer

beamformer:$(SOURCE) $(HEADERS)
	$(CC) -o beamformer_ex $(SOURCE) $(CFLAGS) -framework jvsipF -framework Foundation
       

clean:
	rm -f *.o beamformer_ex  gramOut

