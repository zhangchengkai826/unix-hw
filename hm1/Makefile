IDIR=./include
CC=gcc
CFLAGS=-I$(IDIR) -ansi -g -Wall -Werror -Wextra -Wformat=2 -Wjump-misses-init -Wlogical-op -Wpedantic -Wshadow

ODIR=obj

_DEPS = common.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ_TCP = common.o tcp.o
OBJ_TCP = $(patsubst %,$(ODIR)/%,$(_OBJ_TCP))

_OBJ_TCPM = common.o tcpm.o
OBJ_TCPM = $(patsubst %,$(ODIR)/%,$(_OBJ_TCPM))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tcp: $(OBJ_TCP) 
	$(CC) -o $@ $^ $(CFLAGS)	

tcpm: $(OBJ_TCPM) 
	$(CC) -o $@ $^ $(CFLAGS)	

.PHONY: clean
clean:
	rm -f $(ODIR)/* *~ core $(IDIR)/*~

