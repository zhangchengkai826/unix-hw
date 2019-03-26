IDIR=../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR=../lib

_DEPS = apue.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = apue.o fig5-12.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

fig5-12.out: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS)	

.PHONY: clean
clean:
	rm -f $(ODIR)/* *~ core $(IDIR)/*~
