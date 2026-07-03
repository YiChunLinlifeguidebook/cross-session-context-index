# Development (Mobile-first / Termux)

This project is designed to stay easy to build and maintain from a phone-first setup.

## Prerequisites

- `clang` or `gcc/g++`
- `make`
- `bash` (Termux default shell tools)

## Build and Check

```bash
./scripts/build.sh
./scripts/check.sh
```

## Run

```bash
# Auto classify from content
./scripts/run.sh "Termux GitHub workflow"

# Manual category
./scripts/run.sh --category JIU_C "system architecture test"

# Export JSON
./bin/index records.dat --json
```

## Notes for GitHub Push from Termux

If push is blocked by GH007 email privacy:

1. Set a GitHub noreply email in local git config.
2. Re-commit with that email.
3. Push again.

This keeps repository history public-safe while preserving mobile workflow.
