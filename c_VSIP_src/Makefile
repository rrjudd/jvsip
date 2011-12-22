CC=gcc
INCLUDE=-I./

CFLAGS= -O3 -Wall -std=c89 -pedantic -arch x86_64
SOURCE:=$(wildcard *.c)
OBJECTS:=$(patsubst %.c,%.o,$(SOURCE))
FUNC:=$(patsubst %.c,%(),$(SOURCE))
ARCHIVE=libvsip.a
AR=ar -rcvs

$(ARCHIVE):$(OBJECTS)
	$(AR) $(ARCHIVE) $(OBJECTS)

%o: %c 
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ 

file1:
	echo $(SOURCE) > file1

clean:
	rm -f *.o

cleanall:
	rm -f *.o $(ARCHIVE)
