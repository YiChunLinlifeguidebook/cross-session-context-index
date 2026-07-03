# Nine Palace Index

Nine Palace Index is an experimental lightweight indexing and weighting project developed directly in Termux on mobile.

This repository is part of a broader long-term creative and technical direction connected to:

- **Mechanical Soul**
- **Life Guidebook**

## Vision

The goal of this project is to explore how structured indexing, weighted signals, and lightweight computation can support future AI-oriented systems, personal knowledge structures, and decision-support tools.

It is being developed under constrained conditions — primarily on a mobile device — as a proof that meaningful technical systems can still be built with limited hardware.

## Current Focus

- Lightweight indexing logic
- Weighted configuration and scoring
- Simple command-line workflow
- Mobile-first development in Termux
- Maintainable project structure for future expansion

## 快速開始（Termux）

```sh
# 1. 編譯
make build

# 2. 寫入一筆記錄（自動分類）
./bin/weight config/weights.conf records.dat "AI生成式系統核心架構"

# 3. 查看索引統計
./bin/index records.dat

# 4. JSON 格式輸出
./bin/index records.dat --json

# 5. 安裝到 PATH（可選）
make install
```

## Project Structure

```text
.
├── CHANGELOG.md
├── CONTRIBUTING.md
├── LICENSE
├── Makefile
├── README.md
├── VERSION
├── bin/
├── config/
├── docs/
├── src/
├── build.sh
├── test.sh
└── records.dat
```

## Development Environment

- **Device:** OPPO Reno 14
- **Terminal:** Termux
- **Version Control:** Git + GitHub
- **Remote Protocol:** SSH
- **Primary Languages:** C / C++

## Philosophy

This repository is not only a codebase.  
It is also part of a longer journey:

- rebuilding technical ability,
- creating under real-world constraints,
- and moving step by step toward a future studio vision.

## Related Direction

- **Mechanical Soul** — future studio identity
- **Life Guidebook** — long-term final vision

## Status

Early prototype.

## License

See `LICENSE`.
