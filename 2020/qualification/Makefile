IDIR=lib
CC=g++
CFLAGS=-I$(IDIR) -O3 -std=c++14
$(info $(CFLAGS))

ODIR=src
LDIR=lib

LIBS=-lm

_DEPS = FileHandler.h Algorithm.h Defines.h Library.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = GoogleHash.o FileHandler.o Algorithm.o Library.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(ODIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

googlehash: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

