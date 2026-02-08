---
description: Run the Chapter 3 patterns library unit tests via WSL.
---

# Run Chapter 3 Tests

To run the unit tests for the pattern library:

// turbo

1. Run the WSL bridge script:
   `powershell -ExecutionPolicy Bypass -File companion_code/ch3_patterns/build/invoke_wsl_tests.ps1`

2. (Optional) Run specific tests or groups by passing arguments:
   - To clean: `-t clean`
   - To build and run: `-t all`
   - To run specific group: `-a "-g <GroupName>"`
   - To run specific test: `-a "-g <GroupName> -n <TestName>"`

Example for a specific test group:
`powershell -ExecutionPolicy Bypass -File companion_code/ch3_patterns/build/invoke_wsl_tests.ps1 -a "-g Rectangle_ObjectPattern"`
