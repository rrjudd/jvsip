## Created RJudd
## use gnu's make if possible
MAKE=make
## Any ansi C compiler here
CC=gcc
## Options are compiler dependent but I think these are fairly standard
CFLAGS=-O3 -Wall -std=c89 -pedantic
## Archiver
AR=ar
## Archiver options
AR_OPTIONS=rcvs
ARLIB=libvsip.a
SRC=c_VSIP_src
MKDIR := mkdir -p
INCLUDE:=include
LIB:=lib


vsip:
	(cd $(SRC); $(MAKE) MAKE='$(MAKE)' CC='$(CC)' CFLAGS='$(CFLAGS)'; \
        AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIB)';)
	if test -d $(LIB); then echo '$(LIB) exists'; else $(MKDIR) $(LIB); fi
	if test -d $(INCLUDE); then echo '$(INCLUDE) exists'; else $(MKDIR) $(INCLUDE); fi
	if test $(SRC)/$(ARLIB); then cp $(SRC)/$(ARLIB) $(LIB)/$(ARLIB); fi
	cp $(SRC)/vsip.h $(INCLUDE)/vsip.h

clean:
	(cd $(SRC); $(MAKE) clean)

cleanall:
	(cd $(SRC); $(MAKE) cleanall)

sterile:
	(cd $(SRC); $(MAKE) cleanall)
	rm -rf $(INCLUDE)
	rm -rf $(LIB)
