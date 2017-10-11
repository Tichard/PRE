INCDIR =include
SRCDIR =src

EXEC = test

CC=gcc

CFLAGS=-I$(INCDIR)

ODIR=src/obj
LDIR =lib


LIBS=-lm

_DEPS = zigbee.h
DEPS = $(patsubst %,$(INCDIR)/%,$(_DEPS))

_OBJ = zigbee.o test.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	@$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	@gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	@rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	@rm -f $(EXEC)
