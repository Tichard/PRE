
############################################################################
# project
############################################################################
EXEC=server-fb

DESTDIR = /usr/bin

#
#	sub-directories and source files
#
SRC= fb.c

############################################################################
# C compiler & linker flags 
############################################################################
#CFLAGS=-Wall  -std=c99
CFLAGS= -g -O2 -mtune=cortex-a9 -march=armv7-a -fomit-frame-pointer -mfloat-abi=hard
LDFLAGS=
LIBS= -lm -lwebsockets -lpthread

#CC=sb2 gcc
CC=gcc

############################################################################
# building rules
#
DEPDIR = .deps


OBJS= $(SRC:%.c=%.o)


all:
	mkdir -p $(DEPDIR)
	make $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)
  
%.o: %.c
	@$(CC) -MM $(CFLAGS) -o $(DEPDIR)/$*.d $<
	$(CC) -c $(CFLAGS) $<

-include $(SRC:%.c=$(DEPDIR)/%.d)

  
#
#	install
#
install:
	scp $(EXEC) root@192.168.0.2:$(DESTDIR)/

#
#	uninstall
#
uninstall:

#
#	clean up everything
#
clean:
	rm *.o $(DEPDIR)/*.d $(EXEC)
	
############################################################################

