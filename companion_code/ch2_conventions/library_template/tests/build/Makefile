#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = module_lib

#--- Inputs ----#
PROJECT_HOME_DIR = .

# --- CppUTest Location Verification ---
ifeq "$(CPPUTEST_HOME)" ""
$(error The environment variable CPPUTEST_HOME is not set. \
Set it to where cpputest is installed)
endif

# --- Platform Compatibility (Windows/MSYS2) ---
CPPUTEST_HOME := $(subst \,/,$(CPPUTEST_HOME))
CPPUTEST_HOME := $(subst C:,/c,$(CPPUTEST_HOME))

# --- Workspace Configuration ---
WORKSPACE_PATH ?= /workspace/

# --- Source Code Configuration ---
SRC_FILES += $(WORKSPACE_PATH)/src/module.c

# --- Test Code Configuration ---
TEST_SRC_FILES += $(WORKSPACE_PATH)/tests/srctest/AllTests.cpp
TEST_SRC_FILES += $(WORKSPACE_PATH)/tests/srctest/moduleTests.cpp

# --- Mocks and Stubs ---
MOCKS_SRC_DIRS += $(WORKSPACE_PATH)/tests/mocks
MOCKS_SRC_DIRS += $(WORKSPACE_PATH)/tests/helpers
MOCKS_SRC_DIRS += $(WORKSPACE_PATH)/tests/stubs

# --- CppUMock ---
CPPUTEST_USE_EXTENSIONS = Y

# --- Includes ---
INCLUDE_DIRS += $(CPPUTEST_HOME)/include
INCLUDE_DIRS += $(WORKSPACE_PATH)/inc
INCLUDE_DIRS += $(WORKSPACE_PATH)/tests/helpers/include
INCLUDE_DIRS += $(WORKSPACE_PATH)/tests/mocks/include
INCLUDE_DIRS += $(WORKSPACE_PATH)/tests/stubs/include

# --- Build Artifacts ---
TEST_OUTPUT_DIR = ../out

CPPUTEST_OBJS_DIR = $(TEST_OUTPUT_DIR)/test-obj
CPPUTEST_LIB_DIR = $(TEST_OUTPUT_DIR)/test-lib

TEST_TARGET = $(TEST_OUTPUT_DIR)/$(COMPONENT_NAME)_tests

# ==========================================
#      COMPILER CONFIGURATION
# ==========================================

# C FLAGS
CPPUTEST_CFLAGS += -std=c99
CPPUTEST_CFLAGS += -DDISABLE_DLIBC_OVERRIDES -D_DEBUG -D_CONSOLE

# C++ FLAGS
CPPUTEST_CXXFLAGS += --std=c++14

# CPP FLAGS (Preprocessor, applied to BOTH C and C++)
CPPUTEST_CPPFLAGS += -DDISABLE_DLIBC_OVERRIDES -D_DEBUG -D_CONSOLE

# LINKER FLAGS
CPPUTEST_EXE_FLAGS += -c

# --- The Heavy Lifting ---
include $(CPPUTEST_HOME)/build/MakefileWorker.mk
