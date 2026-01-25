---
description: Steps to initialize a development session in the C Design Patterns repository.
---

To ensure a session starts correctly, follow these steps:

1. **Read Core Guidelines**:
   View [AGENTS.md](file:///c:/Users/Delee_RD/cDesignPatterns/AGENTS.md) to refresh context on coding standards, naming conventions, and directory structure.

2. **Check Project Progress**:
   View [book/_guide.md](file:///c:/Users/Delee_RD/cDesignPatterns/book/_guide.md) to identify which chapters are "In Progress", "Ideas Only", or need "Revision".

3. **Verify Baseline Stability**:
   Ensure the current code and book build are healthy before making changes.

   // turbo
   - Run `python scripts/build_book.py` to check the literate build system.

   // turbo
   - Run `powershell -ExecutionPolicy Bypass -File companion_code/ch3_patterns/build/invoke_wsl_tests.ps1` to verify unit tests.

4. **Initialize Task State**:
   Create or update `task.md` in the brain directory to track the current session's objectives.
