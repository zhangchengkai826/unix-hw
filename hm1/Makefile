IDIR=./include
CC=gcc
CFLAGS=-I$(IDIR) -ansi -g -Wall -Werror -Wextra -Wformat=2 -Wjump-misses-init -Wlogical-op -Wpedantic -Wshadow

ODIR=obj

_DEPS = common.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = common.o tcp.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tcp: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS)	

.PHONY: clean
clean:
	rm -f $(ODIR)/* *~ core $(IDIR)/*~

