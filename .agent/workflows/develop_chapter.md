---
description: Interactive steps for developing code and text sections of the book.
---

This workflow ensures every part of the book is discussed and reviewed by the USER before finalization.

### Pattern/Code Development Workflow

Follow these steps for any section involving C code:

1. **Header Discussion**:
   Propose and discuss the public header files (`.h`). Focus on API design and the Opaque Pattern.
   - **Requirement**: Reference convention IDs from [book/ch2.md](file:///c:/Users/Delee_RD/cDesignPatterns/book/ch2.md) (e.g., `CS-04`, `NC-04`) to justify design choices.
   - Wait for USER feedback/approval.

2. **Implementation & Tests**:
   Implement the source code (`.c`) and write the CppUTest unit tests (`*Tests.cpp`). Discuss any internal design decisions made during implementation.

3. **Discussion & Review**:
   Present the implementation and test results. Review with the USER. Fix any issues.

4. **Book Integration**:
   Once code is stable, write the corresponding book section (`.md`) using `{{ file ... }}` tags to reference the code.

---

### Text/Prose Development Workflow

Follow these steps for introductory, conceptual, or non-code-centric sections:

1. **Skeleton Definition**:
   Define a outline/skeleton of the section.
   - List the main ideas per paragraph.
   - Define how many paragraphs will be used.
   - Detail how these ideas relate to one another.
   - Wait for USER feedback.

2. **Overall Structure Review**:
   Discuss and finalize the structure based on the skeleton.

3. **Paragraph-by-Paragraph Writing**:
   Write the content one paragraph (or small logical section) at a time, discussing with the USER as you go.

4. **Final Revision**:
   Conduct a final review of the entire section for tone, clarity, and consistency.
