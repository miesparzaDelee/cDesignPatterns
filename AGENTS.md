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
5. **Modification Constraint**: **NEVER modify book content (`book/*.md`) unless explicitly instructed by the USER.** This includes formatting and metadata changes.

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
powershell -ExecutionPolicy Bypass -File companion_code/ch3_patterns/build/invoke_wsl_tests.ps1

# Direct runner (from companion_code/ch3_patterns/build/)
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
   Follow these specific workflows for development and initialization:
   - **[Session Startup](file:///c:/Users/Delee_RD/cDesignPatterns/.agent/workflows/startup.md)**: Steps to initialize a new development session.
   - **[Chapter Development](file:///c:/Users/Delee_RD/cDesignPatterns/.agent/workflows/develop_chapter.md)**: Steps for developing code and prose sections.

2. **Project Metadata and Status**:
   **[book/_guide.md](file:///c:/Users/Delee_RD/cDesignPatterns/book/_guide.md)** is the SOLE source of truth for chapter statuses, summaries, and dependencies.
   - **NEVER** use YAML frontmatter in book files (`book/*.md`).
   - If you need to update a chapter's status or metadata, do it in `_guide.md`.

3. **Coding Standards and Conventions**:
   The primary source of truth for all code style, naming, and testing standards is **[book/ch2.md](file:///c:/Users/Delee_RD/cDesignPatterns/book/ch2.md)**.
   - Use the IDs (e.g., `NC-01`, `CS-04`) when discussing code reviews or explaining implementations.
   - When writing book content, explicitly reference these practices to reinforce the book's teachings.

4. **Opaque Pattern (Key Pattern)**:
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
- `companion_code/ch3_patterns/build/run_tests.sh` - Test runner script
- `companion_code/ch3_patterns/build/invoke_wsl_tests.ps1` - WSL test helper
- `scripts/build_book.py` - Book generation script

## Book Development

Development is a conversation. Always check `book/_guide.md` before starting work to understand current context.

1. **Interactive Design**: Never "dump" a full implementation. Start with headers or skeletons and discuss with the USER.
2. **Structural Planning**: For text, define the "bones" (paragraphs and relationships). Use the workflow in `.agent/workflows/develop_chapter.md`.
3. **Continuous Feedback**: Wait for USER approval after each logical step (Header -> Impl -> Tests -> Text).
4. **Literate Integration**: Always ensure code and book text support one another.
5. **Modification Constraint**: **NEVER modify book content (`book/*.md`) unless explicitly instructed by the USER.** This includes formatting and metadata changes.
6. **Build Verification**: Run `python scripts/build_book.py` to verify the build succeeds after any change.
