#
# Fim - makefile
# Author: FlyingBBQ
#

# Targets:
EXE    = fim
TEST   = $(addsuffix _test, $(EXE))
TARGET = $(EXE) $(TEST)

# Compile and linker flags:
CC   = gcc -std=c99
OPT ?= -O2

CCFLAGS = -Wall -Werror -Wextra -Wshadow -Wundef -Wconversion -Wpedantic \
		  -Wformat=2 -Wnull-dereference -Wlogical-op \
		  $(OPT) -MMD -MP
LFLAGS := $(shell sdl2-config --libs) -lSDL2_image
TFLAGS := -lcmocka

# Directories:
BUILD_DIR ?= build
SRC_DIR    = src
TEST_DIR   = test
DOC_DIR    = docs

# The VPATH is searched for sources when compiling the objects.
VPATH = $(SRC_DIR) $(TEST_DIR)

# Define the sources that are used for the targets.
$(EXE)_SRCS = $(wildcard $(SRC_DIR)/*.c)

FILTER = %main.c
$(TEST)_SRCS = $(filter-out $(FILTER),$($(EXE)_SRCS))
$(TEST)_SRCS += $(wildcard $(TEST_DIR)/*.c)

# Create object list that will be filled during target creation.
OBJS =

# Define generic functions to compile sources for a target:
# Arguments:
# 1. target
# 2. list of sources
define create_target =
$(1)_DIR = $(BUILD_DIR)/$(1)
$(1)_OBJS = $(addprefix $$($(1)_DIR)/, $(addsuffix .o, $(notdir $($(1)_SRCS))))
OBJS += $$($(1)_OBJS)

$(call compile_objects,$$($(1)_DIR))

.PHONY: $(1)
$(1)_T: $$($(1)_OBJS)
	@echo Linking $(1)
	$(HIDE)$(CC) $$($(1)_OBJS) -o $(1) $$(LFLAGS)
endef

# Arguments:
# 1. (target) build directory
define compile_objects =
$(1):
	@echo Creating directory $$@
	$(HIDE)mkdir -p $$@

$(1)/%.c.o: %.c | $(1)
	@echo Compiling $$@
	$(HIDE)$(CC) $$(CCFLAGS) -c $$< -o $$@ -I$(SRC_DIR)
endef

# Create dependencies (needs CCFLAGS += -MMD -MP).
DEPS = $(OBJS:.o=.d)
-include $(DEPS)

# Verbose mode. Enable with 'make V=1'
HIDE ?= @
ifeq ($(V),1)
	HIDE =
else
	# Enable parallel builds when verbose mode is disabled.
	MAKEFLAGS := --jobs=$(shell nproc)
endif

# Invoke the function to create all targets.
$(foreach t,$(TARGET),$(eval $(call create_target,$(t))))

# Add dependencies and custom compiler/linker flags for each target.
$(EXE): $(EXE)_T

$(TEST): OPT = -O0 -g
$(TEST): CCFLAGS += -Wno-unused-parameter
$(TEST): CCFLAGS += -DUNIT_TESTING
$(TEST): CCFLAGS += --coverage
$(TEST): LFLAGS  += --coverage
$(TEST): LFLAGS  += -lcmocka
$(TEST): $(TEST)_T

# Set de default goal.
.DEFAULT_GOAL := $(EXE)

# Define custom targets:
.PHONY: all
all: $(TARGET)

.PHONY: test
test: $(TEST)
	./$(TEST)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(EXE)
	rm -f $(TEST)

# Report coverage for the files that have unit tests.
TEST_SRCS = $(filter-out %main.c,$(wildcard $(TEST_DIR)/*.c))
TEST_COVR_FILTER = $(foreach f,$(TEST_SRCS),$(subst $(TEST_DIR)/test_,-f $(SRC_DIR)/,$(f)))
.PHONY: covr
covr: test
	$(HIDE)gcovr $(BUILD_DIR)/$(TEST) -r $(SRC_DIR) -s $(TEST_COVR_FILTER)

.PHONY: docs
docs: | $(DOC_DIR)/Doxyfile
	doxygen $(DOC_DIR)/Doxyfile

.PHONY: format
format:
	astyle --project=astylerc $(SRC_DIR)/*.c $(SRC_DIR)/*.h $(TEST_DIR)/*.c
