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
We group these practices into three main categories, narrowing our focus to what matters most for embedded modularity.
First, coding standards and conventions ensure consistency and prevent common pitfalls across the codebase and across the team.
Second, hardware emulation approaches allow us to develop and verify logic without constant access to physical boards.
This is often the most challenging aspect of embedded modularization, but special techniques make it manageable.
By leveraging these techniques, we aim to spend as much time as possible in the development environment.
Debugging and testing on the host significantly speeds up the development cycle compared to testing on real hardware.
Third, debug modules and testing strategies enable us to isolate components and verify them continuously.

It is important to note that these are recommendations, not immutable laws.
We try to follow them strictly throughout this book to demonstrate their effectiveness within the EMoD framework.
We encourage the reader to identify how these practices are applied in the chapters that follow.
However, in different contexts or legacy environments, strict adherence might not always be possible or beneficial.

---

## Coding Standards and Conventions

<!--raw-typst #draft[
In this section, we define the specific rules that govern our code.
The goal is not to be pedantic, but to ensure that any developer can jump into any module and understand the structure immediately.
We have organized these standards into four main categories:
1. File and Folder Organization
2. Naming Conventions
3. Code Structure and Layout
4. Documentation
] -->

<!--raw-typst #draft[
Explain how each standard/convention is presented. Explain the id, a deeper explanation, the rationale followed and if applicable some examples.
] -->

### File and Folder Organization

#### The Module Unit
<!--raw-typst #convention(id: "FO-01", title: "Module Structure")[
**Standard**: A module must consist of exactly one public header file (`.h`) and one, same-named private source file (`.c`).

**Rationale**: Enforces clear boundaries. The header is the contract; the source is the implementation.
] -->

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

#### Source Files
<!--raw-typst #convention(id: "CS-04", title: "Source Content")[
**Standard**: The module header must be included first in the source file.

**Rationale**: Verifies that the header is truly self-contained.
] -->

<!--raw-typst #convention(id: "CS-05", title: "Source Organization")[
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

## Unit Testing and Hardware Emulation

<!--raw-typst #draft[
In this section, we tackle the biggest challenge in embedded development: verification.
We propose a strategy that moves the majority of testing off the hardware and onto the development machine.
] -->

### The "Faking" Strategy
<!--raw-typst #draft[
**Concept**: "Faking" means creating a software implementation of a hardware peripheral (a "fake") that runs on the host machine.
**Goal**: Decouple the application logic from the physical silicon.
**Mechanism**:
1. Define a strict Hardware Abstraction Layer (HAL).
2. Create a "Native" implementation for the target.
3. Create a "Simulation" implementation for the host (e.g., printing to console instead of sending UART).
] -->

### Off-Target vs. On-Target Testing

#### Off-Target (Host)
<!--raw-typst #draft[
**Approach**: Compile the code on the PC using the "Faking" layer.
**Benefit**: Ultra-fast iteration, access to powerful debuggers, no flash/upload time.
**What to Test**: Protocol logic, state machines, data processing, algorithms.
] -->

#### On-Target (Device)
<!--raw-typst #draft[
**Approach**: Compile for the microcontroller using the "Native" layer.
**Benefit**: Verifies timing, interrupt behavior, and actual electrical interactions.
**Tooling**: Use lightweight "Debug Modules" or simple test harnesses that report status via LEDs or a basic serial port.
] -->
