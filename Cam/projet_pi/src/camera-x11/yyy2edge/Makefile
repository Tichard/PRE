##############################################################################################

PROJ=yyy2edge

TARGET  =
CC      = $(TARGET)gcc
OBJCOPY = $(TARGET)objcopy
AS      = $(TARGET)gcc -x assembler-with-cpp -c
SIZE    = $(TARGET)size
OBJDUMP = $(TARGET)objdump

# List all default C defines here
DDEFS = -O2 -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE

# List all default directories to look for include files here
DINCDIR = . /usr/include/freetype2

# List the default directory to look for the libraries here
DLIBDIR = -L/usr/X11R6/lib

# List all default libraries here
DLIBS = -lX11 -lXext -lXft -lpthread

# C source files here
SRC  = src/yyy2edge.c src/graphics.c

#
# End of user defines
#############################################################################

INCDIR  = $(patsubst %,-I%,$(DINCDIR))
LIBDIR  = $(patsubst %,-L%,$(DLIBDIR))
DEFS    = $(DDEFS)
LIBS    = $(DLIBS)

OBJS      = $(SRC:%.c=%.o)

CFLAGS = $(INCDIR) $(MCFLAGS) $(DEBUG) $(OPT) -fomit-frame-pointer -Wall -std=c99 $(DEFS)
LDFLAGS = -Wl,-Map=$@.map,--gc-sections $(LIBDIR)

# Generate dependency information
CFLAGS += -MD -MP -MF .dep/$(@F).d

#
# makefile rules
#
all: $(PROJ)

$(PROJ): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	-rm -f $(OBJS)
	-rm -f $(PROJ)
	-rm -f *.map
	-rm -fR .dep

# 
# Include the dependency files, should be the last of the makefile
#
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

.PHONY: clean

