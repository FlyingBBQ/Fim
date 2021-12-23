#
# Fim - makefile
# Author: FlyingBBQ
#

# Targets:
EXE    = fim
TEST   = $(addsuffix _test, $(EXE))
TARGET = $(EXE) $(TEST)

# Compile and linker flags:
CC   = gcc -std=c17
OPT ?= -O2

CCFLAGS = $(OPT) -MMD -MP
CCFLAGS += -Wall -Wextra -Wpedantic
CCFLAGS += -Wshadow -Wformat=2 -Wconversion
CCFLAGS += -Wmissing-include-dirs
CCFLAGS += -Werror
LFLAGS := $(shell sdl2-config --libs) -lSDL2_image

# Directories:
BUILD_DIR ?= build
SRC_DIR    = src
TEST_DIR   = test
DOC_DIR    = docs

# Define the sources that are used for the targets.
$(EXE)_SRCS = $(wildcard $(SRC_DIR)/*.c)

FILTER = %main.c
$(TEST)_SRCS = $(filter-out $(FILTER),$($(EXE)_SRCS))
$(TEST)_SRCS += $(wildcard $(TEST_DIR)/*.c)

# Include makefile with functions to create target rules.
include target.mk

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
