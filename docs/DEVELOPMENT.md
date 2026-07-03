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
./scripts/run.sh "Termux GitHub workflow"
./scripts/check.sh
```

## Helper Scripts

- `scripts/build.sh` — compile binaries via `make -B all`
- `scripts/test.sh` — execute `make -B test`
- `scripts/run.sh` — add a record using `bin/weight`
- `scripts/check.sh` — run the project test flow

These scripts are intentionally lightweight and avoid framework-specific tooling.

## Manual Commands

```bash
make -B all
make -B test
./bin/index records.dat --json
```

## Notes for Mobile/Termux

- Keep commands short and repeatable.
- Prefer scripts over long one-liners.
- Use `git status` frequently before commits.

## Notes for GitHub Push from Termux

If push is blocked by GH007 email privacy:

1. Set a GitHub noreply email in local git config.
2. Re-commit with that email.
3. Push again.
