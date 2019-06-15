#
# Fim - makefile
# Author: FlyingBBQ
#

GAME = Fim

CXX = gcc
CFLAGS = -Wall -pedantic -Werror -g
LFLAGS := $(shell sdl2-config --libs) -lSDL2_image

SRCDIR  = src
OBJDIR  = bin
TESTDIR = test

SOURCES  := $(wildcard $(SRCDIR)/*.c)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# top-level rule to create the program.
all: $(GAME)

# compiling the source files
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CXX) $(CFLAGS) -c -s $< -o $@

# linking the program
$(GAME): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LFLAGS) -o $(GAME)

clean:
	rm $(GAME) $(OBJDIR)/*.o
