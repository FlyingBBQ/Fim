#
# Fim - makefile
# Author: FlyingBBQ
#

PROG = game

CXX = gcc
CFLAGS = -Wall -pedantic -Werror -g -Iinc
LFLAGS := $(shell sdl2-config --libs) -lSDL2_image

SRCDIR   = src
INCDIR   = inc
OBJDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# top-level rule to create the program.
all: $(PROG)

# compiling the source files
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CXX) $(CFLAGS) -c -s $< -o $@

# linking the program 
$(PROG): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LFLAGS) -o $(PROG)

clean:
	rm $(PROG) $(OBJDIR)/*.o
