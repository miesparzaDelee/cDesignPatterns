# C Design Patterns Companion Code

This directory contains the C implementation of design patterns from the book "C Design Patterns".

## Structure

- `src/`: C source files for the patterns
- `include/`: Public headers
- `tests/`: Unit tests using CppUTest
- `scripts/`: Test runner scripts

## Running Tests

### Prerequisites
- Linux or WSL environment
- CppUTest framework

### Commands
```bash
# Run all tests
./scripts/invoke_wsl_tests.ps1

# Run specific pattern tests
./scripts/invoke_wsl_tests.ps1 -t factoryTests
```

Available test suites: rectagleTests, circleTests, triangleTests, familyTests, vtableTests, factoryTests

## Patterns Implemented

- Factory Pattern: `factory_shape.h/.c`
- VTable Pattern: Virtual tables for polymorphism
- And more...</content>
<parameter name="filePath">C:\Users\Delee_RD\cDesignPatterns\companion_code\ch3_patterns\README.md