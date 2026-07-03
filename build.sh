#!/usr/bin/env sh
set -e
echo "🔨 Building Nine Palace Index..."
make build
echo "✅ 編譯完成！執行檔在 bin/ 目錄"
echo "   bin/weight  — 寫入端（加權分類記錄）"
echo "   bin/index   — 讀取端（查看統計）"
