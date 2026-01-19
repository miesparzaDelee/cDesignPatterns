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

#### Library and Project Structure
<!--raw-typst #convention(id: "FO-02", title: "Library Organization")[
**Standard**: A set of modules should be kept in the same folder (Library). Headers are included in an `inc` folder, source files in the library root or `src` folder.

**Rationale**: Promotes modularity and clean separation of interface and implementation within libraries.
] -->

<!--raw-typst #convention(id: "FO-03", title: "Library Build Artifacts")[
**Standard**: Libraries should have a `build` folder for instructions/scripts and a `dist` folder for the built artifact.

**Rationale**: Standardizes the build methodology across different libraries.
] -->

<!--raw-typst #convention(id: "FO-04", title: "Library Independence")[
**Standard**: Libraries should be groups of modules organized by purpose, usable independently, and imported as git submodules.

**Rationale**: Allows for independent versioning, updating, and reuse across multiple projects.
] -->

#### The Module Unit
<!--raw-typst #convention(id: "FO-01", title: "Module Structure")[
**Standard**: A module must consist of exactly one public header file (`.h`) and one, same-named private source file (`.c`).

**Rationale**: Enforces clear boundaries. The header is the contract; the source is the implementation.
] -->

#### Sub-modules
<!--raw-typst #convention(id: "FO-05", title: "Sub-module Splitting")[
**Standard**: If a module becomes too complex, split it into sub-modules (additional .h/.c pairs). Submodule headers should be clearly named or placed in subfolders (e.g., `#include "module/submodule.h"`).

**Rationale**: Keeps file sizes manageable and complexity encapsulated without breaking the module abstraction.
] -->

### Naming Conventions

#### Public API
<!--raw-typst #convention(id: "NC-01", title: "Public Function/Type Naming")[
**Standard**: All public functions and types must be prefixed with the module name.
**Style**: Use a mixed convention of underscores and camelCase (e.g., `mod_nameFunction_otherCharacteristics`).
**Detail**: Use underscores (`_`) to separate the module prefix and major concerns, and camelCase (`nameFunction`) for the specific item name.

**Rationale**: Simulates namespacing in C and prevents symbol collisions.
] -->

#### Module Lifecycle
<!--raw-typst #convention(id: "NC-02", title: "Lifecycle Pattern")[
**Standard**: Modules should follow a standardized `init`, `deinit`, and `task` lifecycle pattern where applicable.

**Rationale**: Consistent naming and usage patterns from the start lead to predictable behavior and better maintainability.
] -->

#### Types and Macros
<!--raw-typst #convention(id: "NC-03", title: "Typedef Suffix")[
**Standard**: User-created typedefs should end with a `_t` suffix.

**Rationale**: clearly distinguishes types from variables.
] -->

<!--raw-typst #convention(id: "NC-04", title: "Macro Naming")[
**Standard**: Macros and definitions should be in UPPER_CASE with underscores (e.g., `MOD_NAME_FEATURE_ENABLE`).

**Rationale**: Follows standard C conventions for preprocessor directives.
] -->

#### Internal/Static Scope
<!--raw-typst #convention(id: "NC-05", title: "Private Naming")[
**Standard**: Static variables and functions can follow any clear convention as their context is local.
**Recommendation**: Common practice is to prefix with `s_` or `_` to denote private scope.
] -->

### Code Structure and Layout

#### Header Files
<!--raw-typst #convention(id: "CS-01", title: "Header Content")[
**Standard**: Header files must be self-contained (include all necessary dependencies) and use include guards to prevent multiple inclusions.

**Rationale**: Ensures modules can be included in any order without compilation errors.
] -->

<!--raw-typst #convention(id: "CS-02", title: "Header Organization")[
**Standard**: Follow a strict organization pattern: License -> Guard -> Includes -> Defines -> Types -> Prototypes.

**Rationale**: Predictable layout makes reading APIs easier for other developers.
] -->

<!--raw-typst #convention(id: "CS-03", title: "Configuration Headers")[
**Standard**: Definitions or configuration options should be kept in a separate header file (potentially as a submodule).

**Rationale**:Separates configuration from implementation, facilitating porting and customization.
] -->

<!--raw-typst #convention(id: "CS-04", title: "Design First")[
**Standard**: Header files should be considered signed contracts; they must be designed, reviewed, and finalized before implementation begins.

**Rationale**: Defining the interface first forces clarity of thought and prevents implementation details from leaking into the design.
] -->

<!--raw-typst #convention(id: "CS-05", title: "Architecture Decision Records")[
**Standard**: Complex modules must have an associated ADR where the intention, description, and behavioral definitions are discussed and documented.

**Rationale**: Captures the context and "why" behind design decisions, which is crucial for long-term maintenance.
] -->

<!--raw-typst #convention(id: "CS-06", title: "config structs on init functions")[
**Standard**: Use config structs, even if at first glance does not needed. Modules can easily grow and as stated, those are contract, providing with config structs allows to change and handle improvements wothout breaking current code.

**Rationale**: Captures the context and "why" behind design decisions, which is crucial for long-term maintenance.
] -->

#### Source Files
<!--raw-typst #convention(id: "CS-07", title: "Source Content")[
**Standard**: The module header must be included first in the source file.

**Rationale**: Verifies that the header is truly self-contained.
] -->

<!--raw-typst #convention(id: "CS-08", title: "Source Organization")[
**Standard**: Follow a strict organization pattern: Includes -> Macros -> Types -> Private Prototypes -> Private Vars -> Implementations.

**Rationale**: Improves code navigability and consistency.
] -->

### Documentation

<!--raw-typst #convention(id: "DO-01", title: "Public API Documentation")[
**Standard**: Use comprehensive documentation blocks for header files (the public contract).

**Rationale**: Users of the module should only need to read the header to understand how to use it.
] -->

<!--raw-typst #convention(id: "DO-02", title: "Internal Documentation")[
**Standard**: Source files can use a relaxed documentation style, focusing on "why" rather than "what".

**Rationale**: Implementation details are subject to change; comments should explain complex logic or design decisions.
] -->

---

## Unit Testing and Verification

### Philosophy and Tooling

Verification is not an afterthought; it is an integral part of the development process. We advocate for **Test-Driven Development (TDD)**, where tests are written before the implementation. This ensures that the module's behavior is defined by its requirements and that the code is testable by design.

**CppUTest** is our recommended framework. It is a robust C/C++ unit testing framework that allows us to leverage the sophisticated features of C++ for creating powerful mocks and test harnesses while keeping the production code in pure C.

### Unit Testing Standards

<!--raw-typst #convention(id: "UT-01", title: "Test Organization")[
**Standard**: Each library must have a `test` folder. Inside, each module must have a corresponding test file (e.g., `test_module_name.cpp`) where all public API functions are tested.

**Rationale**: Keeps tests close to the code but separated from source, and ensures 1:1 mapping between modules and test suites.
] -->

<!--raw-typst #convention(id: "UT-02", title: "Test Independence")[
**Standard**: Each test must be self-contained and must not depend on the state or side effects of other tests. Usage of `setup` and `teardown` should ensure a clean state for every test.

**Rationale**: Prevents cascading failures and ensures that tests can be run in any order.
] -->

<!--raw-typst #convention(id: "UT-03", title: "Test Naming")[
**Standard**: Test names should follow a pattern like `FunctionOrFeature_Condition_ExpectedResult` (e.g., `Init_NullPointer_ReturnsError`).

**Rationale**: Makes failures self-explanatory in the test report.
] -->

<!--raw-typst #convention(id: "UT-04", title: "Arrange, Act, Assert")[
**Standard**: Test bodies should clearly follow the **AAA** pattern:
1. **Arrange**: Setup the state.
2. **Act**: Call the function under test.
3. **Assert**: Verify the results.

**Rationale**: Improves readability and standardizes test logic.
] -->

<!--raw-typst #convention(id: "UT-05", title: "Living Documentation")[
**Standard**: Unit tests should serve as executable documentation. They should demonstrate the recommended usage, edge cases, and limits of the module.

**Rationale**: Unlike comments, compiled tests cannot drift out of sync with the code.
] -->

<!--raw-typst #convention(id: "UT-06", title: "Test Folder Structure")[
**Standard**: The `test` folder should follow a consistent internal structure:
- `runners/`: Contains the `main` entry point and build scripts.
- `src/`: Contains helper source files specific to testing (test doubles, fakes).
- `mocks/`: Contains generated mocks.
- `tests/`: Contains the actual test files (e.g., `ModuleTest.cpp`), mirroring the library's source structure.

**Rationale**: Separates test infrastructure from the test logic itself.
] -->

<!--raw-typst #convention(id: "UT-07", title: "Test Helpers")[
**Standard**: Shared setup code and complex assertions should be abstracted into helper functions or "Test Objects". These should be located in the `test/src` directory and included as needed.

**Rationale**: Keep valid test functions focused on the AAA pattern and free of clutter.
] -->

<!--raw-typst #convention(id: "UT-08", title: "CppUTest Template")[
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
] -->

## Debugging and Hardware Emulation

<!--raw-typst #draft[
In this
(Write your ideas for Debugging and Emulation here. How do we debug on host vs target? What is the 'Faking' strategy?)
] -->
