MAKE=make
CFLAGS=
DFLAGS= -O3
LIBS= -lvsip -lm
CC=cc
INCLUDE=-I../../../include
LIBDIR=-L../../../lib

HEADERS = param.h kw.h ts.h
         
SOURCE = param.c kw.c ts.c beamformer_ex.c
OBJECTS = param.o kw.o ts.o 

all:beamformer

param.o:param.c param.h 
	$(CC) -c $(DFLAGS) param.c $(INCLUDE)

kw.o:kw.c kw.h param.h
	$(CC) -c $(DFLAGS) kw.c $(INCLUDE)

ts.o:ts.c ts.h param.h
	$(CC) -c $(DFLAGS) ts.c $(INCLUDE)

beamformer: beamformer_ex.c param.h kw.h ts.h $(OBJECTS) $(SOURCE) $(HEADERS)
	cc -o beamformer_ex $(DFLAGS) $(CFLAGS) beamformer_ex.c\
        $(OBJECTS) $(INCLUDE) $(LIBDIR) $(LIBS)

clean:
	rm -f *.o beamformer_ex  gramOut

