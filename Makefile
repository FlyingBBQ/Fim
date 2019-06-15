#
# Fim - makefile
# Author: FlyingBBQ
#

GAME = Fim
TEST = Test

CC = gcc
CFLAGS = -Wall -pedantic -Werror -g -MMD -MP
LFLAGS := $(shell sdl2-config --libs) -lSDL2_image
TFLAGS := -lcmocka

SRCDIR   = src
TESTDIR  = test
BUILDIR ?= build

SRCS = $(wildcard $(SRCDIR)/*.c )
OBJS = $(SRCS:%.c=$(BUILDIR)/%.o)
TEST_SRCS = $(wildcard $(TESTDIR)/*.c)
TEST_OBJS = $(TEST_SRCS:%.c=$(BUILDIR)/%.o)

DEPS = $(OBJS:.o=.d)

$(BUILDIR)/$(GAME): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LFLAGS)

$(BUILDIR)/$(TEST): $(TEST_OBJS)
	$(CC) $(TEST_OBJS) -o $@ $(TFLAGS)

$(BUILDIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

.PHONY: clean run

clean:
	rm -rf $(BUILDIR)

run: $(BUILDIR)/$(GAME)
	./$(BUILDIR)/$(GAME)

test: $(BUILDIR)/$(TEST)
	./$(BUILDIR)/$(TEST)
