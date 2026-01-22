# Book Builder Tools

This folder contains the Python scripts used to "hydrate" the book's Markdown files. It reads the raw chapters in `book/`, extracts real C code from `src/`, and outputs processed Markdown to `build/`.

## 1. Quick Start

Run the production builder from the project root:

```bash
python3 scripts/build_book.py
```

The processed files will appear in the `build/` directory.

## 2. Dependencies

* **Python 3.x** (Standard library only; no `pip install` required).

## 3. How to Use Tags in Markdown

In your `book/*.md` files, use the following syntax to inject C code.

### A. Syntax Overview

`{{ file "path/to/file.c" type="TYPE" name="NAME" }}`

* **path**: Relative to the project root (e.g., `src/patterns/objectPattern.c`).
* **type**: The kind of extraction (see below).
* **name**: The identifier to find (optional for some types).

### B. Supported Types

| Type | Description | Example |
| :--- | :--- | :--- |
| **`whole`** | Includes the entire file content. | `type="whole"` |
| **`include`** | Extracts a specific `#include` line. | `type="include" name="stdint.h"` |
| **`define`** | Extracts a macro definition (`#define`). | `type="define" name="MAX_SIZE"` |
| **`typedef`** | Extracts a `typedef` (struct/enum/pointer). | `type="typedef" name="object_t"` |
| **`struct`** | Extracts a struct definition or forward decl. | `type="struct" name="myStruct"` |
| **`function`** | Extracts a function body or prototype. | `type="function" name="op_Init"` |
| **`region`** | Extracts code between custom markers. | `type="region" name="my_snippet"` |
| **`test_group`** | Extracts a CppUTest TEST_GROUP block. | `type="test_group" name="MyGroup"` |
| **`test`** | Extracts a CppUTest TEST block. | `type="test" name="MyGroup,myTest"` |

---

## 4. Advanced Features

### Automatic Merging

If you place two tags next to each other (separated only by whitespace), they will be merged into a single C code block in the output.

**Input:**

```markdown
{{ file "src/demo.h" type="struct" name="A" }}
{{ file "src/demo.h" type="struct" name="B" }}
```

**Output:**

```c
struct A { ... };

struct B { ... };
```

### Regions (Arbitrary Lines)

To extract a specific block of logic inside a function without extracting the whole function, use "regions".

**1. In your C file:**

```c
void complexLogic() {
    int x = 0;
    // region: math_logic
    x = x + 5;
    y = x * 2;
    // endregion
}
```

**2. In your Markdown:**
`{{ file "src/logic.c" type="region" name="math_logic" }}`

**3. Output:**

```c
x = x + 5;
y = x * 2;
```

*Note: When you extract the full `complexLogic` function using `type="function"`, the `// region:` comments are automatically stripped to keep the code clean.*

## 5. Scripts Overview

* **`builder.py`**: The core logic library. Contains all regex patterns and extraction rules.
* **`build_book.py`**: The production script. Scans `book/`, ignores files starting with `_`, and outputs to `build/`.
* **`test_env_runner.py`**: A helper script to run the builder on the `test_env/` folder for debugging.

## 6. Running Unit Tests

The companion code tests are run from `companion_code/ch3_patterns/scripts/`.

* **`run_tests.sh`**: Bash script to run CppUTest suites.
* **`invoke_wsl_tests.ps1`**: PowerShell wrapper for running tests in WSL from Windows.

### Usage

```bash
# Run all tests (from companion_code/ch3_patterns/scripts/)
./run_tests.sh

# Run specific test suite
./run_tests.sh -t factoryTests

# From Windows with WSL
powershell -ExecutionPolicy Bypass -File companion_code/ch3_patterns/scripts/invoke_wsl_tests.ps1 -t factoryTests
```

Available test suites: rectagleTests, circleTests, triangleTests, familyTests, vtableTests, factoryTests
