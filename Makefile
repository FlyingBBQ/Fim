#
# Fim - makefile
# Author: FlyingBBQ
#

GAME = Fim

CC = gcc
CFLAGS = -Wall -pedantic -Werror -g -MMD -MP
LFLAGS := $(shell sdl2-config --libs) -lSDL2_image

SRCDIR  = ./src
TESTDIR = ./test
BUILDIR ?= ./build

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:%.c=$(BUILDIR)/%.o)
DEPS = $(OBJS:.o=.d)

$(BUILDIR)/$(GAME): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LFLAGS)

$(BUILDIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

.PHONY: clean run

clean:
	rm -rf $(BUILDIR)

run: $(BUILDIR)/$(GAME)
	./$(BUILDIR)/$(GAME)
