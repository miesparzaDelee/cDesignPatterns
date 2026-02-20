#!/bin/bash
set -e

# --- Configuration ---
DEFAULT_BUILD_DIR="tests/build" 

# Variables
MODULE_ROOT=""
CPPUTEST_HOME_ARG=""
BUILD_DIR_ARG=""
MAKE_TARGET=""
TEST_ARGS_ARG=""

# --- 1. Argument Parsing ---
while getopts ":c:b:t:w:a:g:" opt; do
  case "$opt" in
    c) CPPUTEST_HOME_ARG="$OPTARG" ;;
    b) BUILD_DIR_ARG="$OPTARG" ;;
    t) 
        if [ "$OPTARG" == "clean" ]; then
            MAKE_TARGET="$OPTARG"
        else
            TEST_ARGS_ARG="$TEST_ARGS_ARG -g $OPTARG"
        fi
        ;;
    w) MODULE_ROOT="$OPTARG" ;;  
    a) TEST_ARGS_ARG="$OPTARG" ;;
    g) TEST_ARGS_ARG="$TEST_ARGS_ARG -g $OPTARG" ;; # Append group filter
    \?) ;; 
  esac
done

# --- 2. Resolve Module Root ---
if [ -z "$MODULE_ROOT" ]; then
    # MANUAL RUN FALLBACK:
    # If -w is missing, assume we are in /build/ and the root is one level up.
    SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
    MODULE_ROOT="$(dirname "$SCRIPT_DIR")"
    echo "  - Module Root: $MODULE_ROOT (Auto-detected)"
else
    echo "  - Module Root: $MODULE_ROOT (Argument)"
fi

# Sanity Check
if [ ! -d "$MODULE_ROOT/src" ]; then
    echo "ERROR: Could not find 'src' in $MODULE_ROOT"
    exit 1
fi

# --- 3. Set CPPUTEST_HOME ---
if [ -n "$CPPUTEST_HOME_ARG" ]; then
    export CPPUTEST_HOME="$CPPUTEST_HOME_ARG"
elif [ -n "$CPPUTEST_HOME" ]; then
    : # Already set
# ... existing checks ...
elif [ -d "$HOME/cpputest" ]; then
    export CPPUTEST_HOME="$HOME/cpputest"
    echo "  - CPPUTEST_HOME: $CPPUTEST_HOME (Auto-detected)"
elif [ -d "/usr/share/cpputest" ]; then
    export CPPUTEST_HOME="/usr/share/cpputest"
    echo "  - CPPUTEST_HOME: $CPPUTEST_HOME (Auto-detected System Package)"
else
    echo "ERROR: CPPUTEST_HOME not set."
    exit 1
fi

# --- 4. Execution ---
TARGET_BUILD_DIR="${BUILD_DIR_ARG:-$DEFAULT_BUILD_DIR}"
FULL_BUILD_PATH="$MODULE_ROOT/$TARGET_BUILD_DIR"

if [ ! -d "$FULL_BUILD_PATH" ]; then
    echo "ERROR: Build directory not found: $FULL_BUILD_PATH"
    exit 1
fi

cd "$FULL_BUILD_PATH"
echo "  - Building in: $TARGET_BUILD_DIR"

# --- THE FIX ---
# We explicitly override the Makefile's internal WORKSPACE_PATH variable.
# This forces it to look in the correct folder, ignoring the "/workspace/" default.
MAKE_COMMAND="make WORKSPACE_PATH=$MODULE_ROOT"

if [ -n "$TEST_ARGS_ARG" ]; then
    MAKE_COMMAND="$MAKE_COMMAND CPPUTEST_EXE_FLAGS=\"$TEST_ARGS_ARG\""
fi

if [ -n "$MAKE_TARGET" ]; then
    eval "$MAKE_COMMAND $MAKE_TARGET"
else
    eval "$MAKE_COMMAND"
fi

echo "--- Module Tests Passed ---"
