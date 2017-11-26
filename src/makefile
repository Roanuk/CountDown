IDIR = ../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR=../lib

LIBS=

_DEPS= main.h actions.h controls.h IO.h
DEPS = $(pathsubst %, $(IDIR)/%,$(_DEPS))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


_OBJ = main.o actions.o controls.o IO.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

	
_testMainOBJ = main.o mockActions.o
testMainOBJ = $(patsubst %,$(ODIR)/%,$(_testMainOBJ))

testMain: $(testMainOBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

	
_testActionOBJ = actionsTester.o actions.o mockControls.o
testOBJ = $(patsubst %,$(ODIR)/%,$(_testActionOBJ))

testActions: $(testActionsOBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
_testControlOBJ = controlsTester.o controls.o mockIO.o
testOBJ = $(patsubst %,$(ODIR)/%,$(_testControlOBJ))

testControls: $(testControlsOBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o '~ core $(IDIR)/'~
