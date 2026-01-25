# Recommended Practices and Conventions

## Practices Forged by Experience

The recommended practices and proposed coding and development conventions detailed in this book are purely pragmatic.
They were gathered and refined through years of professional experience, evolving through a process of natural selection.
Practices that provided clear value remained part of our workflow.
Conversely, those that demanded more effort than the benefit they ultimately provided naturally fell out of use.
During this exploratory period, numerous approaches were tested, adopted, or discarded.
Most derive from gold-standard literature and established conventions in the embedded software world.
Others have been adapted or evolved specifically to support the modular framework presented here.

Using the right tools and strict conventions is critical to the success of the modular approach presented.
We group these practices into four main categories, narrowing our focus to what matters most for embedded modularity.
First, coding standards and conventions—covering file organization, naming, code structure, and documentation—ensure consistency and prevent common pitfalls across the codebase.
Second, hardware emulation approaches allow us to develop and verify logic without constant access to physical boards.
This is often the most challenging aspect of embedded modularization, but special techniques make it manageable.
By leveraging these techniques, we aim to spend as much time as possible in the development environment.
Debugging and testing on the host significantly speeds up the development cycle compared to testing on real hardware.
Third, debug modules and testing strategies enable us to isolate components and verify them continuously.

It is important to note that these are recommendations, not immutable laws.
We try to follow them strictly throughout this book to demonstrate their effectiveness within the EMoD framework.
We encourage the reader to identify how these practices are applied in the chapters that follow.
However, in different contexts or legacy environments, strict adherence might not always be possible or beneficial.

### Convention Format

Throughout this chapter, standards are presented as distinct "Convention" blocks for easy reference. Each block contains:

* **ID**: A unique identifier (e.g., `FO-01`) for referencing in code reviews.
* **Standard**: The rule itself.
* **Rationale**: The "why" behind the rule. Understanding the reason is more important than memorizing the rule; if the rationale no longer applies, the rule should be revisited.

---

## Coding Standards and Conventions

In this section, we define the specific rules that govern our code. The goal is not to be pedantic, but to ensure that any developer can jump into any module and understand the structure immediately. By adhering to these standards, we eliminate low-level decision fatigue and focus our energy on solving the actual problem.

We have organized these standards into four main categories:

1. **File and Folder Organization**: Where things live.
2. **Naming Conventions**: What things are called.
3. **Code Structure and Layout**: How files are constructed.
4. **Documentation**: How we communicate intent.

### File and Folder Organization

<convention id="FO-01" title="Library Organization">

**Standard**: A library groups related modules in one folder with `inc/` for public headers and `src/` for source files.

**Rationale**: A consistent layout makes the API boundary obvious and eliminates guesswork when navigating unfamiliar libraries.

**Detail**: `inc/` is the exported API; `src/` is private implementation.

**Example**:

```text
my_library/
├── inc/                    # Public API headers
│   ├── uart.h
│   ├── spi.h
│   └── i2c.h
├── src/                    # Implementation files
│   ├── uart.c
│   ├── spi.c
│   └── i2c.c
├── test/                   # Unit tests (see UT-01)
├── build/                  # Build scripts (see FO-02)
└── dist/                   # Build artifacts (see FO-02)
```

</convention>

<convention id="FO-02" title="Library Build Artifacts">

**Standard**: Every library has `build/` for build scripts and `dist/` for build outputs.

**Rationale**: A fixed build layout keeps CI, IDE tasks, and local builds aligned.

**Detail**: `build/` holds scripts/configs (Makefiles, CMake, shell scripts). `dist/` is for artifacts (`.a`, `.so`, `.dll`) and must be gitignored.

**Example**:

```text
my_library/
├── build/
│   ├── Makefile            # Build instructions
│   ├── CMakeLists.txt      # Alternative build system
│   └── compile.sh          # Convenience script
└── dist/
    ├── libmylibrary.a      # Static library output
    └── libmylibrary.so     # Shared library output (if applicable)
```

**Workflow**: A typical build command might be:

```bash
cd my_library/build
make clean && make
# Artifact appears in ../dist/
```

</convention>

<convention id="FO-03" title="Library Independence">

**Standard**: A library is a self-contained set of modules that can be versioned and reused independently, typically consumed as a git submodule.

**Rationale**: Independent libraries enable controlled upgrades and reproducible builds across projects.

**Detail**: Each library repository includes its own:

* `.gitignore` - Excludes build artifacts and IDE-specific files
* `README.md` - Library purpose, usage instructions, dependencies, and examples
* `LICENSE` - Licensing terms (critical for reuse across projects)
* Build scripts in `build/` (see FO-02)

These root-level files travel with the library when imported.

**Distribution Modes**: Libraries can be consumed in two ways:

1. **Development mode**: Include the library's `inc/` folder directly in your project's include path. Use this during active development or when modifying the library.
2. **Release mode**: Link against the pre-built artifact from `dist/` and include only necessary headers. Use this for stable dependencies.

**Example**:

```text
project/
├── lib/                    # Git submodules
│   ├── uart_lib/          # Independent library
│   │   ├── .gitignore
│   │   ├── README.md
│   │   ├── inc/
│   │   ├── src/
│   │   ├── build/
│   │   └── dist/
│   └── sensor_lib/        # Another independent library
│       ├── .gitignore
│       ├── README.md
│       └── ...
└── main/                  # Your application
```

</convention>

<convention id="FO-04" title="Module Structure">

**Standard**: A module is the smallest independently testable unit in a library and must include one primary public header (`.h`) and one same-named source file (`.c`).

**Rationale**: The 1:1 header/source mapping makes the contract and implementation easy to locate.

**Detail**: The primary header and source share the same base name (e.g., `uart.h` and `uart.c`). If further abstraction of functionality within the module is needed to improve organization, use sub-modules (FO-05).

**Supplemental Headers**: Modules may use additional headers under `inc/<module>/`, if needed, to organize large APIs (e.g., `inc/graphics/rendering.h`) or private definitions (e.g., `inc/<module>/private/helper.h`).

**Example**:

```text
my_library/
├── inc/
│   ├── uart.h          # Public interface
│   └── uart/
│       └── uart_defs.h # Supplemental header (if needed)
└── src/
    └── uart.c          # Implementation
```

</convention>

<convention id="FO-05" title="Sub-module Splitting">

**Standard**: Sub-modules are internal modules used only by the parent module's `.c` file; they are testable but not part of the public API.

**Rationale**: Keeps the public interface small while allowing complex internals to be split into focused units.

**Detail**: Sub-modules follow the same `.h`/`.c` pairing as regular modules. Their headers are placed in `inc/<module>/` subfolders (following the same pattern as supplemental headers in FO-04) to maintain consistent organization.

**Example**:

```text
my_library/
├── inc/
│   ├── uart.h              # Public interface
│   └── uart/
│       ├── uart_defs.h     # Supplemental header (if needed)
│       ├── uart_rx.h       # Sub-module 1
│       └── uart_tx.h       # Sub-module 2
└── src/
    ├── uart.c              # Main module
    ├── uart_rx.c           # Sub-module 1 implementation
    └── uart_tx.c           # Sub-module 2 implementation
```

</convention>

### Naming Conventions

<convention id="NC-01" title="Public Function/Type Naming">

**Standard**: All public functions and types must be prefixed with the module name.

**Rationale**: Simulates namespacing in C and prevents symbol collisions. In large codebases with multiple libraries, unprefixed names like `init()` or `buffer_t` would clash. The module prefix ensures every symbol is globally unique and self-documenting.

**Style**: Use a mixed convention of underscores and camelCase (e.g., `mod_nameFunction_otherCharacteristics`).

**Detail**: Use underscores (`_`) to separate the module prefix and major concerns, and camelCase (`nameFunction`) for the specific item name. This creates natural visual grouping when viewing API lists.

**Example**:

```c
// Module: uart
void uart_init(uart_config_t* config);          // Lifecycle function
void uart_sendByte(uint8_t byte);               // Action function  
uart_status_t uart_getStatus(void);             // Query function

// Module: lcd
typedef struct lcd_config_t {                   // Type with module prefix
    uint8_t width;
    uint8_t height;
} lcd_config_t;
```

</convention>

<convention id="NC-02" title="Lifecycle Pattern">

**Rationale**: Consistent naming and usage patterns from the start lead to predictable behavior and better maintainability.
</convention>

<convention id="NC-03" title="Typedef Suffix">

**Standard**: User-created typedefs should end with a `_t` suffix.

**Rationale**: clearly distinguishes types from variables.
</convention>

<convention id="NC-04" title="Handle Typedef Prefix">
**Standard**: When passing pointers to structs through APIs, define a handle typedef prefixed with `h` (e.g., `hCircle_t`, `hDevice_t`) instead of using the raw pointer type.
**Detail**: A handle is a typedef to a pointer: `typedef struct myStruct * hMyStruct_t;`. This can be used for both visible structs (Object Pattern) and opaque structs (Opaque Pattern).

**Rationale**: Using handles improves API readability and reduces clutter. Instead of `myFunc(&myObject)` everywhere, you use `myFunc(myHandle)`. It also provides a clear signal that this type is meant to be passed by reference, and makes the API more consistent and easier to refactor.
</convention>

<convention id="NC-05" title="Macro Naming">
**Standard**: Macros and definitions should be in UPPER_CASE with underscores (e.g., `MOD_NAME_FEATURE_ENABLE`).

**Rationale**: Follows standard C conventions for preprocessor directives.
</convention>

#### Internal/Static Scope

<convention id="NC-06" title="Private Naming">
**Standard**: Static variables and functions can follow any clear convention as their context is local.
**Recommendation**: Common practice is to prefix with `s_` or `_` to denote private scope.
</convention>

### Code Structure and Layout

#### Header Files

<convention id="CS-01" title="Header Content">
**Standard**: Header files must be self-contained (include all necessary dependencies) and use include guards to prevent multiple inclusions.

**Rationale**: Ensures modules can be included in any order without compilation errors.
</convention>

<convention id="CS-02" title="Header Organization">
**Standard**: Follow a strict organization pattern: License -> Guard -> Includes -> Defines -> Types -> Prototypes.

**Rationale**: Predictable layout makes reading APIs easier for other developers.
</convention>

<convention id="CS-03" title="Configuration Headers">
**Standard**: Definitions or configuration options should be kept in a separate header file (potentially as a submodule).

**Rationale**:Separates configuration from implementation, facilitating porting and customization.
</convention>

<convention id="CS-04" title="Design First">
**Standard**: Header files should be considered signed contracts; they must be designed, reviewed, and finalized before implementation begins.

**Rationale**: Defining the interface first forces clarity of thought and prevents implementation details from leaking into the design.
</convention>

<convention id="CS-05" title="Architecture Decision Records">
**Standard**: Complex modules must have an associated ADR where the intention, description, and behavioral definitions are discussed and documented.

**Rationale**: Captures the context and "why" behind design decisions, which is crucial for long-term maintenance.
</convention>

<convention id="CS-06" title="config structs on init functions">
**Standard**: Use config structs, even if at first glance does not needed. Modules can easily grow and as stated, those are contract, providing with config structs allows to change and handle improvements wothout breaking current code.

**Rationale**: Captures the context and "why" behind design decisions, which is crucial for long-term maintenance.
</convention>

<convention id="CS-07" title="Discriminated Unions for Variants">
**Standard**: When a function or struct must accept multiple variant types, use a discriminated union combined with a type field rather than separate parameters or void pointers.

**Example**:

```c
typedef struct {
    shape_config_t base;
    union {
        rect_config_t rect;
        circle_config_t circle;
        triangle_config_t triangle;
    } variant;
} factory_config_t;
```

**Rationale**: Unions allow multiple alternative types to share the same memory region, minimizing struct size. The discriminator field (e.g., `base.type`) ensures type safety at runtime by clearly indicating which union member is active. This technique is essential for memory-constrained embedded systems where every byte matters.
</convention>

#### Source Files

<convention id="CS-08" title="Source Content">
**Standard**: The module header must be included first in the source file.

**Rationale**: Verifies that the header is truly self-contained.
</convention>

<convention id="CS-09" title="Source Organization">
**Standard**: Follow a strict organization pattern: Includes -> Macros -> Types -> Private Prototypes -> Private Vars -> Implementations.

**Rationale**: Improves code navigability and consistency.
</convention>

### Documentation

<convention id="DO-01" title="Public API Documentation">
**Standard**: Use comprehensive documentation blocks for header files (the public contract).

**Rationale**: Users of the module should only need to read the header to understand how to use it.
</convention>

<convention id="DO-02" title="Internal Documentation">
**Standard**: Source files can use a relaxed documentation style, focusing on "why" rather than "what".

**Rationale**: Implementation details are subject to change; comments should explain complex logic or design decisions.
</convention>

---

## Unit Testing and Verification

### Philosophy and Tooling

Verification is not an afterthought; it is an integral part of the development process. We advocate for **Test-Driven Development (TDD)**, where tests are written before the implementation. This ensures that the module's behavior is defined by its requirements and that the code is testable by design.

**CppUTest** is our recommended framework. It is a robust C/C++ unit testing framework that allows us to leverage the sophisticated features of C++ for creating powerful mocks and test harnesses while keeping the production code in pure C.

### Unit Testing Standards

<convention id="UT-01" title="Test Organization">
**Standard**: Each library must have a `test` folder. Inside, each module must have a corresponding test file (e.g., `test_module_name.cpp`) where all public API functions are tested.

**Rationale**: Keeps tests close to the code but separated from source, and ensures 1:1 mapping between modules and test suites.
</convention>

<convention id="UT-02" title="Test Independence">
**Standard**: Each test must be self-contained and must not depend on the state or side effects of other tests. Usage of `setup` and `teardown` should ensure a clean state for every test.

**Rationale**: Prevents cascading failures and ensures that tests can be run in any order.
</convention>

<convention id="UT-03" title="Test Naming">
**Standard**: Test names should follow a pattern like `FunctionOrFeature_Condition_ExpectedResult` (e.g., `Init_NullPointer_ReturnsError`).

**Rationale**: Makes failures self-explanatory in the test report.
</convention>

<convention id="UT-04" title="Arrange, Act, Assert">
**Standard**: Test bodies should clearly follow the **AAA** pattern:
1. **Arrange**: Setup the state.
2. **Act**: Call the function under test.
3. **Assert**: Verify the results.

**Rationale**: Improves readability and standardizes test logic.
</convention>

<convention id="UT-05" title="Living Documentation">
**Standard**: Unit tests should serve as executable documentation. They should demonstrate the recommended usage, edge cases, and limits of the module.

**Rationale**: Unlike comments, compiled tests cannot drift out of sync with the code.
</convention>

<convention id="UT-06" title="Test Folder Structure">
**Standard**: The `test` folder should follow a consistent internal structure:
- `runners/`: Contains the `main` entry point and build scripts.
- `src/`: Contains helper source files specific to testing (test doubles, fakes).
- `mocks/`: Contains generated mocks.
- `tests/`: Contains the actual test files (e.g., `ModuleTest.cpp`), mirroring the library's source structure.

**Rationale**: Separates test infrastructure from the test logic itself.
</convention>

<convention id="UT-07" title="Test Helpers">
**Standard**: Shared setup code and complex assertions should be abstracted into helper functions or "Test Objects". These should be located in the `test/src` directory and included as needed.

**Rationale**: Keep valid test functions focused on the AAA pattern and free of clutter.
</convention>

<convention id="UT-08" title="CppUTest Template">
**Standard**: Follow this standard template for new test files:
```cpp
#include "CppUTest/TestHarness.h"

extern "C" {
    #include "module_under_test.h"
    // Mocks and other dependencies
}

TEST_GROUP(Module) {
    void setup() {
        module_init();
    }

    void teardown() {
        module_deinit();
    }
};

TEST(Module, Init_StateIsReset) {
    // Arrange
    // Act
    // Assert
}

```

**Rationale**: Provides a consistent starting point for all developers.
</convention>

<convention id="UT-09" title="Build and Test Automation Scripts">
**Standard**: Each library should include a `scripts/` folder at the module root containing:
- `run_tests.sh`: A shell script for building and running tests on Linux (the primary implementation)
- `invoke_wsl_tests.ps1`: A PowerShell wrapper that invokes the Linux script via WSL on Windows

**Detail**: Use **WSL as the common base environment** for both Windows and Linux development. The Windows PowerShell script should simply call the Linux script through WSL, rather than duplicating logic. This ensures a single source of truth for the build process. Scripts should handle path resolution, CPPUTEST_HOME detection, and build directory management automatically. See `companion_code/ch3_patterns/scripts/` for reference implementations.

**Rationale**: Having a single Linux-based script as the source of truth eliminates duplication and ensures identical behavior across Windows (via WSL), Linux, and CI environments. This approach was discovered through experience—it significantly reduces maintenance burden and prevents platform-specific bugs.
</convention>

## Debugging and Hardware Emulation

<draft>
In this
(Write your ideas for Debugging and Emulation here. How do we debug on host vs target? What is the 'Faking' strategy?)
</draft>
