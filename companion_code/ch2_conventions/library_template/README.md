# Library Template — Chapter 2 Conventions

A ready-to-clone library scaffold that embodies the coding standards and conventions from **Chapter 2: Recommended Practices and Conventions**.

## Purpose

Copy this folder to start a new library that is convention-compliant from the start. Each file contains section markers referencing the relevant convention IDs.

## Structure

```text
library_template/
├── .gitignore                          # FO-03
├── README.md                           # FO-03
├── LICENSE                             # FO-03
├── inc/                                # FO-01: Public API headers
│   └── module.h                        # CS-03, CS-04, NC-01→05, DO-01
├── src/                                # FO-01: Implementation
│   └── module.c                        # CS-08, CS-09, NC-06, DO-02
├── build/                              # FO-02, UT-03: Build & test scripts
│   ├── Makefile                        # Library build
│   ├── run_tests.sh                    # POSIX test runner
│   └── run_tests.ps1                   # Windows WSL wrapper
├── dist/                               # FO-02: Build artifacts (gitignored)
├── docs/adr/                           # CS-02: Architecture Decision Records
│   ├── 000_template.md
│   └── 001_example_buffering.md
└── tests/                              # UT-01, UT-02
    ├── build/Makefile                  # CppUTest build config
    ├── srctest/                        # Test suites + runner
    │   ├── AllTests.cpp
    │   └── moduleTests.cpp             # UT-09 template
    ├── helpers/                         # UT-08
    ├── mocks/
    └── stubs/
```

## Convention Coverage

| File | Conventions |
|------|-------------|
| Folder layout | FO-01, FO-02, FO-03 |
| `inc/module.h` | CS-03, CS-04, CS-05, NC-01→05, DO-01 |
| `src/module.c` | CS-08, CS-09, NC-06, DO-02 |
| `docs/adr/` | CS-02 |
| `tests/` | UT-01, UT-02, UT-03, UT-04, UT-05, UT-06, UT-07, UT-09 |

## Quick Start

```bash
# 1. Copy the template
cp -r library_template/ my_new_library/

# 2. Rename module files to match your module name
mv my_new_library/inc/module.h   my_new_library/inc/my_module.h
mv my_new_library/src/module.c   my_new_library/src/my_module.c

# 3. Search-replace "module" → "my_module" across all files
# 4. Update this README and LICENSE with your project details
```

## Building the Library

The `build/Makefile` compiles all sources in `src/` into a static library in `dist/`:

```bash
cd build
make clean && make
# Output: ../dist/libmodule.a
```

## Developing

1. **Design the header first** (CS-01) — define your API in `inc/module.h`
2. **Implement** in `src/module.c` following the section layout (CS-09)
3. **Write tests** in `tests/srctest/moduleTests.cpp` following UT-09
4. **Document decisions** in `docs/adr/` using the ADR template (CS-02)

The skeleton files contain section markers (e.g., `[CS-04]`, `[NC-01]`) referencing each convention so you can see exactly which rule governs each section.

## Running Tests

Tests use **CppUTest** and run via WSL on Windows or natively on Linux.

### Prerequisites

- Linux or WSL environment
- CppUTest framework installed (system-wide at `/usr/share/cpputest` or in `~/cpputest`)

### Run All Tests

```bash
# Linux
./build/run_tests.sh

# Windows (PowerShell → WSL)
.\build\run_tests.ps1
```

### Run a Specific Test Group

```bash
./build/run_tests.sh -t Module_Usage
.\build\run_tests.ps1 -t Module_Usage
```

### Clean Build Artifacts

```bash
./build/run_tests.sh -t clean
```
