# Recommended Practices and Conventions

## Introduction to Recommended Practices

The recommended practices and proposed coding and development conventions detailed in this book are purely pragmatic.
Those wer gathered through learning and surviving due to natural selection.
Meaning that those that provided valuable remain, while those that  more effort than benefit naturally gone and gets unused.
During this exploratory effort, carried out during the professional life of the author, plenty of different approaches and suggestions have been tested, used and unused.
Most of them come from the gold standards books, conventions and authors from software and embedded development world, while some have been adapted and evolving to what we present now.

<!--raw-typst #draft[ 
Describe the importance of such tools and practices in the presented modular approach presented.
- Explain the grouping of such tools and how we narrow to these groups
  -  Coding standards and conventions
  -  Hardware emulation approaches 
  -  Debug modules in unit testing
] -->

<!--raw-typst #draft[ 
Explain that those are only recommendations and that this book follows them, but could not be usable in all cases.
] -->
---

## Coding Standards and Conventions

<!--raw-typst #draft[ 
 Consistency across teams and projects.
] -->

<!--raw-typst #draft[ 
  Reducing onboarding time for new developers.
] -->

<!--raw-typst #draft[ 
  Enabling tools like linters to catch issues early.
] -->

### Specific Recommendations (one per sub-sub section)

<!--raw-typst #draft[ 
  *To do*, define a   
] -->

- **Naming Conventions**: Variables, functions, constants, and macros.
- **Folder and File Structure**:
  - Splitting headers and source files by module.
  - Standardizing include paths.
- **Style Guides**:
  - Indentation, line length, and commenting practices.
  - Inline documentation and Doxygen setup for embedded projects.

### Practical Example

- Transforming messy code into clean, standard-compliant code.

---

## 3. Unit Testing in Embedded Systems

### Challenges in Embedded Testing

- Limited resources and hardware dependencies.
- Lack of standard frameworks compared to general software.

### Strategies for Testing

- Mocking hardware dependencies (e.g., simulating peripherals).
- Writing testable code: Dependency injection and abstraction layers.
- Debugging on target vs. simulation.

### Testing Frameworks

- CUnit, Unity, or custom lightweight testing frameworks.

### Example

- Unit test for a linked list module from your repository.
- Mocking a simple hardware function like GPIO read/write.

---

## Summary

- Recap key practices.
- Emphasize how these practices lay the groundwork for patterns and templates in later chapters.
