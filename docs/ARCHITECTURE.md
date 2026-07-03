# Architecture

Nine Palace Index currently has a small two-binary architecture:

- `src/weight.c` (`bin/weight`)
  - Loads keyword/category/weight rules from `config/weights.conf`
  - Accepts content from CLI input and classifies manually or automatically
  - Calculates weights and appends records into `records.dat`
- `src/index.cpp` (`bin/index`)
  - Reads `records.dat`
  - Prints records and category statistics
  - Supports plain output and `--json`

## Data Model

- File header (`magic`, `version`, `count`)
- Record entries (`id`, `category`, `content`, `weight`, `created_at`)

`records.dat` is a binary file shared between the C writer and C++ reader.

## Data Flow

1. `weight` parses keyword rules from `config/weights.conf`.
2. `weight` classifies content and computes weight.
3. `weight` loads existing `records.dat`, appends a new record, and writes back.
4. `index` reads the file, aggregates category weights, and renders output.

## Design Notes

- Keep runtime simple for Termux/mobile constraints.
- Use plain C/C++ binaries and a Makefile-based build.
- Prefer minimal dependencies and transparent data handling.
- Preserve project direction toward **Mechanical Soul** and **Life Guidebook** while keeping engineering output practical.
