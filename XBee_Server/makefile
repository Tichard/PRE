# ###---- MAKEFILE ---- ####

# define project directories
INCDIR = include
SRCDIR = src
ODIR   = src/obj
LDIR   = lib

#define variables
EXEC    = mainXBee
CC      = gcc
CFLAGS  = -I$(INCDIR)
LIBS    = -lm


# get all the header files
_DEPS = $(wildcard $(INCDIR)/*.h)
DEPS  = $(patsubst %,%,$(_DEPS))

# create list of object files
_OBJ = $(patsubst %.c,%.o,$(wildcard $(SRCDIR)/*.c))
OBJ  = $(patsubst $(SRCDIR)/%,$(ODIR)/%,$(_OBJ))

# make object files
$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	@mkdir -p $(ODIR)
	@$(CC) -c -o $@ $< $(CFLAGS)

# compile exectutable file
$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


# various others command
.PHONY: clean

clean:
	@rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	@rm -f $(EXEC)
