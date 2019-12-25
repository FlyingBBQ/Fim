#
# Fim - makefile
# Author: FlyingBBQ
#

GAME = Fim
TEST = Test

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g -MMD -MP 
LFLAGS := $(shell sdl2-config --libs) -lSDL2_image # -lgcov
TFLAGS := -lcmocka # -lgcov

SRCDIR   = src
DOCDIR   = docs
TESTDIR  = test
BUILDIR ?= build

SRCS = $(wildcard $(SRCDIR)/*.c )
OBJS = $(SRCS:%.c=$(BUILDIR)/%.o)
TEST_SRCS = $(wildcard $(TESTDIR)/*.c)
TEST_OBJS = $(TEST_SRCS:%.c=$(BUILDIR)/%.o)

DEPS = $(OBJS:.o=.d)

mkdir_check = $(if $(wildcard $(@D)),,mkdir -p $(@D))

$(BUILDIR)/$(GAME): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LFLAGS)

$(BUILDIR)/$(TEST): $(TEST_OBJS)
	$(CC) $(TEST_OBJS) -o $@ $(TFLAGS)

$(BUILDIR)/%.o: %.c
	$(mkdir_check)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

.PHONY: clean run test docs covr format

clean:
	rm -rf $(BUILDIR)

run: $(BUILDIR)/$(GAME)
	./$(BUILDIR)/$(GAME)

build_test: CFLAGS += -ftest-coverage -fprofile-arcs -Wno-unused-parameter
build_test: LFLAGS += -lgcov
build_test: TFLAGS += -lgcov
build_test: $(BUILDIR)/$(TEST)

test: build_test
	./$(BUILDIR)/$(TEST)

docs: | $(DOCDIR)/Doxyfile
	doxygen $(DOCDIR)/Doxyfile

#covr: $(BUILDIR)/$(TEST)
covr: build_test
	./$(BUILDIR)/$(TEST) > /dev/null
	gcovr $(BUILDIR)/$(TESTDIR) -r $(SRCDIR)

format:
	astyle --project=astylerc $(SRCDIR)/*.c $(SRCDIR)/*.h $(TESTDIR)/*.c
