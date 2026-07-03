# Architecture

Nine Palace Index currently has two core binaries:

- `bin/weight` (`src/weight.c`)
  - Loads keyword/category/weight rules from `config/weights.conf`
  - Accepts a record from CLI input
  - Calculates weight and category (manual or auto mode)
  - Persists records into `records.dat` (binary format)
- `bin/index` (`src/index.cpp`)
  - Reads `records.dat`
  - Prints human-readable output or JSON (`--json`)
  - Aggregates category weights for quick inspection

## Data Flow

1. `weight` reads config and existing records.
2. New content is classified and stored.
3. `index` reads the same store for reporting/export.

## Design Notes

- Keep runtime simple for Termux/mobile constraints.
- Use plain C/C++ binaries and a Makefile-based build.
- Prefer minimal dependencies and transparent data handling.
- Preserve project direction toward **Mechanical Soul** and **Life Guidebook** while keeping engineering output practical.
