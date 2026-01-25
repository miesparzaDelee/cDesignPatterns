# AGENTS.md - C Design Patterns Repository

This repo is a C design patterns book with a literate build system. Code examples
live in `companion_code/ch3_patterns/`, tests use CppUTest, and the book is built
from Markdown in `book/` with Python scripts.

## Collaboration Mindset

Development is a conversation. Follow the workflows in `.agent/workflows/develop_chapter.md` to ensure:

1. **Interactive Design**: Never "dump" a full implementation. Start with headers or skeletons and discuss with the USER.
2. **Structural Planning**: For text, define the "bones" (paragraphs and relationships) before writing prose.
3. **Continuous Feedback**: Wait for USER approval after each logical step (Header -> Impl -> Tests -> Text).
4. **Literate Integration**: Always ensure code and book text support one another.

## Build, Test, Lint Commands

### Book Build

```bash
python scripts/build_book.py
```

- Reads Markdown chapters from `book/`
- Injects C code from `src/` via `{{ file "path" type="..." }}` tags
- Outputs hydrated Markdown to `build/` and Typst PDF source

### Unit Tests (CppUTest)

Preferred: run the VS Code task named `Test Patterns`.

CLI equivalents (full suite):

```bash
# WSL helper wrapper (recommended on Windows)
powershell -ExecutionPolicy Bypass -File companion_code/ch3_patterns/scripts/invoke_wsl_tests.ps1

# Direct runner (from companion_code/ch3_patterns/scripts/)
./run_tests.sh

# Specify CppUTest location
./run_tests.sh -c /path/to/cpputest
```

Single test (after build, from `companion_code/ch3_patterns/tests/build/`):

```bash
./patterns_lib_tests -g <TestGroup> -n <TestName>
```

Test groups are declared with `TEST_GROUP(...)` in
`companion_code/ch3_patterns/tests/srctest/*Tests.cpp`.

### Linting

No dedicated lint command is configured. Use compiler warnings from the CppUTest
build and keep formatting consistent with the style section below.

## Guidelines and Operational Procedures

To ensure we "start with the right foot" and maintain quality, agents MUST follow these references:

1. **Operational Workflows**:
   Consult [.agent/workflows/](file:///c:/Users/Delee_RD/cDesignPatterns/.agent/workflows/) for session startup and chapter development processes. These are the living instructions for this repository.

2. **Coding Standards and Conventions**:
   The primary source of truth for all code style, naming, and testing standards is **[book/ch2.md](file:///c:/Users/Delee_RD/cDesignPatterns/book/ch2.md)**.
   - Use the IDs (e.g., `NC-01`, `CS-04`) when discussing code reviews or explaining implementations.
   - When writing book content, explicitly reference these practices to reinforce the book's teachings.

3. **Opaque Pattern (Key Pattern)**:
   While detailed in Chapter 2, remember the core requirement for this repo: expose size constants and opaque handles in headers; hide implementation details in sources.

## Literate Programming Tags

In `book/*.md`, inject code with:

```markdown
{{ file "path/to/file.c" type="TYPE" name="IDENTIFIER" }}
```

Types: `whole`, `include`, `define`, `typedef`, `struct`, `function`,
`region`, `test_group`, `test`

## Markdown HTML Tags

We use cmarker to parse custom HTML tags in Markdown so the content stays
readable while Typst handles layout. Register new tags in
`scripts/build_book.py` via the `html:` mapping, and implement the rendering
functions in `book/template.typ`.

Tracked tags and attributes live in `docs/markdown_tags.md`.

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
- `companion_code/ch3_patterns/scripts/invoke_wsl_tests.ps1` - WSL test helper
- `scripts/build_book.py` - Book generation script

## Book Development

Before editing chapters, check `book/_guide.md` for status and notes.

Status meanings:

- **Complete** - Final review ready, code and tests validated
- **First Draft** - Section templates and ideas, needs more content
- **Ideas Only** - Initial concepts, needs revision
- **Not Started** - No content yet

When modifying chapter content:

1. Update `book/_guide.md` with new status and notes
2. Ensure code examples compile and tests pass
3. Update `book/structure.txt` if adding new chapters
4. Run `python scripts/build_book.py` to verify the build succeeds
