CFLAGS = -Wall -pedantic -Werror -g
LFLAGS := $(shell sdl2-config --libs) -lSDL2_image
OBJS = sprites.o gfx.o init.o input.o main.o 
PROG = game
CXX = gcc

# top-level rule to create the program.
all: $(PROG)

# compiling other source files.
%.o: src/%.c src/%.h src/defs.h src/structs.h
	$(CXX) $(CFLAGS) -c -s $<

# linking the program.
$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG) $(LFLAGS)

# cleaning everything that can be automatically recreated with "make".
clean:
	rm $(PROG) *.o
