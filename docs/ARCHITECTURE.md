# Architecture

Nine Palace Index currently has a small two-binary architecture:

- `src/weight.c` (`bin/weight`)
  - Loads keyword rules from `config/weights.conf`
  - Calculates weights from input content
  - Appends records into `records.dat`
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
2. `weight` classifies or accepts a category and computes weight.
3. `weight` loads existing `records.dat`, appends a new record, and writes back.
4. `index` reads the file, aggregates category weights, and renders output.

## Design Notes

- Lightweight CLI-first design for Termux/mobile workflows.
- No external runtime dependencies beyond standard C/C++ toolchains.
- Intentional early-stage simplicity to keep iteration fast.
