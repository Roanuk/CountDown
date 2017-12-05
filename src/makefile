IDIR = ../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR=../lib

LIBS=-lpython2.7

_DEPS= main.h PythonCaller.h
DEPS = $(pathsubst %, $(IDIR)/%,$(_DEPS))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -I/usr/include/python2.7


_OBJ = main.o PythonCaller.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o '~ core $(IDIR)/'~
