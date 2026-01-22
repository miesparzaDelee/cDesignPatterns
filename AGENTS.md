# AGENTS.md - C Design Patterns Repository

This repository contains a C design patterns book with a literate programming build system. Code examples live in `companion_code/ch3_patterns/`, tests use CppUTest framework, and the book is built using Python scripts.

## Build Commands

### Book Build
```bash
python scripts/build_book.py
```
- Reads Markdown chapters from `book/`
- Injects C code from `src/` using `{{ file "path" type="..." }}` tags
- Outputs hydrated Markdown to `build/` and Typst PDF source

### C Pattern Tests (CppUTest)
```bash
# Run from companion_code/ch3_patterns/scripts/
./run_tests.sh

# With specific test target:
./run_tests.sh -t rectagleTests
./run_tests.sh -t circleTests
./run_tests.sh -t triangleTests
./run_tests.sh -t familyTests
./run_tests.sh -t vtableTests

# Specify CppUTest location:
./run_tests.sh -c /path/to/cpputest
```

**Running a single test directly:**
```bash
cd companion_code/ch3_patterns/tests/build
make WORKSPACE_PATH=$PWD/../.. rectagleTests
make WORKSPACE_PATH=$PWD/../.. circleTests
```

**Available test targets:** `rectagleTests`, `circleTests`, `triangleTests`, `familyTests`, `vtableTests`

## Code Style Guidelines

### Naming Conventions
- **Types**: Suffix with `_t` (e.g., `shape_t`, `circle_config_t`)
- **Handles**: Prefix with `h` (e.g., `hCircle_t`, `hShape_t`)
- **Memory blocks**: Suffix with `_memory_t` for opaque allocation structs
- **Constants/Macros**: UPPER_SNAKE_CASE (e.g., `CIRCLE_SIZE`, `PI`)
- **Functions**: `module_functionName` pattern (e.g., `circle_init`, `circle_getArea`)
- **Private members**: Prefix with underscore in internal structs (e.g., `self->_reserved`)

### Types
- Use `<stdint.h>` types: `uint8_t`, `uint32_t`, `int32_t`, etc.
- Use `<stdbool.h>` for boolean values
- Use `<stddef.h>` for `NULL`, `size_t`

### Imports
- System includes first: `<stdio.h>`, `<stdint.h>`, etc.
- Local includes second: `"shape.h"`, `"circle.h"`
- Order: alphabetized within each group

### Header Guards
```c
#ifndef MODULE_NAME_H
#define MODULE_NAME_H
// ... content ...
#endif // MODULE_NAME_H
```

### Error Handling
- Return `NULL` or error codes for failure
- Validate input parameters at function entry
- No exceptions (C does not support them)

### Opaque Pattern (Key Pattern)
Expose size constants and opaque handles in headers; hide implementation:
```c
// In header:
#define CIRCLE_SIZE (2)
typedef struct circle * hCircle_t;
hCircle_t circle_init(circle_memory_t *mem, circle_config_t *config);

// In source:
struct circle { uint32_t radius; float area; };
```

### Code Regions
Use `// region:name` and `// endregion` comments for extraction in book:
```c
void example() {
    int x = 5;
    // region:math_logic
    x = x * 2;
    // endregion
}
```

### Formatting
- 4-space indentation (no tabs)
- Opening brace on same line as function/scope
- Lines wrapped at 80-100 characters

### Memory Management
- Use explicit `uint8_t` byte arrays for opaque memory blocks
- Always initialize memory before use with `memset()` or similar
- Document ownership semantics for all pointer parameters

### Test Conventions
- Test files follow naming: `*Tests.cpp` (CppUTest convention)
- Tests use `TEST_GROUP_*` and `TEST_*` macros
- Mock/stub files in `tests/mocks/`, `tests/stubs/`

## Literate Programming Tags

In `book/*.md`, inject code with:
```
{{ file "path/to/file.c" type="TYPE" name="IDENTIFIER" }}
```

Types: `whole`, `include`, `define`, `typedef`, `struct`, `function`, `region`, `test_group`, `test`

## Directory Structure

- `companion_code/ch3_patterns/src/` - C source files
- `companion_code/ch3_patterns/include/` - Public headers
- `companion_code/ch3_patterns/tests/srctest/` - CppUTest tests
- `companion_code/ch3_patterns/tests/mocks/` - Mock implementations
- `companion_code/ch3_patterns/tests/stubs/` - Stub implementations
- `companion_code/ch3_patterns/tests/helpers/` - Test helpers
- `book/` - Chapter Markdown source
- `scripts/` - Python build tools
- `build/` - Output (hydrated Markdown, PDF source)

## Key Files

- `companion_code/ch3_patterns/tests/build/Makefile` - Test build configuration
- `companion_code/ch3_patterns/scripts/run_tests.sh` - Test runner script
- `scripts/build_book.py` - Book generation script

## Book Development

**IMPORTANT**: Before working on any chapter, check `book/_guide.md` for the current status and notes. This is the single source of truth for book progress.

- **Complete** - Ready for final review, code and tests validated
- **First Draft** - Has section templates and ideas, needs more content
- **Ideas Only** - Initial concepts, not properly revised, needs significant work
- **Not Started** - No content created yet

When completing or modifying chapter content:
1. Update `_guide.md` with new status and notes
2. Ensure code examples compile and tests pass
3. Update `book/structure.txt` if adding new chapters
4. Run `python scripts/build_book.py` to verify build succeeds
