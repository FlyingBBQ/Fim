#
# Fim - makefile
# Author: FlyingBBQ
#

EXE  = fim
LIB  = $(addprefix lib, $(addsuffix .a, $(EXE)))
TEST = $(addsuffix _test, $(EXE))

CC = gcc -std=c99
OPT ?= -O2
CFLAGS = $(OPT) -MMD -MP
#CFLAGS = -Wall -Werror -Wextra -Wshadow -Wundef -Wconversion -Wpedantic \
		 -Wformat=2 -Wnull-dereference -Wlogical-op \
		 $(OPT) -MMD -MP
LFLAGS := $(shell sdl2-config --libs) -lSDL2_image
TFLAGS := -lcmocka

SRCDIR   = src
DOCDIR   = docs
TESTDIR  = test
BUILDIR ?= build

VPATH = $(SRCDIR)

TARGET = $(foreach t, $(EXE), $(addprefix $(BUILDIR)/, $(t)))
SOURCEDIRS = $(foreach directory, $(TARGET), $(addsuffix /$(SRCDIR), $(directory)))

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(addsuffix .o, $(subst $(SRCDIR),$(SOURCEDIRS),$(SRCS)))

TEST_SRCS = $(wildcard $(TESTDIR)/*.c)
TEST_OBJS = $(TEST_SRCS:%.c=$(BUILDIR)/%.o)

DEPS = $(OBJS:.o=.d)

MAKEFLAGS := --jobs=$(shell nproc)


$(TARGET)/$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LFLAGS)

$(BUILDIR)/$(LIB): $(OBJS)
	$(AR) rcs $@ $(filter-out %main.o, $(OBJS))

$(BUILDIR)/$(TEST): $(TEST_OBJS) | $(BUILDIR)/$(LIB)
	$(CC) $(TEST_OBJS) -o $@ -L$(BUILDIR) -l$(EXE) $(TFLAGS)

define generate_rules =
$(1):
	@echo Creating directory $$@
	@mkdir -p $$@

$(1)/%.c.o: %.c | $(1)
	@echo Building $$@
	@$(CC) $(CFLAGS) -c $$< -o $$@ -I$(SRCDIR)
endef

-include $(DEPS)

$(foreach targetdir, $(SOURCEDIRS), $(eval $(call generate_rules, $(targetdir))))

.PHONY: clean run test docs format release

clean:
	rm -rf $(BUILDIR)

run: $(BUILDIR)/$(EXE)
	./$(BUILDIR)/$(EXE)

build_test: OPT = -O0
build_test: CFLAGS += -Wno-unused-parameter
build_test: $(BUILDIR)/$(TEST)

test: build_test
	./$(BUILDIR)/$(TEST)

docs: | $(DOCDIR)/Doxyfile
	doxygen $(DOCDIR)/Doxyfile

format:
	astyle --project=astylerc $(SRCDIR)/*.c $(SRCDIR)/*.h $(TESTDIR)/*.c

release:
	CMOCKA_XML_FILE=$(BUILDIR)/%g.xml CMOCKA_MESSAGE_OUTPUT=xml ./$(BUILDIR)/$(TEST)
