#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
# The name of the library or executable being generated
COMPONENT_NAME = patterns_lib

#--- Inputs ----#
# The root directory of your project (usually the current directory)
PROJECT_HOME_DIR = .

# --- CppUTest Location Verification ---
ifeq "$(CPPUTEST_HOME)" ""
$(error The environment variable CPPUTEST_HOME is not set. \
Set it to where cpputest is installed)
endif

# --- Platform Compatibility (Windows/MSYS2) ---
# These lines convert Windows paths (C:\foo) to MSYS Unix paths (/c/foo).
# If you are running strictly on Linux, these are harmless but unnecessary.
CPPUTEST_HOME := $(subst \,/,$(CPPUTEST_HOME))
CPPUTEST_HOME := $(subst C:,/c,$(CPPUTEST_HOME))

# --- Workspace Configuration ---
# '?' allows you to override this from the command line: make WORKSPACE_PATH=...
# defaulting to /workspace/ creates a dependency on a specific folder structure.
# Consider changing this to "." if the makefile is in the root of the repo.
WORKSPACE_PATH ?= /workspace/

# --- Source Code Configuration ---
# SRC_FILES: Explicit individual files
SRC_FILES += $(WORKSPACE_PATH)/src/rectangle.c
SRC_FILES += $(WORKSPACE_PATH)/src/circle.c
SRC_FILES += $(WORKSPACE_PATH)/src/triangle.c
SRC_FILES += $(WORKSPACE_PATH)/src/shape.c
SRC_FILES += $(WORKSPACE_PATH)/src/shape_rectangle.c
SRC_FILES += $(WORKSPACE_PATH)/src/shape_circle.c
SRC_FILES += $(WORKSPACE_PATH)/src/shape_triangle.c
#SRC_FILES += $(WORKSPACE_PATH)/src/shape_api.c
# SRC_DIRS: Directories to search for .c and .cpp files
# Note: You can append multiple dirs using +=
# SRC_DIRS += $(WORKSPACE_PATH)/src/

# --- Test Code Configuration ---
# TEST_SRC_FILES: Explicit individual test files (often the main runner)
TEST_SRC_FILES += $(WORKSPACE_PATH)/tests/srctest/AllTests.cpp
TEST_SRC_FILES += $(WORKSPACE_PATH)/tests/srctest/rectagleTests.cpp
TEST_SRC_FILES += $(WORKSPACE_PATH)/tests/srctest/circleTests.cpp
TEST_SRC_FILES += $(WORKSPACE_PATH)/tests/srctest/triangleTests.cpp	

TEST_SRC_FILES += $(WORKSPACE_PATH)/tests/srctest/familyTests.cpp

# TEST_SRC_DIRS: Directories containing test source code
#TEST_SRC_DIRS += $(WORKSPACE_PATH)/tests/srctest

# --- Mocks and Stubs ---
# MOCKS_SRC_DIRS: Directories for mocks (GoogleMock or CppUMock) and stubs.
# CppUTest will compile everything found here.
MOCKS_SRC_DIRS += $(WORKSPACE_PATH)/tests/mocks
MOCKS_SRC_DIRS += $(WORKSPACE_PATH)/tests/helpers
MOCKS_SRC_DIRS += $(WORKSPACE_PATH)/tests/stubs

# --- CppUMock ---
# Set to Y to enable the CppUMock extension (mocking framework)
CPPUTEST_USE_EXTENSIONS = Y

# --- Includes ---
# Directories to look for header files (.h)
INCLUDE_DIRS += $(CPPUTEST_HOME)/include
INCLUDE_DIRS += $(WORKSPACE_PATH)/include
INCLUDE_DIRS += $(WORKSPACE_PATH)/tests/helpers/include
INCLUDE_DIRS += $(WORKSPACE_PATH)/tests/mocks/include
INCLUDE_DIRS += $(WORKSPACE_PATH)/tests/stubs/include

# --- Build Artifacts ---
# Where object files (.o) and dependency files (.d) go
CPPUTEST_OBJS_DIR = test-obj
# Where the final static library (.a) goes
CPPUTEST_LIB_DIR = test-lib

# ==========================================
#      COMPILER CONFIGURATION 
# ==========================================

# 1. COMPILER EXECUTABLES
# Uncomment these to enforce a specific compiler version (e.g., gcc-10)
# Default is just 'gcc' and 'g++'
# CC = gcc
# CXX = g++

# 2. C FLAGS (Apply ONLY to .c files)
# Add your C standard here (e.g., -std=c99, -std=c11, -std=gnu99)
CPPUTEST_CFLAGS += -std=c99
CPPUTEST_CFLAGS += -DDISABLE_DLIBC_OVERRIDES -D_DEBUG -D_CONSOLE

# 3. C++ FLAGS (Apply ONLY to .cpp files)
# Used for your Test files and C++ production code
CPPUTEST_CXXFLAGS += --std=c++14

# 4. CPP FLAGS (Preprocessor flags, applied to BOTH C and C++)
CPPUTEST_CPPFLAGS += -DDISABLE_DLIBC_OVERRIDES -D_DEBUG -D_CONSOLE

# 5. LINKER FLAGS
CPPUTEST_EXE_FLAGS += -c

# --- External Libraries ---
# If your code uses math.h, you might need -lm
# LD_LIBRARIES += -lm

# --- The Heavy Lifting ---
# This includes the standard CppUTest makefile rules.
# It handles the actual compilation recipes.
include $(CPPUTEST_HOME)/build/MakefileWorker.mk