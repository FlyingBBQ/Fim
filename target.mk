# Create empty object list that will be filled during target creation.
OBJS =

# The VPATH is searched for sources when compiling the objects.
VPATH = $(SRC_DIR) $(TEST_DIR)

# Define generic functions to compile sources for a target:
# Arguments:
# 1. target name
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
# 1. target build directory
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
