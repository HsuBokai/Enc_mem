IDIR =./include
CC=gcc
CFLAGS=-I$(IDIR) `pkg-config --cflags --libs glib-2.0`  -lgcrypt

ODIR=.
LDIR =./lib

_DEPS = enc_mem.h my_crypto.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o enc_mem.o my_crypto.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

target = main

$(target): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(target)
