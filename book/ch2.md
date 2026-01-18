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
We have organized these standards into three categories:
1. File and Folder Organization
2. Naming Conventions
3. Code Structure and Layout
] -->

### File and Folder Organization

#### The Module Unit
<!--raw-typst #draft[
**Standard**: Every module must consist of exactly one public header file (`.h`) and one private source file (`.c`) with the same name.
**Rationale**: Enforces clear boundaries. The header is the contract; the source is the implementation. Prevents "header-only" logic or split implementations that represent the same conceptual object.
] -->

#### File Hierarchy
<!--raw-typst #draft[
**Standard**: Source files are located in `src/`, headers for public use can be in `src/` or `include/` depending on the project scope, but for this book we keep them collocated in `src/` for simplicity.
**Rationale**: Keeps related files together.
] -->

### Naming Conventions

#### Static (Private) Variables and Functions
<!--raw-typst #draft[
**Standard**: All file-scope (static) variables and functions must be prefixed with `s_` (for static variables) or `_` (for internal functions), or simply use descriptive names that clearly do not collide with public namespaces if the `static` keyword is properly used.
**Preferred Approach**: Use `variable_name` for locals, `module_variable_name` for public struct members, and `s_variable_name` for private file-scoped, static variables.
**Rationale**: Instantly identifies the scope of the variable during code review. Prevents accidental naming collisions and makes it obvious when we are modifying global state.
] -->

#### Component Prefixes
<!--raw-typst #draft[
**Standard**: All public functions and types usually must include the module name as a prefix (e.g., `uart_init`, `uart_send`).
**Rationale**: C lacks namespaces. Prefixes simulate namespaces and prevent symbol clashes.
] -->

### Code Structure and Layout

#### Header File Layout
<!--raw-typst #draft[
**Standard**: Headers must follow a strict order:
1. License/Copyright
2. Include Guard (or `#pragma once`)
3. Includes (Standard -> 3rd Party -> Project)
4. Public Macro Definitions
5. Public Type Definitions (structs, enums)
6. Public Function Prototypes
**Rationale**: Predictability. Users know exactly where to look for the API.
] -->

#### Source File Layout
<!--raw-typst #draft[
**Standard**: Source files must follow a strict order:
1. Includes (Module Header first -> Others)
2. Private Macro Definitions
3. Private Type Definitions
4. Private (Static) Function Prototypes
5. Private (Static) Variables
6. Public Function Implementations
7. Private Function Implementations
**Rationale**: The "Module Header first" rule ensures the header is self-contained. Declaring private prototypes up front allows functions to be implemented in any order (e.g., top-down).
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
