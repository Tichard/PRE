##############################################################################################

PROJ=sample_app

TARGET  =
CC      = $(TARGET)gcc
OBJCOPY = $(TARGET)objcopy
AS      = $(TARGET)gcc -x assembler-with-cpp -c
SIZE    = $(TARGET)size
OBJDUMP = $(TARGET)objdump

# List all default C defines here, like -D_DEBUG=1
DDEFS = -g -DDBG -O0

# List all default directories to look for include files here
DINCDIR = .

# List the default directory to look for the libraries here
DLIBDIR =

# List all default libraries here
DLIBS =

# C source files here
SRC  = src/main.c

#
# End of user defines
#############################################################################

INCDIR  = $(patsubst %,-I%,$(DINCDIR))
LIBDIR  = $(patsubst %,-L%,$(DLIBDIR))
DEFS    = $(DDEFS)
LIBS    = $(DLIBS)

OBJS      = $(SRC:%.c=%.o)

CFLAGS = $(INCDIR) $(MCFLAGS) $(DEBUG) $(OPT) -fomit-frame-pointer -Wall -std=c99 -DDBG -D_POSIX_C_SOURCE=200809L $(DEFS)
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

