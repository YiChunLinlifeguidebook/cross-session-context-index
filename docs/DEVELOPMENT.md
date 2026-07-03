# Development

This project is optimized for simple command-line work, including Termux.

## Requirements

- `make`
- `gcc`
- `g++`
- POSIX shell (`sh`)

## Quick Start

```bash
./scripts/build.sh
./scripts/test.sh
./scripts/run.sh
```

## Helper Scripts

- `scripts/build.sh` — compile binaries via `make`
- `scripts/test.sh` — execute `make test`
- `scripts/run.sh` — run `bin/index records.dat`
- `scripts/check.sh` — run build + test in one command

These scripts are intentionally lightweight and avoid framework-specific tooling.

## Manual Commands

```bash
make
make test
./bin/index records.dat --json
```

## Notes for Mobile/Termux

- Keep commands short and repeatable.
- Prefer scripts over long one-liners.
- Use `git status` frequently before commits.
