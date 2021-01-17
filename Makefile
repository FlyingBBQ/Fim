#
# Fim - makefile
# Author: FlyingBBQ
#

EXE  = fim
LIB  = $(addprefix lib, $(addsuffix .a, $(EXE)))
TEST = $(addsuffix _test, $(EXE))

CC = gcc -std=c99
OPT ?= -O2
CFLAGS = -Wall -Werror -Wextra -Wshadow -Wundef -Wconversion -Wpedantic \
		 -Wformat=2 -Wnull-dereference -Wlogical-op \
		 $(OPT) -MMD -MP
LFLAGS := $(shell sdl2-config --libs) -lSDL2_image
TFLAGS := -lcmocka

SRCDIR   = src
DOCDIR   = docs
TESTDIR  = test
BUILDIR ?= build

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:%.c=$(BUILDIR)/%.o)
TEST_SRCS = $(wildcard $(TESTDIR)/*.c)
TEST_OBJS = $(TEST_SRCS:%.c=$(BUILDIR)/%.o)

DEPS = $(OBJS:.o=.d)

MAKEFLAGS := --jobs=$(shell nproc)

mkdir_check = $(if $(wildcard $(@D)),,mkdir -p $(@D))

$(BUILDIR)/$(EXE): $(BUILDIR)/$(LIB)
	$(CC) $(filter %main.o, $(OBJS)) -o $@ -L$(BUILDIR) -l$(EXE) $(LFLAGS)

$(BUILDIR)/$(LIB): $(OBJS)
	$(AR) rcs $@ $(filter-out %main.o, $(OBJS))

$(BUILDIR)/$(TEST): $(TEST_OBJS)
	$(CC) $(TEST_OBJS) -o $@ $(TFLAGS)

$(BUILDIR)/%.o: %.c
	$(mkdir_check)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

.PHONY: clean run test docs covr format release

clean:
	rm -rf $(BUILDIR)

run: $(BUILDIR)/$(EXE)
	./$(BUILDIR)/$(EXE)

build_test: OPT = -O0
build_test: CFLAGS += -ftest-coverage -fprofile-arcs -Wno-unused-parameter
build_test: LFLAGS += -lgcov
build_test: TFLAGS += -lgcov
build_test: $(BUILDIR)/$(TEST)

test: build_test
	./$(BUILDIR)/$(TEST)

docs: | $(DOCDIR)/Doxyfile
	doxygen $(DOCDIR)/Doxyfile

covr: build_test
	./$(BUILDIR)/$(TEST) > /dev/null
	gcovr $(BUILDIR)/$(TESTDIR) -r $(SRCDIR)

format:
	astyle --project=astylerc $(SRCDIR)/*.c $(SRCDIR)/*.h $(TESTDIR)/*.c

release: covr
	CMOCKA_XML_FILE=$(BUILDIR)/%g.xml CMOCKA_MESSAGE_OUTPUT=xml ./$(BUILDIR)/$(TEST)
	gcovr $(BUILDIR)/$(TESTDIR) -r $(SRCDIR) --html-details -o $(BUILDIR)/test.html
