# Chapter 2: Recommended Practices and Conventions

## 1. Introduction to Recommended Practices

- **Objective**: Explain why coding standards, testing, debugging, and version control are essential for modular embedded systems.
- **Key Takeaways**: What the reader will gain by following these practices.

---

## 2. Coding Standards and Conventions

### Why Standards Matter

- Consistency across teams and projects.
- Reducing onboarding time for new developers.
- Enabling tools like linters to catch issues early.

### Specific Recommendations

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

### Testing Frameworks

- CUnit, Unity, or custom lightweight testing frameworks.

### Example

- Unit test for a linked list module from your repository.
- Mocking a simple hardware function like GPIO read/write.

---

## 4. Debugging Techniques

### Common Debugging Challenges

- Pinpointing issues in modular codebases.
- Debugging on target vs. simulation.

### Best Practices

- Use of logging (UART, SWO).
- Debugging tools: JTAG/SWD, logic analyzers.
- Strategies for isolating bugs in modular systems.

### Example Scenario

- Debugging a task scheduler issue using logging and breakpoints.

---

## 5. Version Control Best Practices

### Why Version Control is Essential for Modular Development

- Managing multiple contributors and codebase versions.
- Tracking changes in modules without introducing regressions.

### Recommendations

- Structuring repositories for modular systems.
- Branching strategies for feature development.
- Using submodules for third-party libraries.

### Examples

- Setting up a Git repository with modular code templates.

---

## 6. Summary

- Recap key practices.
- Emphasize how these practices lay the groundwork for patterns and templates in later chapters.
