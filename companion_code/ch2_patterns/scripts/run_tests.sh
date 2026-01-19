#!/bin/bash
set -e

# --- Configuration ---
DEFAULT_BUILD_DIR="tests/build" 

# Variables
MODULE_ROOT=""
CPPUTEST_HOME_ARG=""
BUILD_DIR_ARG=""
MAKE_TARGET=""

# --- 1. Argument Parsing ---
while getopts ":c:b:t:w:" opt; do
  case "$opt" in
    c) CPPUTEST_HOME_ARG="$OPTARG" ;;
    b) BUILD_DIR_ARG="$OPTARG" ;;
    t) MAKE_TARGET="$OPTARG" ;;
    w) MODULE_ROOT="$OPTARG" ;;  
    \?) ;; 
  esac
done

# --- 2. Resolve Module Root ---
if [ -z "$MODULE_ROOT" ]; then
    # MANUAL RUN FALLBACK:
    # If -w is missing, assume we are in /scripts/ and the root is one level up.
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
elif [ -d "$HOME/cpputest" ]; then
    export CPPUTEST_HOME="$HOME/cpputest"
    echo "  - CPPUTEST_HOME: $CPPUTEST_HOME (Auto-detected)"
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
if [ -n "$MAKE_TARGET" ]; then
    make "WORKSPACE_PATH=$MODULE_ROOT" "$MAKE_TARGET"
else
    make "WORKSPACE_PATH=$MODULE_ROOT"
fi

echo "--- Module Tests Passed ---"