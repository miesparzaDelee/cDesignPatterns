# ADR: Sensor Data Buffering

## Status

Accepted

## Context

Need to buffer sensor readings to handle burst data without loss.
Memory constrained to 2KB for this module.

## Decision

Use circular buffer with 100-sample capacity (200 bytes).
Overflow strategy: drop oldest samples.

## Alternatives Considered

- **Dynamic allocation**: Rejected due to fragmentation risk on constrained platforms.
- **Larger buffer**: Exceeds the 2KB memory budget allocated to this module.
- **Linked list**: Higher per-element overhead (pointer + data) and fragmentation risk.

## Consequences

- Simple, predictable memory usage with a fixed footprint.
- May lose data during sustained bursts exceeding 100 samples.
- No heap usage — safe for bare-metal and RTOS environments.
