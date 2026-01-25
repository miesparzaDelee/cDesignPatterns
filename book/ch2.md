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
void uart_init(uart_config_t* config);          // init function
void uart_sendByte(uint8_t byte);               // Action function  
uart_status_t uart_getStatus(void);             // Query function

// Module: lcd
typedef struct lcd_config_t {                   // Type with module prefix
    uint8_t width;
    uint8_t height;
} lcd_config_t;
```

</convention>

<convention id="NC-02" title="Function Semantic Naming">

**Standard**: Use consistent semantic suffixes for functions to communicate their purpose and usage pattern across the codebase.

**Rationale**: Repeated use of the same suffixes creates a shared vocabulary across modules, enabling developers to immediately recognize function behavior without reading implementation details. This standardization reduces cognitive load and improves code navigability.

**Detail**: Common semantic suffixes include lifecycle management (`_init`, `_deinit`, `_start`, `_stop`), periodic operations (`_task`, `_update`), data processing (`_process`), and event handling (`_handle`). Apply these patterns consistently where they fit, but don't force them where they don't naturally apply. The goal is recognition, not rigid compliance.

**Example**:

```c
// Module: uart (lifecycle + control)
void uart_init(uart_t* self, uart_config_t* config);
void uart_start(uart_t* self);
void uart_stop(uart_t* self);
void uart_deinit(uart_t* self);

// Module: sensor (lifecycle + periodic task)
void sensor_init(sensor_t* self, sensor_config_t* config);
void sensor_task(sensor_t* self);                        // Called periodically
void sensor_deinit(sensor_t* self);

// Module: filter (lifecycle + data processing)
void filter_init(filter_t* self, filter_config_t* config);
void filter_process(filter_t* self, float* data);       // Data transformation
```

</convention>

<convention id="NC-03" title="Typedef Suffix">

**Standard**: User-created typedefs should end with a `_t` suffix.

**Rationale**: Clearly distinguishes types from variables and follows the standard C convention used in POSIX and embedded systems.

**Detail**: Apply the `_t` suffix to all user-defined types including structs, enums, unions, and function pointers. This creates visual consistency and immediately signals that an identifier is a type, not a variable or function.

**Example**:

```c
// Struct typedef
typedef struct {
    uint32_t baudrate;
    uint8_t data_bits;
} uart_config_t;

// Enum typedef
typedef enum {
    STATUS_OK,
    STATUS_ERROR,
    STATUS_BUSY
} status_t;

// Union typedef
typedef union {
    uint32_t word;
    uint8_t bytes[4];
} data_t;

// Function pointer typedef
typedef void (*callback_t)(void* context);
```

</convention>

<convention id="NC-04" title="Handle Prefix">

**Standard**: When passing pointers to structs through APIs, define a handle typedef prefixed with `h` (e.g., `hCircle_t`, `hDevice_t`) instead of using the raw pointer type.

**Rationale**: Using handles improves API readability and reduces clutter. Instead of `myFunc(&myObject)` everywhere, you use `myFunc(myHandle)`. It also provides a clear signal that this type is meant to be passed by reference, and makes the API more consistent and easier to refactor.

**Detail**: A handle is a typedef to a pointer: `typedef struct myStruct * hMyStruct_t;`. This can be used for both visible structs (Object Pattern) and opaque structs (Opaque Pattern).

**Example**:

```c
// Define handle typedef
typedef device_t* hDevice_t;

// API using handles
void device_init(hDevice_t self, device_config_t* config);
void device_process(hDevice_t self);

// Usage
device_t myDevice;
hDevice_t handle = &myDevice;
device_init(handle, &config);    // Clean and clear
device_process(handle);

// Without handles (for comparison)
device_init(&myDevice, &config); // Direct pointer, less semantic clarity
```

</convention>

<convention id="NC-05" title="Macro Naming">

**Standard**: Macros and definitions should be in UPPER_CASE with underscores (e.g., `MOD_NAME_FEATURE_ENABLE`).

**Rationale**: Follows standard C conventions for preprocessor directives and makes macros immediately distinguishable from functions and variables.

**Detail**: Apply UPPER_CASE to all preprocessor definitions including constants, feature flags, include guards, and function-like macros. This visual distinction prevents accidental misuse and signals that the identifier has preprocessor semantics (text substitution, no type safety). In header files, prefix public macros with the module name to avoid naming conflicts (e.g., `UART_MAX_BUFFER_SIZE`). In source files, simpler names can be used since the context is local and the macro won't be exposed externally.

**Example**:

```c
// uart.h - Header file (public macros with module prefix)
#ifndef UART_H
#define UART_H

#define UART_MAX_BUFFER_SIZE 256
#define UART_DEFAULT_BAUDRATE 9600
#define UART_ENABLE_DMA 1

void uart_init(uart_t* self, uart_config_t* config);

#endif // UART_H

// uart.c - Source file (local macros can use simpler names)
#define RETRY_COUNT 3
#define TIMEOUT_MS 100

// These macros are only visible within this .c file
```

</convention>

#### Internal/Static Scope

<convention id="NC-06" title="Private Naming">

**Standard**: Static variables and functions can follow any clear convention as their context is local.

**Rationale**: Since static identifiers are file-scoped, naming conflicts are not a concern. However, a visual distinction helps readers quickly identify private vs public symbols.

**Detail**: Common MISRA-compliant prefixes include `priv_` (private), `s_` (static), or `local_`. While leading underscore (`_`) is visually appealing and commonly used, it violates MISRA-C Rule 21.1 (reserved identifiers). For projects requiring MISRA compliance, use compliant alternatives. For non-MISRA projects, choose based on team preference and consistency.

**Recommendation**: Use `priv_` for private static variables and no prefix for static functions (since `static` keyword already signals scope).

**Example**:

```c
// uart.c

// Private static variables
static uart_state_t priv_state = {0};
static uint8_t priv_buffer[256];

// Private static functions (no prefix needed)
static void reset_buffer(void) {
    memset(priv_buffer, 0, sizeof(priv_buffer));
}

static bool validate_config(uart_config_t* config) {
    return (config != NULL && config->baudrate > 0);
}

// Public API functions
void uart_init(uart_t* self, uart_config_t* config) {
    if (validate_config(config)) {
        // Initialize...
    }
}
```

</convention>

### Code Structure and Layout

<convention id="CS-01" title="Design First">

**Standard**: Header files should be considered signed contracts; they must be designed, reviewed, and finalized before implementation begins.

**Rationale**: Defining the interface first forces clarity of thought, prevents implementation details from leaking into the design, and establishes a clear contract that guides development.

**Detail**: Headers define the module's public API—what it promises to do, not how it does it. By designing headers first, you create a boundary that separates interface from implementation. This approach enables design review, parallel development, and prevents the common mistake of designing APIs around implementation constraints. Treat header finalization as a milestone: once approved, the contract is set.

**Workflow**:

1. **Design**: Define module purpose, data structures, and function signatures in the header
2. **Review**: Discuss the API with team/stakeholders for clarity and completeness  
3. **Finalize**: Lock the header as the contract
4. **Implement**: Write the `.c` file to fulfill the contract

</convention>

<convention id="CS-02" title="Architecture Decision Records">

**Standard**: Important, complex, or key modules must have an associated ADR documenting the design rationale, alternatives considered, and behavioral contracts.

**Rationale**: Captures the context and "why" behind design decisions, which is crucial for long-term maintenance. ADRs serve as living documentation that travels with the code, preventing knowledge loss and reducing rework.

**Detail**: Use ADRs for modules that are complex, business-critical, or have significant architectural impact. The structure should be defined by your team and adapted to your project needs. ADRs complement CS-01 (Design First) by documenting the decision-making process during header design. Create the ADR before or during header design, not after implementation.

**Suggested Template**:

1. **Title**: Module name and purpose
2. **Status**: Proposed | Accepted | Deprecated
3. **Context**: Problem being solved, constraints
4. **Decision**: What was decided and why
5. **Alternatives Considered**: Other options and why they were rejected
6. **Consequences**: Trade-offs, impacts, future implications

**Example**:

```markdown
# ADR: Sensor Data Buffering

## Status
Accepted

## Context
Need to buffer sensor readings to handle burst data without loss.
Memory constrained to 2KB for this module.

## Decision
Use circular buffer with 100-sample capacity (200 bytes).
Overflow strategy: drop oldest samples.

## Alternatives Considered
- Dynamic allocation: Rejected due to fragmentation risk
- Larger buffer: Exceeds memory budget

## Consequences
- Simple, predictable memory usage
- May lose data during sustained bursts
```

</convention>

<convention id="CS-03" title="Header Content">

**Standard**: Header files must be self-contained (only necessary dependencies) and use include guards to prevent multiple inclusions.

**Rationale**: Ensures modules can be included in any order without compilation errors and prevents redefinition errors during compilation.

**Detail**: A self-contained header includes only dependencies it needs (e.g., `stdint.h` for `uint32_t`) so users don't have to know internal requirements. Use traditional include guards (`#ifndef`/`#define`/`#endif`) for maximum portability across all C compilers.

**Example**:

```c
// device.h
#ifndef DEVICE_H
#define DEVICE_H

// Include dependencies needed by this header
#include <stdint.h>
#include <stdbool.h>

// Type definitions ..


// Function prototypes ..

#endif // DEVICE_H
```

</convention>

<convention id="CS-04" title="Header Organization">

**Standard**: Follow a strict organization pattern: Guard → Includes → Defines → Types → Prototypes.

**Rationale**: Predictable layout makes reading APIs easier for other developers and ensures consistent structure across all modules.

**Detail**: Headers should flow logically from external dependencies to internal definitions to the public API. Within the prototypes section, place lifecycle functions (`_init`, `_deinit`) first, followed by other functions grouped by purpose. This order ensures that definitions are available before use and presents the API in the order users typically need it.

**Example**:

```c
// sensor.h
#ifndef SENSOR_H
#define SENSOR_H

// 1. Includes - external dependencies
#include <stdint.h>
#include <stdbool.h>

// 2. Defines - constants and macros
#define SENSOR_MAX_READINGS 100

// 3. Types - enums, structs, typedefs
typedef enum {
    SENSOR_MODE_ACTIVE,
    SENSOR_MODE_SLEEP
} sensor_mode_t;

typedef struct {
    uint32_t id;
    sensor_mode_t mode;
    float last_reading;
} sensor_t;

typedef struct {
    uint32_t id;
    sensor_mode_t mode;
} sensor_config_t;

// 4. Prototypes - init first, then other functions
void sensor_init(sensor_t* self, sensor_config_t* config);
void sensor_deinit(sensor_t* self);

void sensor_task(sensor_t* self);
float sensor_read(sensor_t* self);
void sensor_setMode(sensor_t* self, sensor_mode_t mode);

#endif // SENSOR_H
```

</convention>

<convention id="CS-05" title="Configuration Structs">

**Standard**: Initialization functions should accept configuration through a dedicated config struct, even for simple cases.

**Rationale**: Config structs provide future extensibility without breaking the API contract. As modules grow, new parameters can be added to the struct without changing function signatures.

**Detail**: Define a `module_config_t` struct containing all initialization parameters and pass it to the `module_init()` function. This pattern allows adding new configuration options later while maintaining backward compatibility through struct initialization. For truly static configuration (compile-time constants), use `#define` directives, but prefer runtime configurability through structs when parameters may vary between instances or deployments.

**Example**:

```c
// device.h

// Configuration structure
typedef struct {
    uint32_t id;
    uint32_t mode;
} device_config_t;

// Init function accepts config struct
void device_init(device_t* self, device_config_t* config);

// Usage - easy to extend config later without changing function signature
device_config_t config = {.id = 1, .mode = 0};
device_t myDevice;
device_init(&myDevice, &config);
```

<convention id="CS-06" title="Discriminated Unions for Variants">

**Standard**: When a function or struct must accept multiple variant types, use a discriminated union with an explicit type field rather than separate parameters or void pointers.

**Rationale**: Keeps variant data compact and type-safe while avoiding brittle parameter lists. A union stores only the largest variant, so the struct size is the maximum of its variants instead of the sum of all variants.

**Detail**: Define a `type` or `kind` field (typically an enum) alongside a union of variant payloads. Initialize the type before use and switch on it when handling the data.

**Example**:

```c
typedef enum {
    bus_mode_uart,
    bus_mode_spi
} bus_mode_t;

typedef struct {
    uint32_t baudrate;
    uint8_t parity;
} uart_config_t;

typedef struct {
    uint32_t bitrate;
    uint8_t polarity;
} spi_config_t;

typedef struct {
    bus_mode_t mode;
    union {
        uart_config_t uart;
        spi_config_t spi;
    } variant;
} bus_config_t;
```

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
