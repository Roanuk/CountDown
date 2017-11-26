IDIR = ../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR=../lib

LIBS=

_DEPS= main.h
DEPS = $(pathsubst %, $(IDIR)/%,$(_DEPS))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o '~ core $(IDIR)/'~
