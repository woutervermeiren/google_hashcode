IDIR=lib
CC=g++
CFLAGS=-I$(IDIR) -O3
$(info $(CFLAGS))

ODIR=src
LDIR=lib

LIBS=-lm

_DEPS = FileHandler.h Algorithm.h Defines.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = GoogleHash.o FileHandler.o Algorithm.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

googlehash: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

