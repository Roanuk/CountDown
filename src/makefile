IDIR = ../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR=../lib

LIBS=

_DEPS= main.h SevenSegment.h Matrix.h CoolBars.h Input.h
DEPS = $(pathsubst %, $(IDIR)/%,$(_DEPS))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -I/usr/include/python2.7


_OBJ = main.o SevenSegment.o Matrix.o CoolBars.o Input.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o '~ core $(IDIR)/'~
